// Fan Made FFCC - July 28th 2017

#pragma once

#include "CoreMinimal.h"
#include "NPC/NPC.h"
#include "NPCMerchant.generated.h"

/**
 * 
 */
UCLASS()
class FFCC_API ANPCMerchant : public ANPC
{
	GENERATED_BODY()
	
private:

protected:

	UPROPERTY(EditAnywhere, Category = "Shop")
		class UMerchShopDataAsset* MerchantShopData;
public:
	
	virtual class UDataAsset* GetData() override;
	
};
