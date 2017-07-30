// Fan Made FFCC - July 28th 2017

#include "NPCStatsComponent.h"


// Sets default values for this component's properties
UNPCStatsComponent::UNPCStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	NPCStats = FNPCStats();

	// ...
}


// Called when the game starts
void UNPCStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UNPCStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FNPCStats UNPCStatsComponent::GetNPCStats() const
{
	return NPCStats;
}