// Fan Made FFCC - July 28th 2017

#include "Materials.h"

// Sets default values
AMaterials::AMaterials()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

void AMaterials::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//UItemTypeEnum::InitMaterial(MaterialType, ItemData.ItemName, ItemData.ItemBuyValue, ItemData.ItemSellValue);
}

// Called when the game starts or when spawned
void AMaterials::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMaterials::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMaterials::OnPickedUp()
{
	Super::OnPickedUp();
}

