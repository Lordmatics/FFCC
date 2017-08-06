// Fan Made FFCC - July 28th 2017

#include "CameraFollow.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "FFCCCharacter.h"
#include "EngineUtils.h"

#include "Engine.h"

// Sets default values
ACameraFollow::ACameraFollow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("MyRoot"));
	Root->SetRelativeRotation(FRotator(0.0f, -40.0f, 0.0f));
	RootComponent = Root;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(Root);

	xOffset = -100.0f;
	yOffset = -300.0f;
	zOffset = 750.0f;

	// YRot - 40.0f;

	InterpSpeed = 2.5f;

	CameraBounds = FCameraBoundaries();
}

// Called when the game starts or when spawned
void ACameraFollow::BeginPlay()
{
	Super::BeginPlay();

	if (UWorld* const World = GetWorld())
	{
		for (TActorIterator<AFFCCCharacter> ActorItr(World); ActorItr; ++ActorItr)
		{
			// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
			TargetToFollow = *ActorItr;
			break;
		}
	}

	if (!TargetToFollow) return;

	//AttachRootComponentToActor(TargetToFollow);

	FVector NewLocation;
	//NewLocation = TargetToFollow->GetActorLocation();
	NewLocation = FVector(xOffset, yOffset, zOffset);
	Camera->SetWorldLocation(NewLocation);


}

// Called every frame
void ACameraFollow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GEngine && TargetToFollow)
	{
		FVector CamPos = GetActorLocation();
		CamPos.Z = 0.0f;
		FVector PlayerPos = TargetToFollow->GetActorLocation();
		PlayerPos.Z = 0.0f;

		GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Red, FString::Printf(TEXT("CamPos: %s"), *CamPos.ToString()));
		GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Red, FString::Printf(TEXT("PlayerPos: %s"), *PlayerPos.ToString()));

		//GEngine->AddOnScreenDebugMessage(-1,DeltaTime,FColor::Red,FString::Printf(TEXT("Distance: %s"), ))
	}

	// Values@

	// if ( 0.0f - -500 >= 500 -> Blend Y from Left to Mid
	// If( 0.0f - 500 <= 500 -> Blend Y from Right to Mid

	// If(Cam.Y - Pla.y >= 500.0f etc
	// If(Cam.x - Pla.x > -900.0f )-> Blend from Bot to Mid
	// If(Cam.x - Pla.x <= -1000.0f ) - > Blend top to mid
	if (!TargetToFollow) return;
	FVector NewLocation = GetActorLocation();
	FVector TargetLocation = NewLocation;
	float CamX = NewLocation.X;
	float PlayerX = TargetToFollow->GetActorLocation().X;

	float CamY = NewLocation.Y;
	float PlayerY = TargetToFollow->GetActorLocation().Y;


	if (CamX - PlayerX >= CameraBounds.Max_X)
	{
		TargetLocation.X = PlayerX - 1000.0f;
	}
	if (CamX - PlayerX <= CameraBounds.Min_X)
	{
		TargetLocation.X = PlayerX - 1000.0f;
	}

	if (CamY - PlayerY <= CameraBounds.Min_Y)
	{
		TargetLocation.Y = PlayerY;
	}

	if (CamY - PlayerY >= CameraBounds.Max_Y)
	{
		TargetLocation.Y = PlayerY;
	}

	NewLocation = FMath::VInterpTo(NewLocation, TargetLocation, DeltaTime, InterpSpeed);
	SetActorLocation(NewLocation);
}

