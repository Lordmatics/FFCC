// Fan Made FFCC - July 28th 2017

#include "Food.h"

// Sets default values
AFood::AFood()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

void AFood::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//UItemTypeEnum::InitFood(FoodType, ItemData.ItemName, ItemData.ItemBuyValue, ItemData.ItemSellValue);
}

// Called when the game starts or when spawned
void AFood::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AFood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFood::OnPickedUp()
{
	Super::OnPickedUp();

}