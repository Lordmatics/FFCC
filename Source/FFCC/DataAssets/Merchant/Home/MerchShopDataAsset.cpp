// Fan Made FFCC - July 28th 2017

#include "MerchShopDataAsset.h"
#include "FFCC/DataAssets/Item/ItemDataAsset.h"

UItemDataAsset* UMerchShopDataAsset::GetItemDataAtIndex(int Index)
{
	if (Index < MerchantShopList.Num())
	{
		return MerchantShopList[Index].ItemData;
	}
	return nullptr;
}



