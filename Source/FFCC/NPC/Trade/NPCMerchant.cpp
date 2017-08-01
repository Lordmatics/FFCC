// Fan Made FFCC - July 28th 2017

#include "NPCMerchant.h"
#include "FFCC/DataAssets/Merchant/Home/MerchShopDataAsset.h"

UDataAsset* ANPCMerchant::GetData()
{
	return MerchantShopData ? MerchantShopData : Super::GetData();
}



