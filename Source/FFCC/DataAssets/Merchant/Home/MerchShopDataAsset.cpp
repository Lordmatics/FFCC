// Fan Made FFCC - July 28th 2017

#include "MerchShopDataAsset.h"
#include "FFCC/DataAssets/Item/ItemDataAsset.h"
#include "FFCC/Items/ItemTypeEnum.h"
#include "Classes/Engine/Texture2D.h"

//UTexture2D* UMerchShopDataAsset::GetItemIconAt(int Index)
//{
//	if (Index < MerchantShopList.Num())
//	{
//		return MerchantShopList[Index].ItemIcon;
//	}
//	return nullptr;
//}

UItemDataAsset* UMerchShopDataAsset::GetItemDataAtIndex(int Index)
{
	if (Index < MerchantShopList.Num() && Index >= 0)
	{
		return MerchantShopList[Index].ItemData;
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

FItemData UMerchShopDataAsset::GetItemDataAt(int Index)
{
	if (Index < MerchantShopList.Num() && Index >= 0)
	{
		if (MerchantShopList[Index].ItemData != nullptr)
		{
			return MerchantShopList[Index].ItemData->GetItemData();
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("VERY BAD VERY BAD GetItemDataAt Returned Default Constructor"));
	return FItemData();
}

UTexture2D* UMerchShopDataAsset::GetIconAt(int Index)
{
	FItemData Data = GetItemDataAt(Index);
	return Data.ItemIcon;
}

FString UMerchShopDataAsset::GetNameAt(int Index) 
{
	FItemData Data = GetItemDataAt(Index);
	return Data.ItemName;
}

int UMerchShopDataAsset::GetSellValueAt(int Index) 
{
	FItemData Data = GetItemDataAt(Index);
	return Data.ItemSellValue;
}

int UMerchShopDataAsset::GetBuyValueAt(int Index) 
{
	FItemData Data = GetItemDataAt(Index);
	return Data.ItemBuyValue;
}