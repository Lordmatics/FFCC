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
	
	int GetSize() const;

	int GetBuyValueAt(int Index);
	int GetSellValueAt(int Index);
	FString GetItemNameAt(int Index);
	TAssetPtr<UTexture2D> GetItemIconAt(int Index);

	void AddItem(const FItemData& ItemName);

	void RemoveItemByName(const FString& Name);

	void ClearInventory();
	
};
