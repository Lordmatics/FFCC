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
#include "FFCC/CustomComponents/LookAt/LookAtComponent.h"
#include "FFCC/CustomComponents/Dialogue/DialogueComponent.h"
#include "FFCC/CustomComponents/NPCStats/NPCStatsComponent.h"
#include "FFCC/CustomComponents/Shop/ShopComponent.h"
#include "FFCC/CustomComponents/Pickupables/PickupComponent.h"
#include "FFCC/NPC/NPC.h"
#include "FFCC/DataAssets/Merchant/Home/MerchShopDataAsset.h"
#include "FFCC/Debug/Logs.h"

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

	ShopComponent = CreateDefaultSubobject<UShopComponent>(TEXT("ShopComponent"));
	bShowMerchantStock = false;
	bShowPlayerStock = false;
	MerchantHierarchy = 0;

	LookAtComp = CreateDefaultSubobject<ULookAtComponent>(TEXT("LookAtComponent"));
	MerchantLevel = 1;

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
}

void AFFCCCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AFFCCCharacter::BeginInteract);
	PlayerInputComponent->BindAction("ShopUp", IE_Pressed, this, &AFFCCCharacter::ShopUp);
	PlayerInputComponent->BindAction("ShopDown", IE_Pressed, this, &AFFCCCharacter::ShopDown);
	PlayerInputComponent->BindAction("ShopSelect", IE_Pressed, this, &AFFCCCharacter::ShopSelect);
	PlayerInputComponent->BindAction("ShopBack", IE_Pressed, this, &AFFCCCharacter::ShopBack);

	PlayerInputComponent->BindAction("DebugML", IE_Pressed, this, &AFFCCCharacter::UpgradeMerchantLevel);



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
	CurrentPickupComponent = Cast<UPickupComponent>(OtherActor->GetComponentByClass(UPickupComponent::StaticClass()));
	if (CurrentPickupComponent)
	{

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
	if (NPC)
	{
		// If is a merchant
		UMerchShopDataAsset* MerchData = Cast<UMerchShopDataAsset>(NPC->GetData()); // VTable points to correct version of data
		if (MerchData && ShopComponent)
		{
			// Potential optimise here. Store locally, then push to UMG when enter shop.
			// Maybe improve things since UMG checks per frame
			ShopComponent->SetMerchantStock(*MerchData); // Pass by address for efficiency
		}
	}
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

	CurrentPickupComponent = Cast<UPickupComponent>(OtherActor->GetComponentByClass(UPickupComponent::StaticClass()));
	if (CurrentPickupComponent)
	{
		CurrentPickupComponent = nullptr;
	}
	CurrentTargetActor = nullptr;
	MenuReset();
}

void AFFCCCharacter::BeginInteract()
{
	if (LookAtComp && CurrentTargetActor)
	{
		// TODO: Smooth this out
		FRotator NewRotation;  LookAtComp->GetRotationToLookAt(GetActorLocation(), CurrentTargetActor->GetActorLocation(), NewRotation);
		//FRotator CurRot = GetActorRotation();
		//while (CurRot != NewRotation)
		//{
			//CurRot = FMath::RInterpTo(CurRot, NewRotation, GetWorld()->GetDeltaSeconds(), 5.0f);
			SetActorRotation(NewRotation);
		//}
	}

	if (CurrentLookAtTarget && bInInteractRange)
	{
		UE_LOG(LogTemp, Warning, TEXT("Target now looking at player"));
		CurrentLookAtTarget->SetLookingAtTarget(this);
		CurrentLookAtTarget->SetLookingAtTarget(true);
	}

	if (CurrentPickupComponent)
	{
		// Play pickup animation
		// Wait for anim to be nearly finished
		// Kill target
		if (CurrentPickupComponent->OnPickedUp.IsBound())
		{
			CurrentPickupComponent->OnPickedUp.Broadcast(); // consider add to inventory here?
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
	bShowBlacksmithShop = true;
	bInAShop = true;
}

void AFFCCCharacter::AlchemistDrop()
{

}

void AFFCCCharacter::ShopUp()
{
	if (!bInAShop) return;
	ShopItemIndex--;
	if (ShopItemIndex < 0)
	{
		ShopItemIndex = MaxShopItemIndex - 1;
	}
}

void AFFCCCharacter::ShopDown()
{
	if (!bInAShop) return;

	ShopItemIndex++;
	if (ShopItemIndex >= MaxShopItemIndex)
	{
		ShopItemIndex = 0;
	}
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

	if (bShowMerchantShop)
	{
		if (ShopItemIndex == 0)
		{
			// Buy
			bShowMerchantShop = false;
			bShowMerchantStock = true;
			MaxShopItemIndex = GetMaxShopIndex();
			MerchantHierarchy++;
		}
		else if (ShopItemIndex == 1)
		{
			// Sell
			bShowMerchantShop = false;
			bShowPlayerStock = true;
			MerchantHierarchy++;
		}
	}
	else if (bShowBlacksmithShop)
	{

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

	ShopItemIndex = 0;
	MerchantHierarchy = 0;
	
}

void AFFCCCharacter::CloseMerchantShop()
{
	MerchantHierarchy--;
	if (MerchantHierarchy == 0)
	{
		InteractIndexInDialogue = 0;
		//TradeFlags = Flags::E_Other;
		bShowMerchantShop = false;
		bShowMerchantStock = false;
		bShowChat = false;
		bInAShop = false;

		ShopItemIndex = 0;
		MerchantHierarchy = 0;
		UE_LOG(LogTemp, Warning, TEXT("Back to no menu: %d"), MerchantHierarchy);
	}
	else if (MerchantHierarchy == 1)
	{
		// Menu to choose buying or selling
		//OpenMerchantShop();
		bShowMerchantShop = true; // Show BUY SELL Menu
		bInAShop = true; // Maybe redundant
		bShowMerchantStock = false; // Hide List
		ShopItemIndex = 0;
		MaxShopItemIndex = 2; // 2 options { BUY , SELL }
	}
	else if (MerchantHierarchy == 2)
	{
		// Buy and Sell menu, so since there is no menu further up this can be blank
	}
}

void AFFCCCharacter::CloseBlacksmithShop()
{

}

void AFFCCCharacter::CloseTailorShop()
{

}

