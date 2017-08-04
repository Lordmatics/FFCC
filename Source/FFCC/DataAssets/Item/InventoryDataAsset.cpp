// Fan Made FFCC - July 28th 2017

#include "InventoryDataAsset.h"
#include "FFCC/FFCCGameMode.h"
#include "Classes/Engine/World.h"



void UInventoryDataAsset::AddItem(const FItemData& ItemToAdd)
{
	FItemData Data = ItemToAdd;
	InventoryItemData.Add(Data);
}

void UInventoryDataAsset::RemoveItemByName(const FString& Name)
{
	for (int i = 0; i < InventoryItemData.Num(); i++)
	{
		if (InventoryItemData[i].ItemName == Name)
		{
			InventoryItemData.RemoveAt(i);
			break;
		}
	}
}
void UInventoryDataAsset::ClearInventory()
{
	while (InventoryItemData.Num() != 0)
	{
		InventoryItemData.RemoveAt(0);
	}
}