// Fan Made FFCC - July 28th 2017

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MerchShopDataAsset.generated.h"

USTRUCT()
struct FShopData
{

	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Shop", meta = (ToolTip = "The Item Name"))
		FString ItemName;

	UPROPERTY(EditAnywhere, Category = "Shop", meta = (ToolTip = "The Item BUY"))
		int ItemBuyPrice;

	UPROPERTY(EditAnywhere, Category = "Shop", meta = (ToolTip = "The Item SELL"))
		int ItemSellPrice;

	UPROPERTY(EditAnywhere, Category = "Shop", meta = (ToolTip = "The Item IMAGE"))
		UTexture2D* ItemIcon;

	/** Default Constructor*/
	FShopData()
	{
		ItemName = "";
		ItemBuyPrice = 0;
		ItemSellPrice = 0;
		ItemIcon = nullptr;
	}
};

/**
 * 
 */
UCLASS()
class FFCC_API UMerchShopDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
	
private:
	/** Core of the database - a bunch of dialogue structs*/
	UPROPERTY(EditAnywhere, Category = "Shop Database", meta = (Tooltip = "Shop Storage"))
		TArray<FShopData> MerchantShopList;

public:

	FORCEINLINE TArray<FShopData> GetShopData() const { return MerchantShopList; }
	
};
