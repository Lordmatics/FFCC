// Fan Made FFCC - July 28th 2017

#include "MerchShopDataAsset.h"
#include "FFCC/DataAssets/Item/ItemDataAsset.h"
#include "Classes/Engine/Texture2D.h"

UTexture2D* UMerchShopDataAsset::GetItemIconAt(int Index)
{
	if (Index < MerchantShopList.Num())
	{
		return MerchantShopList[Index].ItemIcon;
	}
	return nullptr;
}

UItemDataAsset* UMerchShopDataAsset::GetItemDataAtIndex(int Index)
{
	if (Index < MerchantShopList.Num())
	{
		return MerchantShopList[Index].ItemData;
	}
	return nullptr;
}



