// Fan Made FFCC - July 28th 2017

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FFCC/Items/ItemTypeEnum.h"
#include "InventoryDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class FFCC_API UInventoryDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
private:
	/** Core of the database - a bunch of dialogue structs*/
	UPROPERTY(EditAnywhere, Category = "Item Data", meta = (Tooltip = "Item Storage"))
		TArray<FItemData> InventoryItemData;

public:

	FORCEINLINE TArray<FItemData> GetItemDataList() { return InventoryItemData; }
	
	void AddItem(const FItemData& ItemName);

	void RemoveItemByName(const FString& Name);

	void ClearInventory();
	
};
