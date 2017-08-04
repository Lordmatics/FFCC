// Fan Made FFCC - July 28th 2017

#include "ShopComponent.h"
//#include "FFCC/Items/Item.h"
//#include "FFCC/DataAssets/Merchant/Home/MerchShopDataAsset.h"
//#include "FFCC/DataAssets/Item/InventoryDataAsset.h"
//#include "FFCC/FFCCGameMode.h"
//#include "Classes/Engine/World.h"
//// Sets default values for this component's properties
UShopComponent::UShopComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//MaxInventorySize = 32;
	//CurrentSlotsFilled = 0;
	//// ...

	//CurrentStock = nullptr;
	//UWorld* const World = GetWorld();
	//if (World)
	//{
	//	GameMode = Cast<AFFCCGameMode>(World->GetAuthGameMode());
	//}
	//else
	//{
	//	GameMode = nullptr;
	//}
}


// Called when the game starts
void UShopComponent::BeginPlay()
{
	Super::BeginPlay();

	//UWorld* const World = GetWorld();
	//if (World)
	//{
	//	GameMode = Cast<AFFCCGameMode>(World->GetAuthGameMode());
	//}
	//else
	//{
	//	GameMode = nullptr;
	//}

	//for (int i = 0; i < 32; i++)
	//{
	//	Inventory.Add(FItemData());
	//}
	// ...
	
}


// Called every frame
void UShopComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
//
//bool UShopComponent::AddItem(const FString& ItemToAdd)
//{
//	if (CurrentSlotsFilled >= MaxInventorySize) return false;
//	//FItemData Data = FItemData(ItemToAdd);
//	//InventoryDataList->AddItem()
//	//if (GameMode && GameMode->ItemDatabase)
//	//{
//	//	FName RowName = FName(*ItemToAdd);
//	//	FItemData* Data = GameMode->ItemDatabase->FindRow<FItemData>(RowName, ItemToAdd);
//	//	if (Data)
//	//	{
//	//		Inventory.Add(Data);
//	//		CurrentSlotsFilled++;
//	//	}
//	//}
//	//if (!ItemToAdd) return false;
//	//Inventory[CurrentSlotsFilled] = FItemData(ItemToAdd);
//	//Inventory.Add(ItemToAdd);
//	return true;
//}
//
//void UShopComponent::RemoveItem(const FItemData& ItemToRemove)
//{
//	//for (int i = 0; i < CurrentSlotsFilled; i++)
//	//{
//	//	if (Inventory[i].ItemName == ItemToRemove.ItemName)
//	//	{
//	//		Inventory[i] = Inventory[--CurrentSlotsFilled];
//	//		break;
//	//	}
//	//}
//}
//
//int UShopComponent::GetInventorySize() const
//{
//	return CurrentSlotsFilled;
//	//return Inventory.Num() > 0 ? Inventory.Num() : 0;
//}
//
//FString UShopComponent::GetItemNameAtIndex(int Index)
//{
//	FString ReturnValue = "? ? ? ? ";
//	if (Index > CurrentSlotsFilled - 1) return ReturnValue;
//	//AItem* Temp = new AItem()
//	if (CurrentSlotsFilled == 0) return ReturnValue;
//	if (Inventory[Index] != nullptr)
//	{
//		ReturnValue = Inventory[Index]->ItemName;
//	}
//	return ReturnValue;
//}
//
//int UShopComponent::GetItemSellValueAtIndex(int Index)
//{
//	int ReturnValue = 99999;
//	if (Index > CurrentSlotsFilled - 1) return ReturnValue;
//	if (CurrentSlotsFilled == 0) return ReturnValue;
//
//	if (Inventory[Index] != nullptr)
//	{
//		ReturnValue = Inventory[Index]->ItemSellValue;
//	}
//
//	return ReturnValue;
//}
//
//int UShopComponent::GetItemBuyValueAtIndex(int Index)
//{
//	int ReturnValue = 99999;
//
//	if (Index > CurrentSlotsFilled - 1) return ReturnValue;
//	if (CurrentSlotsFilled == 0) return ReturnValue;
//
//	if (Inventory[Index] != nullptr)
//	{
//		ReturnValue = Inventory[Index]->ItemSellValue;
//	}
//
//		return ReturnValue;
//}
//
//FString UShopComponent::GetMerchNameAtRow(int Row)
//{
//	if (CurrentStock == nullptr) return "";
//	if(Row > CurrentStock->GetShopData().Num() - 1) return "";
//
//	return CurrentStock->GetShopData()[Row].ItemName;
//}
//
//int UShopComponent::GetMerchBuyAtRow(int Row)
//{
//	if (CurrentStock == nullptr) return 0;
//	if (Row > CurrentStock->GetShopData().Num() - 1) return 0;
//	return CurrentStock->GetShopData()[Row].ItemBuyPrice;
//}
//
//int UShopComponent::GetMerchSellAtRow(int Row)
//{
//	if (CurrentStock == nullptr) return 0;
//
//	if (Row > CurrentStock->GetShopData().Num() - 1) return 0;
//	return CurrentStock->GetShopData()[Row].ItemSellPrice;
//}
//
//UTexture2D* UShopComponent::GetMerchIconAtRow(int Row)
//{
//	if (CurrentStock == nullptr) return  nullptr;
//
//	if (Row > CurrentStock->GetShopData().Num() - 1) return nullptr;
//	return CurrentStock->GetShopData()[Row].ItemIcon;
//}
//
//void UShopComponent::SetMerchantStock(UMerchShopDataAsset& Data)
//{
//	CurrentStock = &Data;
//}