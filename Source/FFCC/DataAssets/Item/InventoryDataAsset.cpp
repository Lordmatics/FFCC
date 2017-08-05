// Fan Made FFCC - July 28th 2017

#include "InventoryDataAsset.h"
#include "FFCC/FFCCGameMode.h"
#include "Classes/Engine/World.h"
#include "Classes/Engine/Texture2D.h"

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

void UInventoryDataAsset::RemoveItemAt(int Index)
{
	if (Index > GetSize() - 1 || Index < 0)
	{
		return;
	}
	if (Index < InventoryItemData.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemRemoved NAME : %s"), *InventoryItemData[Index].ItemName);
		UE_LOG(LogTemp, Warning, TEXT("ItemRemoved TYPE : %d"), (int)InventoryItemData[Index].ItemType);
		UE_LOG(LogTemp, Warning, TEXT("ItemRemoved BUY : %d"), InventoryItemData[Index].ItemBuyValue);
		UE_LOG(LogTemp, Warning, TEXT("ItemRemoved SELL : %d"), InventoryItemData[Index].ItemSellValue);
		InventoryItemData.RemoveAt(Index);
	}
}

void UInventoryDataAsset::ClearInventory()
{
	while (InventoryItemData.Num() != 0)
	{
		InventoryItemData.RemoveAt(0);
	}
}

int UInventoryDataAsset::GetBuyValueAt(int Index)
{
	if (Index > GetSize() - 1 || Index < 0)
	{
		return -1;
	}
	return InventoryItemData[Index].ItemBuyValue;
}

int UInventoryDataAsset::GetSellValueAt(int Index)
{
	if (Index > GetSize() - 1 || Index < 0)
	{
		return -1;
	}
	return InventoryItemData[Index].ItemSellValue;
}

FString UInventoryDataAsset::GetItemNameAt(int Index)
{
	if (Index > GetSize() - 1 || Index < 0)
	{
		return FString(TEXT("? ? ? ?"));
	}
	return InventoryItemData[Index].ItemName;
}

UTexture2D* UInventoryDataAsset::GetItemIconAt(int Index)
{
	if (Index > GetSize() - 1 || Index < 0)
	{
		return nullptr;
	}
	return InventoryItemData[Index].ItemIcon;
}

int UInventoryDataAsset::GetSize() const
{
	return InventoryItemData.Num();
}