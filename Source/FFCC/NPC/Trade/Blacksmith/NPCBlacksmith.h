// Fan Made FFCC - July 28th 2017

#pragma once

#include "CoreMinimal.h"
#include "NPC/NPC.h"
#include "Items/ItemTypeEnum.h"
#include "NPCBlacksmith.generated.h"

/**
 * 
 */
UCLASS()
class FFCC_API ANPCBlacksmith : public ANPC
{
	GENERATED_BODY()
	
	
protected:

	UPROPERTY(EditAnywhere, Category = "Shop")
		EBlacksmithType BlacksmithType;

	UPROPERTY(EditAnywhere, Category = "Shop")
		class UBlacksmithShopDataAsset* BlacksmithShopData;
public:

	virtual class UDataAsset* GetData() override;

	EBlacksmithType GetBlacksmithType() const;
	
};
