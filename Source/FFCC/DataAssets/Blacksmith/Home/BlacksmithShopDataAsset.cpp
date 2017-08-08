// Fan Made FFCC - July 28th 2017

#include "BlacksmithShopDataAsset.h"
#include "FFCC/DataAssets/Item/ItemDataAsset.h"
#include "Classes/Engine/Texture2D.h"


UItemDataAsset* UBlacksmithShopDataAsset::GetItemDataAtIndex(int Index)
{
	if (Index < BlacksmithShopList.Num() && Index >= 0)
	{
		return BlacksmithShopList[Index].ItemData;
	}
	return nullptr;
}


//int UMerchShopDataAsset::GetBuyValueAt(int Index) const 
//{
//	if (Index < MerchantShopList.Num() && Index >= 0)
//	{
//		return MerchantShopList[Index].ItemBuyPrice;
//	}
//	return -1;
//}

FItemData UBlacksmithShopDataAsset::GetItemDataAt(int Index)
{
	if (Index < BlacksmithShopList.Num() && Index >= 0)
	{
		if (BlacksmithShopList[Index].ItemData != nullptr)
		{
			return BlacksmithShopList[Index].ItemData->GetItemData();
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("VERY BAD VERY BAD GetItemDataAt Returned Default Constructor"));
	return FItemData();
}

UTexture2D* UBlacksmithShopDataAsset::GetIconAt(int Index)
{
	FItemData Data = GetItemDataAt(Index);
	return Data.ItemIcon;
}

FString UBlacksmithShopDataAsset::GetNameAt(int Index)
{
	FItemData Data = GetItemDataAt(Index);
	return Data.ItemName;
}

int UBlacksmithShopDataAsset::GetSellValueAt(int Index)
{
	FItemData Data = GetItemDataAt(Index);
	return Data.ItemSellValue;
}

int UBlacksmithShopDataAsset::GetBuyValueAt(int Index)
{
	FItemData Data = GetItemDataAt(Index);
	return Data.ItemBuyValue;
}

void UBlacksmithShopDataAsset::AddRecipe(const FCraftEquipmentData& CraftData)
{
	//if (BlacksmithShopList != nullptr)
	//{
		FCraftEquipmentData temp = CraftData;
		BlacksmithShopList.Add(temp);
	//}
}

void UBlacksmithShopDataAsset::ClearInventory()
{
	while (BlacksmithShopList.Num() != 0)
	{
		BlacksmithShopList.RemoveAt(0);
	}
}