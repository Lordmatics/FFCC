// Fan Made FFCC - July 28th 2017

#include "ShopComponent.h"
#include "FFCC/Items/Item.h"
#include "FFCC/DataAssets/Merchant/Home/MerchShopDataAsset.h"

// Sets default values for this component's properties
UShopComponent::UShopComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	MaxInventorySize = 32;
	CurrentSlotsFilled = 0;
	// ...

	CurrentStock = nullptr;
}


// Called when the game starts
void UShopComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UShopComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UShopComponent::AddItem(AItem* ItemToAdd)
{
	if (Inventory.Num() >= MaxInventorySize) return false;
	if (ItemToAdd == nullptr) return false;
	Inventory.Add(ItemToAdd);
	CurrentSlotsFilled++;
	return true;
}

void UShopComponent::RemoveItem(AItem* ItemToRemove)
{
	if (ItemToRemove == nullptr) return;
	Inventory.Remove(ItemToRemove);
	CurrentSlotsFilled--;
}

FString UShopComponent::GetItemNameAtIndex(int Index)
{
	if (Index > Inventory.Num()) return FString(TEXT(""));
	return Inventory[Index]->ItemName;
}

int UShopComponent::GetItemSellValueAtIndex(int Index)
{
	if (Index > Inventory.Num()) return 99999;
	return Inventory[Index]->ItemSellValue;
}

int UShopComponent::GetItemBuyValueAtIndex(int Index)
{
	if (Index > Inventory.Num()) return 99999;
	return Inventory[Index]->ItemBuyValue;
}

FString UShopComponent::GetMerchNameAtRow(int Row)
{
	if (CurrentStock == nullptr) return FString();
	if(Row > CurrentStock->GetShopData().Num()) return FString();
	return CurrentStock->GetShopData()[Row].ItemName;
}

int UShopComponent::GetMerchBuyAtRow(int Row)
{
	if (CurrentStock == nullptr) return 0;
	if (Row > CurrentStock->GetShopData().Num()) return 0;
	return CurrentStock->GetShopData()[Row].ItemBuyPrice;
}

int UShopComponent::GetMerchSellAtRow(int Row)
{
	if (CurrentStock == nullptr) return 0;

	if (Row > CurrentStock->GetShopData().Num()) return 0;
	return CurrentStock->GetShopData()[Row].ItemSellPrice;
}

UTexture2D* UShopComponent::GetMerchIconAtRow(int Row)
{
	if (CurrentStock == nullptr) return  nullptr;

	if (Row > CurrentStock->GetShopData().Num()) return nullptr;
	return CurrentStock->GetShopData()[Row].ItemIcon;
}

void UShopComponent::SetMerchantStock(UMerchShopDataAsset& Data)
{
	CurrentStock = &Data;
}