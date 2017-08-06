// Fan Made FFCC - July 28th 2017

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FFCC/Items/ItemTypeEnum.h"
#include "BlacksmithShopDataAsset.generated.h"

USTRUCT()
struct FCraftEquipmentData
{

	GENERATED_USTRUCT_BODY()

		//UPROPERTY(EditAnywhere, Category = "Shop", meta = (ToolTip = "The Item Name"))
		//	FString ItemName;

		//UPROPERTY(EditAnywhere, Category = "Shop", meta = (ToolTip = "The Item BUY"))
		//	int ItemBuyPrice;

		//UPROPERTY(EditAnywhere, Category = "Shop", meta = (ToolTip = "The Item SELL"))
		//	int ItemSellPrice;

		//UPROPERTY(EditAnywhere, Category = "Shop", meta = (ToolTip = "The Item IMAGE"))
		//	class UTexture2D* ItemIcon;
	UPROPERTY(EditAnywhere, Category = "Shop", meta = (ToolTip = "The Item Data"))
		EBlacksmithType BlacksmithType;
	
	UPROPERTY(EditAnywhere, Category = "Shop", meta = (ToolTip = "The Item Data"))
		class UItemDataAsset* ItemData;

	/** Default Constructor*/
	FCraftEquipmentData()
	{
		//ItemName = "";
		//ItemBuyPrice = 0;
		//ItemSellPrice = 0;
		//ItemIcon = nullptr;
		BlacksmithType = EBlacksmithType::E_Weapon_Armour;
		ItemData = nullptr;
	}
};
/**
 * 
 */
UCLASS()
class FFCC_API UBlacksmithShopDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
private:
	/** Core of the database - a bunch of dialogue structs*/
	UPROPERTY(EditAnywhere, Category = "Shop Database", meta = (Tooltip = "Shop Storage"))
		TArray<FCraftEquipmentData> BlacksmithShopList;

public:

	FORCEINLINE TArray<FCraftEquipmentData> GetShopData() const { return BlacksmithShopList; }


	class UTexture2D* GetIconAt(int Index);
	FString GetNameAt(int Index);
	int GetSellValueAt(int Index);
	int GetBuyValueAt(int Index);

	//class UTexture2D* GetItemIconAt(int Index);
	class UItemDataAsset* GetItemDataAtIndex(int Index);
	struct FItemData GetItemDataAt(int Index);
	
	
};
