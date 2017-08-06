// Fan Made FFCC - July 28th 2017

#include "NPC.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "FFCC/CustomComponents/Dialogue/DialogueComponent.h"
#include "FFCC/CustomComponents/LookAt/LookAtComponent.h"
#include "FFCC/CustomComponents/NPCStats/NPCStatsComponent.h"
#include "Classes/Engine/DataAsset.h"

// Sets default values
ANPC::ANPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->SetCollisionProfileName(FName(TEXT("ShopKeep")));

	DialogueComp = CreateDefaultSubobject<UDialogueComponent>(TEXT("DialogueComponent"));
	LookAtComp = CreateDefaultSubobject<ULookAtComponent>(TEXT("LookAtComponent"));
	NPCStatsComp = CreateDefaultSubobject<UNPCStatsComponent>(TEXT("NPCStatsComponent"));

}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LookAtTarget(DeltaTime);

}

// Called to bind functionality to input
void ANPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANPC::LookAtTarget(float DeltaTime)
{
	if (LookAtComp)
	{
		if (LookAtComp->GetLookAtTarget())
		{
			if (LookAtComp->IsLookingAtTarget())
			{
				FRotator MyRot = GetActorRotation();
				FRotator NewRot; LookAtComp->GetRotationToLookAt(GetActorLocation(), LookAtComp->GetLookAtTarget()->GetActorLocation(), NewRot);
				MyRot = FMath::RInterpTo(MyRot, NewRot, DeltaTime, InterpSpeed);
				SetActorRotation(MyRot, ETeleportType::TeleportPhysics);
			}
		}
	}
}

UDataAsset* ANPC::GetData()
{
	return nullptr;
}