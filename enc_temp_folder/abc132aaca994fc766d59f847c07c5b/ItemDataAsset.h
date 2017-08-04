// Fan Made FFCC - July 28th 2017

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FFCC/Items/ItemTypeEnum.h"
#include "ItemDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class FFCC_API UItemDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
private:
	/** Core of the database - a bunch of dialogue structs*/
	UPROPERTY(EditAnywhere, Category = "Item Data", meta = (Tooltip = "Item Storage"))
		FItemData ItemData;

public:

	FORCEINLINE FItemData GetItemData() { return ItemData; }
	
	
};
