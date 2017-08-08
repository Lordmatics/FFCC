// Fan Made FFCC - July 28th 2017

#include "NPCBlacksmith.h"
#include "FFCC/DataAssets/Blacksmith/Home/BlacksmithShopDataAsset.h"

UDataAsset* ANPCBlacksmith::GetData()
{
	return BlacksmithShopData ? BlacksmithShopData : Super::GetData();
}

EBlacksmithType ANPCBlacksmith::GetBlacksmithType() const
{
	return BlacksmithType;
}