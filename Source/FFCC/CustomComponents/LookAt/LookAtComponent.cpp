// Fan Made FFCC - July 28th 2017

#include "LookAtComponent.h"


// Sets default values for this component's properties
ULookAtComponent::ULookAtComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void ULookAtComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULookAtComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULookAtComponent::GetRotationToLookAt(const FVector& You, const FVector& Target, FRotator& OutRotation)
{
	FVector Direction = Target - You;
	Direction.Z = 0.0f;
	OutRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
}