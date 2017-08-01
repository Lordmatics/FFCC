// Fan Made FFCC - July 28th 2017

#include "Seeds.h"


// Sets default values
ASeeds::ASeeds()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASeeds::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	UItemTypeEnum::InitSeed(SeedType, ItemName, ItemBuyValue, ItemSellValue);

}

// Called when the game starts or when spawned
void ASeeds::BeginPlay()
{
	Super::BeginPlay();
	

}

// Called every frame
void ASeeds::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASeeds::OnPickedUp()
{
	Super::OnPickedUp();

}