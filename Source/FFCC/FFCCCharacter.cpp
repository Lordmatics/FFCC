// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FFCCCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EngineUtils.h"
#include "FFCC/Camera/CameraFollow.h"
#include "Classes/GameFramework/PlayerController.h"
#include "Classes/Engine/Texture2D.h"
#include "FFCC/CustomComponents/LookAt/LookAtComponent.h"
#include "FFCC/CustomComponents/Dialogue/DialogueComponent.h"
#include "FFCC/CustomComponents/NPCStats/NPCStatsComponent.h"
#include "FFCC/CustomComponents/Shop/ShopComponent.h"
#include "FFCC/CustomComponents/Pickupables/PickupComponent.h"
#include "FFCC/NPC/NPC.h"
#include "FFCC/DataAssets/Merchant/Home/MerchShopDataAsset.h"
#include "FFCC/DataAssets/Blacksmith/Home/BlacksmithShopDataAsset.h"
#include "FFCC/DataAssets/Item/InventoryDataAsset.h"
#include "FFCC/Items/Item.h"
#include "FFCC/Items/Recipes/CraftingRecipe.h"
#include "FFCC/DataAssets/Blacksmith/Home/BlacksmithShopDataAsset.h"
#include "FFCC/Debug/Logs.h"

//#include "Runtime/Engine/Classes/Engine/StreamableManager.h"
//#include "Engine.h"

//////////////////////////////////////////////////////////////////////////
// AFFCCCharacter

AFFCCCharacter::AFFCCCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	InteractSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractCollisionSphere"));
	InteractSphere->SetupAttachment(GetCapsuleComponent());
	InteractSphere->SetCollisionProfileName(FName(TEXT("Interact")));
	InteractSphere->SetSphereRadius(100.0f);
	InteractSphere->OnComponentBeginOverlap.AddDynamic(this, &AFFCCCharacter::OnOverlapEnter);
	InteractSphere->OnComponentEndOverlap.AddDynamic(this, &AFFCCCharacter::OnOverlapExit);

	EmptyString = FString(TEXT(""));
	QMString = FString(TEXT("????"));

	InteractIndexInDialogue = 0;
	InteractTargetCurrentSentence = EmptyString;
	InteractTargetName = QMString;

	bShowChat = false;

	TradeFlags = Flags::E_Alchemist;
	ShopItemIndex = 0;
	MaxShopItemIndex = 2;
	bInAShop = false;

	bShowMerchantStock = false;
	bShowBlacksmithStock = false;
	bShowPlayerStock = false;
	MerchantHierarchy = 0;
	BlacksmithHierarchy = 0;

	LookAtComp = CreateDefaultSubobject<ULookAtComponent>(TEXT("LookAtComponent"));
	MerchantLevel = 1;
	BlacksmithLevel = 1;
	bMenuScroll = false;
	IndexForTopElementInPlayersInventory = 0;

	bShowAreYouSurePrompt = false;
	GilCount = 999999; // Remember to load this back in
	CachedBuySellIndex = 0;
	//ShopComponent = CreateDefaultSubobject<UShopComponent>(TEXT("ShopComponent"));
	//TestShopComponent = CreateDefaultSubobject<UShopComponent>(TEXT("TestShopComponent"));

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

void AFFCCCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (UWorld* const World = GetWorld())
	{
		ACameraFollow* temp = nullptr;
		for (TActorIterator<ACameraFollow> ActorItr(World); ActorItr; ++ActorItr)
		{
			// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
			temp = *ActorItr;
			break;
		}
		if (APlayerController* PC = Cast<APlayerController>(Controller))
		{
			if(temp)
				PC->SetViewTargetWithBlend(temp, 1.0f);
		}
	}

	if (InventoryData && InventoryData->GetItemDataList().Num() > 0)
	{
		InventoryData->ClearInventory();
		// Load Saved Data to restock inventory
	}

	if (CurrentBlacksmithData)
	{
		CurrentBlacksmithData->ClearInventory();
		// Load Saved Data to restock inventory
	}
	//UE_LOG(GenLog, Warning, TEXT("GenLog"));
	//UE_LOG(AILog, Warning, TEXT("AILog"));
	//UE_LOG(PlayerLog, Warning, TEXT("PlayerLog"));
	//UE_LOG(BadLog, Warning, TEXT("BadLog"));
}
//////////////////////////////////////////////////////////////////////////
// Input

void AFFCCCharacter::UpgradeMerchantLevel()
{
	MerchantLevel++;
	MaxShopItemIndex = GetMaxShopIndex();
	// TEMP
	UpgradeBlacksmithLevel();
}

void AFFCCCharacter::UpgradeBlacksmithLevel()
{
	BlacksmithLevel++;
}

void AFFCCCharacter::DebugSell()
{
	if (!InventoryData) return;
	UE_LOG(LogTemp, Warning, TEXT("BEFORE - Inventory Num: %d"), InventoryData->GetSize());
	InventoryData->RemoveItemAt(ShopItemIndex);
	UE_LOG(LogTemp, Warning, TEXT("Removing Element: %d"), ShopItemIndex);
	UE_LOG(LogTemp, Warning, TEXT("AFTER - Inventory Num: %d"), InventoryData->GetSize());

}

void AFFCCCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFFCCCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFFCCCharacter::StopJumping);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AFFCCCharacter::BeginInteract);
	PlayerInputComponent->BindAction("ShopUp", IE_Pressed, this, &AFFCCCharacter::ShopUp);
	PlayerInputComponent->BindAction("ShopDown", IE_Pressed, this, &AFFCCCharacter::ShopDown);
	PlayerInputComponent->BindAction("ShopSelect", IE_Pressed, this, &AFFCCCharacter::ShopSelect);
	PlayerInputComponent->BindAction("ShopBack", IE_Pressed, this, &AFFCCCharacter::ShopBack);

	PlayerInputComponent->BindAction("DebugML", IE_Pressed, this, &AFFCCCharacter::UpgradeMerchantLevel);
	PlayerInputComponent->BindAction("DebugSell", IE_Pressed, this, &AFFCCCharacter::DebugSell);




	PlayerInputComponent->BindAxis("MoveForward", this, &AFFCCCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFFCCCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	//PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	//PlayerInputComponent->BindAxis("TurnRate", this, &AFFCCCharacter::TurnAtRate);
	//PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	//PlayerInputComponent->BindAxis("LookUpRate", this, &AFFCCCharacter::LookUpAtRate);
}

void AFFCCCharacter::Jump()
{
	if (bInAShop || bShowChat) return;
	Super::Jump();
}

void AFFCCCharacter::StopJumping()
{
	if (bInAShop || bShowChat) return;

	Super::StopJumping();
}

void AFFCCCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AFFCCCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AFFCCCharacter::MoveForward(float Value)
{
	if (bShowChat || bInAShop) return;

	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AFFCCCharacter::MoveRight(float Value)
{
	if (bShowChat || bInAShop) return;

	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AFFCCCharacter::OnOverlapEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherbodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor) return;
	UE_LOG(LogTemp, Warning, TEXT("Overlapped"));

	CurrentTargetActor = OtherActor;

	CurrentLookAtTarget = Cast<ULookAtComponent>(OtherActor->GetComponentByClass(ULookAtComponent::StaticClass()));
	if (CurrentLookAtTarget)
	{
		bInInteractRange = true;
	}	
	CurrentDialogueComponent = Cast<UDialogueComponent>(OtherActor->GetComponentByClass(UDialogueComponent::StaticClass()));
	if (CurrentDialogueComponent)
	{
		//TArray<FString> Dialogues = CurrentDialogueComponent->GetNPCDialogue();
		//int TotalDialogueLength = CurrentDialogueComponent->GetNPCDialogueLength();
		//InteractTargetName = CurrentDialogueComponent->GetNPCName();
		//InteractTargetCurrentSentence = Dialogues[InteractIndexInDialogue];
	}
	UNPCStatsComponent* NPCComp = Cast<UNPCStatsComponent>(OtherActor->GetComponentByClass(UNPCStatsComponent::StaticClass()));
	if (NPCComp)
	{
		FNPCStats NPCStats = NPCComp->GetNPCStats();
		switch (NPCStats.Trade)
		{
			case ECharacterTrade::E_Alchemist: // Gives Scrolls
			{
				//TradeFlags &= ~Flags::E_Blacksmith;
				//TradeFlags &= ~Flags::E_Merchant;
				//TradeFlags &= ~Flags::E_Tailor;
				//TradeFlags |= Flags::E_Alchemist;
				TradeFlags = Flags::E_Alchemist;
				UE_LOG(LogTemp, Warning, TEXT("TradeFlags (ALC)"));
				MaxShopItemIndex = 0;
				break;
			}
			case ECharacterTrade::E_Blacksmith: // Open Weapon + Armour Shop
			{
				TradeFlags = Flags::E_Blacksmith;
				UE_LOG(LogTemp, Warning, TEXT("TradeFlags (BLM)"));
				MaxShopItemIndex = 0;
				break;
			}
			case ECharacterTrade::E_Merchant: // Open Item Shop
			{
				TradeFlags = Flags::E_Merchant;
				UE_LOG(LogTemp, Warning, TEXT("TradeFlags (MER)"));
				MaxShopItemIndex = 2;
				break;
			}
			case ECharacterTrade::E_Tailor: // Open Accessory Shop
			{
				TradeFlags = Flags::E_Tailor;
				UE_LOG(LogTemp, Warning, TEXT("TradeFlags (TAI)"));
				MaxShopItemIndex = 0;
				break;
			}
			default:
			{
				TradeFlags = Flags::E_Other;
				UE_LOG(LogTemp, Warning, TEXT("TradeFlags (DEF)"));
				MaxShopItemIndex = 0;
				break;
			}
		}
	}

	// If Overlap is type safe
	ANPC* NPC = Cast<ANPC>(OtherActor);
	if (NPC && NPC->GetData())
	{
		// If is a merchant
		UMerchShopDataAsset* MerchData = Cast<UMerchShopDataAsset>(NPC->GetData()); // VTable points to correct version of data
		if (MerchData)
		{
			CurrentShopData = MerchData;
		}
		UBlacksmithShopDataAsset* BlacksmithData = Cast<UBlacksmithShopDataAsset>(NPC->GetData());
		if (BlacksmithData)
		{
			CurrentBlacksmithData = BlacksmithData;
		}
		//if (MerchData && ShopComponent)
		//{
		//	// Potential optimise here. Store locally, then push to UMG when enter shop.
		//	// Maybe improve things since UMG checks per frame
		//	ShopComponent->SetMerchantStock(*MerchData); // Pass by address for efficiency
		//}
	}
}

UMerchShopDataAsset* AFFCCCharacter::GetMerchData() const
{
	return CurrentShopData;
}

UBlacksmithShopDataAsset* AFFCCCharacter::GetBlacksmithData() const
{
	return CurrentBlacksmithData;
}

void AFFCCCharacter::OnOverlapExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherbodyIndex)
{
	if (!OtherActor) return;
	UE_LOG(LogTemp, Warning, TEXT("Overlapped-EXIT"));

	CurrentLookAtTarget = Cast<ULookAtComponent>(OtherActor->GetComponentByClass(ULookAtComponent::StaticClass()));

	if (CurrentLookAtTarget)
	{
		// WARNING: Need to Check Trigger has not overlap something else before you exit first encounter
		CurrentLookAtTarget->SetLookingAtTarget(nullptr);
		CurrentLookAtTarget->SetLookingAtTarget(false);
		CurrentLookAtTarget = nullptr;
		bInInteractRange = false;
	}
	CurrentDialogueComponent = Cast<UDialogueComponent>(OtherActor->GetComponentByClass(UDialogueComponent::StaticClass()));
	if (CurrentDialogueComponent)
	{
		CurrentDialogueComponent = nullptr;
	}

	CurrentTargetActor = nullptr;
	MenuReset(); // Maybe only do this if was interacting with npc
}

void AFFCCCharacter::BeginInteract()
{
	if (bInAShop) return;

	//	 TURN TO WHAT YOU ARE INTERACTING WITH
	if (LookAtComp && CurrentTargetActor)
	{
		// TODO: Smooth this out
		FRotator NewRotation;  LookAtComp->GetRotationToLookAt(GetActorLocation(), CurrentTargetActor->GetActorLocation(), NewRotation);
		//FRotator CurRot = GetActorRotation();
		//while (CurRot != NewRotation)
		//{
			//CurRot = FMath::RInterpTo(CurRot, NewRotation, GetWorld()->GetDeltaSeconds(), 5.0f);
		SetActorRotation(NewRotation, ETeleportType::TeleportPhysics);
		//}
	}

	//	MAKE OBJECT YOU ARE INTERACTING WITH LOOK AT YOU
	if (CurrentLookAtTarget && bInInteractRange)
	{
		UE_LOG(LogTemp, Warning, TEXT("Target now looking at player"));
		CurrentLookAtTarget->SetLookingAtTarget(this);
		CurrentLookAtTarget->SetLookingAtTarget(true);
	}

	// CHECK IF ITEM IS PICKUPABLE
	if (CurrentTargetActor)
	{
		AItem* Item = Cast<AItem>(CurrentTargetActor);
		if (Item && InventoryData)
		{
			ACraftingRecipe* Recipe = Cast<ACraftingRecipe>(Item);
			if (Recipe && CurrentBlacksmithData && Item->ItemDataAsset)
			{
				FCraftEquipmentData Data = FCraftEquipmentData(Recipe->CraftType, Item->ItemDataAsset);
				CurrentBlacksmithData->AddRecipe(Data);
				//InventoryData->
			}
			// If Inventory full -> Branch to lift not pick n destroy
			InventoryData->AddItem(Item->GetItemData());

			Item->OnPickedUp(); // Destroy
			Item = nullptr;
		}
	}


	if (CurrentDialogueComponent && bInInteractRange)
	{
		//TODO: Unhide Chat Box
		bShowChat = true;
		// Initialise conversation
		TArray<FString> Dialogues = CurrentDialogueComponent->GetNPCDialogue();
		int TotalDialogueLength = CurrentDialogueComponent->GetNPCDialogueLength();
		if (InteractIndexInDialogue < TotalDialogueLength)
		{
			// UPDATES WHATS DISPLAYED IN CHAT BOX
			InteractTargetName = CurrentDialogueComponent->GetNPCName();
			InteractTargetCurrentSentence = Dialogues[InteractIndexInDialogue];
		}


		//int TotalDialogueLength = CurrentDialogueComponent->GetNPCDialogueLength();

		// Proceed through dialogue
		InteractIndexInDialogue++;
		if (InteractIndexInDialogue > TotalDialogueLength)
		{
			// Go To Conversation End
			InteractIndexInDialogue = 0;
			InteractTargetName = QMString;
			InteractTargetCurrentSentence = EmptyString;
			// TODO: Hide chat box
			bShowChat = false;
			if (CurrentLookAtTarget)
			{
				// WARNING: Need to Check Trigger has not overlap something else before you exit first encounter
				CurrentLookAtTarget->SetLookingAtTarget(nullptr);
				CurrentLookAtTarget->SetLookingAtTarget(false);
				CurrentLookAtTarget = nullptr;
			}
			// Search for whether a menu should be openned
			switch (TradeFlags)
			{
			case Flags::E_Merchant:
				{
					OpenMerchantShop();
					break;
				}
			case Flags::E_Blacksmith:
				{
					OpenBlacksmithShop();
					break;
				}
			case Flags::E_Tailor:
				{
					OpenTailorShop();
					break;
				}
			case Flags::E_Alchemist:
				{
					AlchemistDrop();
					break;
				}
			default:
				{
					break;
				}
			}
		}

		UE_LOG(LogTemp, Warning, TEXT("Conversation GO"));

	}


	//UE_LOG(LogTemp, Warning, TEXT("Interact Pressed"));
}

FString AFFCCCharacter::GetTargetName() const
{
	return InteractTargetName;
}

FString AFFCCCharacter::GetTargetSentence() const
{
	return InteractTargetCurrentSentence;
}

bool AFFCCCharacter::ShouldShowChat() const
{
	return bShowChat;
}

void AFFCCCharacter::OpenMerchantShop()
{
	MerchantHierarchy++;
	bShowMerchantShop = true;
	bInAShop = true;
	UE_LOG(LogTemp, Warning, TEXT("OpenMerchantShop"));
	UE_LOG(LogTemp, Warning, TEXT("OpenMerchantShop: %s"), bShowMerchantShop ? TEXT("True") : TEXT("False"));
	UE_LOG(LogTemp, Warning, TEXT("OpenMerchantShop: %s"), bInAShop ? TEXT("True") : TEXT("False"));
}

void AFFCCCharacter::OpenTailorShop()
{
	bShowTailorShop = true;
	bInAShop = true;
}

void AFFCCCharacter::OpenBlacksmithShop()
{
	BlacksmithHierarchy++;
	bShowBlacksmithShop = true;
	bInAShop = true;
}

void AFFCCCharacter::AlchemistDrop()
{

}

int AFFCCCharacter::GetInventorySize() const
{
	//return 17;

	// If inventory size not 0 return size
	int Size = InventoryData ? InventoryData->GetSize() : 0;
	return Size; // How much that could be displayed at once
}

void AFFCCCharacter::ShopUp()
{
	if (!bInAShop) return;
	if (bShowAreYouSurePrompt)
	{
		AreYouSureIndex--;
		if (AreYouSureIndex < 0)
		{
			AreYouSureIndex = MaxShopItemIndex - 1;
		}
		return;
	}
	ShopItemIndex--;

	if (ShopItemIndex < 0)
	{
		// Check to see if we should scroll for more ivnentory space
		// Check if there are enough elements to scroll
		if (bMenuScroll && GetInventorySize() > MaxShopItemIndex)
		{
			// Stay at bottom index
			ShopItemIndex = 0;
			// Push Elements Down
			int TEMPInvSize = GetInventorySize();
			//IndexForTopElementInPlayersInventory <= 0 ? IndexForTopElementInPlayersInventory = TEMPInvSize : IndexForTopElementInPlayersInventory -= 1;
			//IndexForTopElementInPlayersInventory = TEMPInvSize - 1;
			IndexForTopElementInPlayersInventory -= 1;
			if (IndexForTopElementInPlayersInventory < 0)
			{
				IndexForTopElementInPlayersInventory = TEMPInvSize - 1;
			}
		}
		else
		{
			// Snap to Bottom
			// IF YOU DONT HAVE ENOUGH ITEMS TO COVER ONE SCREEN
			if (GetInventorySize() <= MaxShopItemIndex && bShowPlayerStock)
			{
				// If you have nothing in your inventory prevent going up
				if (GetInventorySize() <= 0)
				{
					ShopItemIndex = 0;
					return;
				}
				// Cursor goes to bottom
				ShopItemIndex = GetInventorySize() - 1;
				return;
			}
			ShopItemIndex = MaxShopItemIndex - 1;

			//IndexForTopElementInPlayersInventory = 0;
		}
	}
}

void AFFCCCharacter::ShopDown()
{
	if (!bInAShop) return;

	if (bShowAreYouSurePrompt)
	{
		AreYouSureIndex++;
		if (AreYouSureIndex >= 2)
		{
			AreYouSureIndex = 0;
		}
		return;
	}
	ShopItemIndex++;

	// IF YOU DONT HAVE ENOUGH ITEMS TO COVER ONE SCREEN

	int BottomIndex = GetInventorySize() <= MaxShopItemIndex ? GetInventorySize() - 1 : MaxShopItemIndex - 1;

		if (ShopItemIndex >= MaxShopItemIndex)
		{
			if (bMenuScroll && GetInventorySize() > MaxShopItemIndex)
			{
				// Stay at top index
				ShopItemIndex = MaxShopItemIndex - 1;
				// Push Elements Up
				int TEMPInvSize = GetInventorySize();
				//int BotIndex = IndexForTopElementInPlayersInventory > (MaxShopItemIndex - 1) ? IndexForTopElementInPlayersInventory - (MaxShopItemIndex - 1) : IndexForTopElementInPlayersInventory + (MaxShopItemIndex - 1);
				//IndexForTopElementInPlayersInventory >= TEMPInvSize ? IndexForTopElementInPlayersInventory = 0 : IndexForTopElementInPlayersInventory += 1;

				IndexForTopElementInPlayersInventory += 1;
				if (IndexForTopElementInPlayersInventory >= TEMPInvSize)
				{
					IndexForTopElementInPlayersInventory = 0;
				}

				return;

			}
			else
			{
				// Snap to Top
				ShopItemIndex = 0;
				return;
				//IndexForTopElementInPlayersInventory = 0;
			}
		}
		else if (ShopItemIndex > BottomIndex && bShowPlayerStock)
		{
			if (bMenuScroll && GetInventorySize() > MaxShopItemIndex)
			{
				// Stay at top index
				ShopItemIndex = MaxShopItemIndex - 1;
				// Push Elements Up
				int TEMPInvSize = GetInventorySize();
				//int BotIndex = IndexForTopElementInPlayersInventory > (MaxShopItemIndex - 1) ? IndexForTopElementInPlayersInventory - (MaxShopItemIndex - 1) : IndexForTopElementInPlayersInventory + (MaxShopItemIndex - 1);
				//IndexForTopElementInPlayersInventory >= TEMPInvSize ? IndexForTopElementInPlayersInventory = 0 : IndexForTopElementInPlayersInventory += 1;

				IndexForTopElementInPlayersInventory += 1;
				if (IndexForTopElementInPlayersInventory >= TEMPInvSize)
				{
					IndexForTopElementInPlayersInventory = 0;
				}
			}
			else
			{
				ShopItemIndex = 0;
			}
		}
		//else if (bShowAreYouSurePrompt)
		//{
		//	if (ShopItemIndex >= 2)
		//	{
		//		ShopItemIndex = 0;
		//	}
		//	//ShopItemIndex = 1 - ShopItemIndex;
		//	//ShopItemIndex = ShopItemIndex == 0 ? ShopItemIndex = 1 : ShopItemIndex = 0;
		//}
	




}

int AFFCCCharacter::GetMaxShopIndex() const
{
	switch (MerchantLevel)
	{
	case 1:
	{
		return 7;
	}
	case 2:
	{
		return 12;
	}
	case 3:
	{
		return 15;
	}
	case 4:
	{
		return 17;
	}
	default:
		return 7;
	}
}

void AFFCCCharacter::ShopSelect()
{
	if (!bInAShop) return;

	UE_LOG(LogTemp, Warning, TEXT("ShopSelect"));

	if (bShowPlayerStock)
	{
		UE_LOG(LogTemp, Warning, TEXT("InSellMenu"));
		// If in merchant shop
		// Menu scroll basically means you're selling items
		if (bMenuScroll)
		{
			// bring up yes or no
			if (!bShowAreYouSurePrompt)
			{
				// Dont bring up menu if you have no items
				if (GetInventorySize() <= 0) return;

				bShowAreYouSurePrompt = true;
				MaxShopItemIndex = 2; // Are you sure - Yes or No
				MerchantHierarchy++;
				UE_LOG(LogTemp, Warning, TEXT("GoTo AreYouSure"));
				return;
			}
			else if (bShowAreYouSurePrompt)
			{
				if (AreYouSureIndex == 0)
				{
					// Sell
					if (!InventoryData) return;
					UE_LOG(LogTemp, Warning, TEXT("BEFORE - Inventory Num: %d"), InventoryData->GetSize());
					int SellPrice = InventoryData->RemoveItemAt(ShopItemIndex); // Put this in a function later on - SELL Logic
																  // TODO: Add money to pocket
					UE_LOG(LogTemp, Warning, TEXT("Removing Element: %d"), ShopItemIndex);
					UE_LOG(LogTemp, Warning, TEXT("AFTER - Inventory Num: %d"), InventoryData->GetSize());
					// Prevents Row Highlight Overflow
					ShopItemIndex = ShopItemIndex - 1;
					if (ShopItemIndex < 0) ShopItemIndex = 0;
					// Add To money
					GilCount += SellPrice;
				}
				else
				{
					// Dont Sell
				}
				// Close Menu
				CloseMerchantShop();
				return;
			}

		}
	}

	if (bShowMerchantStock)
	{
		// bring up yes or no
		if (!bShowAreYouSurePrompt)
		{
			// Dont bring up menu if you have no items
			//if (GetInventorySize() <= 0) return;

			bShowAreYouSurePrompt = true;
			MaxShopItemIndex = 2; // Are you sure - Yes or No
			MerchantHierarchy++;
			UE_LOG(LogTemp, Warning, TEXT("GoTo AreYouSure"));
			return;
		}
		else if (bShowAreYouSurePrompt)
		{
			if (AreYouSureIndex == 0)
			{
				// Buy
				if (!CurrentShopData) return;
				int BuyPrice = CurrentShopData->GetBuyValueAt(ShopItemIndex);
					//CurrentShopData->GetShopData()[ShopItemIndex].ItemBuyPrice;		 // Put this in a function later on - SELL Logic
								// TODO: Add money to pocket
				if (BuyPrice != -1 && BuyPrice <= GilCount)
				{
					// Can be purchased
					GilCount -= BuyPrice;
					InventoryData->AddItem(CurrentShopData->GetItemDataAt(ShopItemIndex)); // This could potentially need checks against FItemData Def Const
				}
				// Add To money
			//	GilCount += SellPrice;
			}
			else
			{
				// Dont Buy
			}
			// Close Menu
			CloseMerchantShop();
			return;
		}
	}

	if (bShowMerchantShop)
	{
		UE_LOG(LogTemp, Warning, TEXT("ShowMerchantShop"));

		if (ShopItemIndex == 0)
		{
			// Buy
			bShowMerchantShop = false;
			bShowMerchantStock = true;
			MaxShopItemIndex = GetMaxShopIndex(); // Change this later on for unique merchants
			MerchantHierarchy++;
			bMenuScroll = false;
			CachedBuySellIndex = 0;
			UE_LOG(LogTemp, Warning, TEXT("GoTo BuyMenu"));

		}
		else if (ShopItemIndex == 1)
		{
			// Sell
			bShowMerchantShop = false;
			bShowPlayerStock = true;
			MaxShopItemIndex = 17; // MAX ITEMS ON SCREEN
			ShopItemIndex = 0;
			MerchantHierarchy++;
			bMenuScroll = true;
			CachedBuySellIndex = 1;
			UE_LOG(LogTemp, Warning, TEXT("GoTo SellMenu"));

		}
	}
	else if (bShowBlacksmithShop)
	{
		UE_LOG(LogTemp, Warning, TEXT("ShowBlacksmithShop"));

		if (ShopItemIndex == 0)
		{
			// Craft
			bShowBlacksmithShop = false;
			bShowBlacksmithStock = true;
			//MaxShopItemIndex = GetMaxShopIndex(); // Change this later on for unique merchants
			BlacksmithHierarchy++;
			//bMenuScroll = false;
			bMenuScroll = true;
			CachedBuySellIndex = 0;
			UE_LOG(LogTemp, Warning, TEXT("GoTo CraftMenu"));

		}
		else if (ShopItemIndex == 1)
		{
			// Sell
			bShowBlacksmithShop = false;
			bShowPlayerStock = true; // Need to change this to only show recipes
			MaxShopItemIndex = 17; // MAX ITEMS ON SCREEN
			ShopItemIndex = 0;
			BlacksmithHierarchy++;
			bMenuScroll = true;
			CachedBuySellIndex = 1;
			UE_LOG(LogTemp, Warning, TEXT("GoTo SellMenu"));

		}
	}
	else if (bShowTailorShop)
	{

	}


}

void AFFCCCharacter::ShopBack()
{
	switch (TradeFlags)
	{
	case Flags::E_Merchant:
		{
			CloseMerchantShop();
			UE_LOG(LogTemp, Warning, TEXT("CloseMerchantShop"));
			break;
		}
	case Flags::E_Blacksmith:
		{
			CloseBlacksmithShop();
			break;
		}
	case Flags::E_Tailor:
		{
			CloseTailorShop();
			break;
		}
	case Flags::E_Alchemist:
		{
			break;
		}
	default:
		{
			break;
		}
	}

}

void AFFCCCharacter::MenuReset()
{
	// Go To Conversation End
	InteractIndexInDialogue = 0;
	InteractTargetName = QMString;
	InteractTargetCurrentSentence = EmptyString;
	// TODO: Hide chat box
	bShowChat = false;

	TradeFlags = Flags::E_Other;
	bShowMerchantShop = false;
	bShowMerchantStock = false;
	bShowBlacksmithShop = false;
	bShowBlacksmithStock = false;
	bShowPlayerStock = false;

	ShopItemIndex = 0;
	MerchantHierarchy = 0;
	BlacksmithHierarchy = 0;
	IndexForTopElementInPlayersInventory = 0;
	bMenuScroll = false;
	CachedBuySellIndex = 0;
	
}

void AFFCCCharacter::CloseMerchantShop()
{
	MerchantHierarchy--;
	if (MerchantHierarchy <= 0)
	{
		InteractIndexInDialogue = 0;
		//TradeFlags = Flags::E_Other;
		bShowMerchantShop = false;
		bShowMerchantStock = false;
		bShowPlayerStock = false;

		bShowChat = false;
		bInAShop = false;

		ShopItemIndex = 0;
		MerchantHierarchy = 0;
		bMenuScroll = false;
		UE_LOG(LogTemp, Warning, TEXT("Back to no menu: %d"), MerchantHierarchy);
	}
	else if (MerchantHierarchy == 1)
	{
		// Menu to choose buying or selling
		//OpenMerchantShop();
		bShowMerchantShop = true; // Show BUY SELL Menu
		bInAShop = true; // Maybe redundant
		bShowMerchantStock = false; // Hide List
		bShowPlayerStock = false;
		//ShopItemIndex = 0; // Change to cached index
		ShopItemIndex = CachedBuySellIndex;
		
		MaxShopItemIndex = 2; // 2 options { BUY , SELL }
		bMenuScroll = false;
	}
	else if (MerchantHierarchy == 2)
	{
		// Buy and Sell menu, so since there is no menu further up this can be blank
		// For the time being - will add a "how many to buy / sell " soon
		bShowAreYouSurePrompt = false;
		AreYouSureIndex = 0;
		MaxShopItemIndex = GetMaxShopIndex(); // hmm
	//	if (ShopItemIndex >= MaxShopItemIndex) ShopItemIndex = ShopItemIndex - 1; // Retain position in inventory, unless you go out of bounds then go one up
	//	if (ShopItemIndex < 0) ShopItemIndex = 0;
		bShowMerchantShop = false;
		// menu scroll player stock merchant stock hmm

		// Needs more not sure which bits yet

		//bMenuScroll = true; // If selling
	}
	else if (MerchantHierarchy == 3)
	{
		// Are yous ure prompt - no further menu so can be blank
	}
}

void AFFCCCharacter::CloseBlacksmithShop()
{
	BlacksmithHierarchy--;
	if (BlacksmithHierarchy <= 0)
	{
		InteractIndexInDialogue = 0;
		//TradeFlags = Flags::E_Other;
		bShowBlacksmithShop = false;
		bShowBlacksmithStock = false;
		bShowPlayerStock = false;

		bShowChat = false;
		bInAShop = false;

		ShopItemIndex = 0;
		BlacksmithHierarchy = 0;
		bMenuScroll = false;
		UE_LOG(LogTemp, Warning, TEXT("Back to no menu: %d"), BlacksmithHierarchy);
	}
	else if (BlacksmithHierarchy == 1)
	{
		// Menu to choose crafting or selling
		//OpenMerchantShop();
		bShowBlacksmithShop = true; // Show BUY SELL Menu
		bInAShop = true; // Maybe redundant
		bShowBlacksmithStock = false; // Hide List
		bShowPlayerStock = false;
		//ShopItemIndex = 0; // Change to cached index
		ShopItemIndex = CachedBuySellIndex;

		MaxShopItemIndex = 2; // 2 options { BUY , SELL }
		bMenuScroll = false;
	}
	else if (BlacksmithHierarchy == 2)
	{
		// Craft and Sell menu
		bShowAreYouSurePrompt = false;
		AreYouSureIndex = 0;
		MaxShopItemIndex = GetMaxShopIndex(); // hmm
											  //	if (ShopItemIndex >= MaxShopItemIndex) ShopItemIndex = ShopItemIndex - 1; // Retain position in inventory, unless you go out of bounds then go one up
											  //	if (ShopItemIndex < 0) ShopItemIndex = 0;
		bShowBlacksmithShop = false;
		// menu scroll player stock merchant stock hmm

		// Needs more not sure which bits yet

		//bMenuScroll = true; // If selling
	}
	else if (BlacksmithHierarchy == 3)
	{
		// Are yous ure prompt - no further menu so can be blank
	}
}

void AFFCCCharacter::CloseTailorShop()
{

}

FString AFFCCCharacter::GetItemNameAtIndex(int Index)
{
	FString ReturnValue = FString(TEXT("? ? ? ? "));
	if (!InventoryData) return ReturnValue;
	if (InventoryData->GetSize() == 0) return ReturnValue;
	if(Index > InventoryData->GetSize() - 1) return ReturnValue;
	ReturnValue = InventoryData->GetItemNameAt(Index);
	//if (Index > CurrentSlotsFilled - 1) return ReturnValue;
	////AItem* Temp = new AItem()
	//if (CurrentSlotsFilled == 0) return ReturnValue;
	//if (Inventory[Index] != nullptr)
	//{
	//	ReturnValue = Inventory[Index]->ItemName;
	//}
	return ReturnValue;
}

int AFFCCCharacter::GetItemSellValueAtIndex(int Index)
{
	int ReturnValue = -1;
	if (!InventoryData) return ReturnValue;
	if (InventoryData->GetSize() == 0) return ReturnValue;
	if (Index > InventoryData->GetSize() - 1) return ReturnValue;
	ReturnValue = InventoryData->GetSellValueAt(Index);
	//if (Index > CurrentSlotsFilled - 1) return ReturnValue;
	//if (CurrentSlotsFilled == 0) return ReturnValue;

	//if (Inventory[Index] != nullptr)
	//{
	//	ReturnValue = Inventory[Index]->ItemSellValue;
	//}

	return ReturnValue;
}

int AFFCCCharacter::GetItemBuyValueAtIndex(int Index)
{
	int ReturnValue = -1;
	if (!InventoryData) return ReturnValue;
	if (InventoryData->GetSize() == 0) return ReturnValue;
	if (Index > InventoryData->GetSize() - 1) return ReturnValue;
	ReturnValue = InventoryData->GetBuyValueAt(Index);
	//if (Index > CurrentSlotsFilled - 1) return ReturnValue;
	//if (CurrentSlotsFilled == 0) return ReturnValue;

	//if (Inventory[Index] != nullptr)
	//{
	//	ReturnValue = Inventory[Index]->ItemSellValue;
	//}

	return ReturnValue;
}

UTexture2D* AFFCCCharacter::GetItemIconAtIndex(int Index)
{
	UTexture2D* ReturnValue = InvalidTexture;
	if (!InventoryData) return ReturnValue;
	if (InventoryData->GetSize() == 0) return ReturnValue;
	if (Index > InventoryData->GetSize() - 1) return ReturnValue;
	ReturnValue = InventoryData->GetItemIconAt(Index);
	return ReturnValue != nullptr ? ReturnValue : InvalidTexture;
}

FString AFFCCCharacter::GetMerchNameAtRow(int Row)
{
	FString ReturnValue = "? ? ? ? ";
	if (!CurrentShopData) return ReturnValue;
	if (CurrentShopData->GetShopData().Num() == 0) return ReturnValue;
	if (Row > CurrentShopData->GetShopData().Num() - 1) return ReturnValue;
	ReturnValue = CurrentShopData->GetNameAt(Row);
	//ReturnValue = CurrentShopData->GetShopData()[Row].ItemName;
	return ReturnValue;
	//if (CurrentShopData && CurrentShopData->GetItemDataAtIndex(Row))
	//{

	//}
	//if (CurrentShopData == nullptr) return "";
	//if (Row > CurrentShopData->GetShopData().Num() - 1) return "";

	//return CurrentShopData->GetShopData()[Row].ItemName;
}

int AFFCCCharacter::GetMerchBuyAtRow(int Row)
{
	int ReturnValue = 99999;
	if (!CurrentShopData) return ReturnValue;
	if (CurrentShopData->GetShopData().Num() == 0) return ReturnValue;
	if (Row > CurrentShopData->GetShopData().Num() - 1) return ReturnValue;
	ReturnValue = CurrentShopData->GetBuyValueAt(Row);
//	ReturnValue = CurrentShopData->GetShopData()[Row].ItemBuyPrice;
	return ReturnValue;
	//if (CurrentShopData == nullptr) return 0;
	//if (Row > CurrentShopData->GetShopData().Num() - 1) return 0;
	//return CurrentShopData->GetShopData()[Row].ItemBuyPrice;
}

int AFFCCCharacter::GetMerchSellAtRow(int Row)
{
	int ReturnValue = 99999;
	if (!CurrentShopData) return ReturnValue;
	if (CurrentShopData->GetShopData().Num() == 0) return ReturnValue;
	if (Row > CurrentShopData->GetShopData().Num() - 1) return ReturnValue;
	ReturnValue = CurrentShopData->GetSellValueAt(Row);
	//ReturnValue = CurrentShopData->GetShopData()[Row].ItemSellPrice;
	return ReturnValue;
	//if (CurrentShopData == nullptr) return 0;

	//if (Row > CurrentShopData->GetShopData().Num() - 1) return 0;
	//return CurrentShopData->GetShopData()[Row].ItemSellPrice;
}

//void AFFCCCharacter::DoAsyncLoad()
//{
	//UE_LOG(LogTemp, Warning, TEXT("Init Ran"));
	//UObject* NewTrack = AudioAssetToLoad.ResolveObject(); 	// Creates a pointer to store the loaded object
	//USoundWave* Track = Cast<USoundWave>(NewTrack);
	//if (Track != nullptr && AudioComponentA != nullptr)
	//{
	//	CurrentMaxTimeInTrack = Track->GetDuration();
	//	AudioComponentA->SetSound(Track);
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Audio Component or Track NULL : DoAsyncInitialise"));
	//}
//}

UTexture2D* AFFCCCharacter::GetMerchIconAtRow(int Row)
{
	UTexture2D* ReturnValue = InvalidTexture;
	if (!CurrentShopData) return ReturnValue;
	if (CurrentShopData->GetShopData().Num() == 0) return ReturnValue;
	if (Row > CurrentShopData->GetShopData().Num() - 1) return ReturnValue;
	ReturnValue = CurrentShopData->GetIconAt(Row);
	//if (ReturnValue.IsPending())
	//{
		//TArray<FAssetData> AssetDatas;
		//UObjectLibrary Lib;
		//Lib.GetAssetDataList(AssetDatas);
		
		//TArray<FStringAssetReference> ImageToLoad;
		//FStreamableManager& Loader = AssetLoader;
		//const FStringAssetReference& Ref = ReturnValue.ToStringReference();
		//Loader.RequestAsyncLoad(ImageToLoad, FStreamableDelegate::CreateUObject(this, &AFFCCCharacter::DoAsyncLoad));
		//TArray<FAudio> Audios = AudioDataBase->GetAudios();
		//AudioAssetToLoad = Audios[Index].AudioResource.ToStringReference();
		//AudioToLoad.AddUnique(AudioAssetToLoad);
		//Loader.RequestAsyncLoad(AudioToLoad, FStreamableDelegate::CreateUObject(this, &AAudioManager::DoAsyncInitialise));


		//ObjectLibrary->GetAssetDataList(AssetDatas);

		//for (int32 i = 0; i < AssetDatas.Num(); ++i)
		//{
		//	FAssetData& AssetData = AssetDatas[i];

		//	const FString* FoundTypeNameString = AssetData.TagsAndValues.Find(GET_MEMBER_NAME_CHECKED(UAssetObject, TypeName));

		//	if (FoundTypeNameString && FoundTypeNameString->Contains(TEXT("FooType")))
		//	{
		//		return AssetData;
		//	}
		//}
		//FStreamableManager& AssetMgr = GetStreamable();
	//}
	//ReturnValue = CurrentShopData->GetShopData()[Row].ItemIcon;
	return ReturnValue != nullptr ? ReturnValue : InvalidTexture;

	//if (Row > CurrentShopData->GetShopData().Num() - 1) return nullptr;
	//return CurrentShopData->GetShopData()[Row].ItemIcon;
}