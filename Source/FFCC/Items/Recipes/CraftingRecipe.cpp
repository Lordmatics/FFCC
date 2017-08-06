// Fan Made FFCC - July 28th 2017

#include "CraftingRecipe.h"




// Sets default values
ACraftingRecipe::ACraftingRecipe()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

void ACraftingRecipe::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//UItemTypeEnum::InitFood(FoodType, ItemData.ItemName, ItemData.ItemBuyValue, ItemData.ItemSellValue);
}

// Called when the game starts or when spawned
void ACraftingRecipe::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACraftingRecipe::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACraftingRecipe::OnPickedUp()
{
	Super::OnPickedUp();

}