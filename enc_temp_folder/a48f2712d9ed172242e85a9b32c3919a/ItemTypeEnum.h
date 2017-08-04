// Fan Made FFCC - July 28th 2017

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Classes/Engine/Texture2D.h"
#include "Classes/Engine/DataTable.h"
#include "ItemTypeEnum.generated.h"

UENUM(BlueprintType)
enum class EMaterialType : uint8
{
	E_Alloy,
	E_AncientPotion,
	E_AncientSword,
	E_AngelsTear,
	E_BlueSilk,
	E_Bronze,
	E_BronzeShard,
	E_CerberusFang,
	E_ChillyGel,
	E_ChimeraHorn,
	E_CockatriceScale,
	E_CoeurlsWhisker,
	E_CrystalBall,
	E_CursedCrook,
	E_DarkSphere,
	E_DesertFang,
	E_DevilsClaw,
	E_DiamondOre,
	E_DragonFang,
	E_DweomerSpore,
	E_EtherealOrb,
	E_FaeriesTear,
	E_FiendsClaw,
	E_Gear,
	E_GigasClaw,
	E_Gold,
	E_GreenSphere,
	E_GriffinsWing,
	E_HardShell,
	E_HeavenlyDust,
	E_HolyWater,
	E_Iron,
	E_IronShard,
	E_Jade,
	E_JaggedScythe,
	E_KingsScale,
	E_LordsRobe,
	E_MagmaRock,
	E_MalboroSeed,
	E_Mythril,
	E_Needle,
	E_OgreFang,
	E_OrcBelt,
	E_Orichalcum,
	E_PressedFlower,
	E_RedEye,
	E_Remedy,
	E_Ruby,
	E_ShinyShard,
	E_Silver,
	E_Thunderball,
	E_TinyCrystal,
	E_ToadOil,
	E_Ultimate,
	E_WhiteSilk,
	E_WindCrystal,
	E_WormAntenna,
	E_YellowFeather,
	E_ZusBeak,
	E_MAX
};

UENUM(BlueprintType)
enum class EFoodType : uint8
{
	E_Meat,
	E_Fish,
	E_StripedApple,
	E_CherryCluster,
	E_StarCarrot,
	E_RoundCorn,
	E_RainbowGrapes,
	E_BannockBread,
	E_Milk,
	E_SpringWater,
	E_StrangeLiquid,
	E_Wheat,
	E_Flour,
	E_MAX
};

UENUM(BlueprintType)
enum class ESeedType : uint8
{
	E_FruitSeed,
	E_VegetableSeed,
	E_StrangeSeed,
	E_WheatSeed,
	E_FlowerSeed,
	E_MAX
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	E_Seed,
	E_Food,
	E_Material
};

USTRUCT()
struct FItemData : public FTableRowBase
{

	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Item", meta = (ToolTip = "The Type"))
		int LookUpIndex;

	UPROPERTY(EditAnywhere, Category = "Item", meta = (ToolTip = "The Type"))
		EItemType ItemType;

	UPROPERTY(EditAnywhere, Category = "Item", meta = (ToolTip = "The Seed"))
		ESeedType SeedType;

	UPROPERTY(EditAnywhere, Category = "Item", meta = (ToolTip = "The Food"))
		EFoodType FoodType;

	UPROPERTY(EditAnywhere, Category = "Item", meta = (ToolTip = "The Material"))
		EMaterialType MaterialType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
		FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
		int ItemSellValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
		int ItemBuyValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
		TAssetPtr<UTexture2D> AchievementIcon;

	//http://en.cppreference.com/w/cpp/language/reference_initialization
	//operator FItemData&() { FItemData(); }

	/** Default Constructor*/
	FItemData()
	{
		ItemType = EItemType::E_Material;
		SeedType = ESeedType::E_MAX;
		FoodType = EFoodType::E_MAX;
		MaterialType = EMaterialType::E_MAX;
		ItemName = FString(TEXT("? ? ? ?"));
		ItemSellValue = 0;
		ItemBuyValue = 0;
		LookUpIndex = 0;
	}

	FItemData(const FItemData& Other)
	{
		ItemType = Other.ItemType;
		SeedType = Other.SeedType;
		FoodType = Other.FoodType;
		MaterialType = Other.MaterialType;
		ItemName = Other.ItemName;
		ItemSellValue = Other.ItemBuyValue;
		ItemBuyValue = Other.ItemSellValue;
		LookUpIndex = 0;
	}

	FItemData(ESeedType _SeedType, const FString& _Name, int _Buy, int _Sell)
	{
		ItemType = EItemType::E_Seed;
		SeedType = _SeedType;
		FoodType = EFoodType::E_MAX;
		MaterialType = EMaterialType::E_MAX;
		ItemName = _Name;
		ItemBuyValue = _Buy;
		ItemSellValue = _Sell;
		LookUpIndex = 0;
	}

	FItemData(EFoodType _FoodType, const FString& _Name, int _Buy, int _Sell)
	{
		ItemType = EItemType::E_Food;
		SeedType = ESeedType::E_MAX;
		FoodType = _FoodType;
		MaterialType = EMaterialType::E_MAX;
		ItemName = _Name;
		ItemBuyValue = _Buy;
		ItemSellValue = _Sell;
		LookUpIndex = 0;
	}

	FItemData(EMaterialType _MaterialType, const FString& _Name, int _Buy, int _Sell)
	{
		ItemType = EItemType::E_Material;
		SeedType = ESeedType::E_MAX;
		FoodType = EFoodType::E_MAX;
		MaterialType = _MaterialType;
		ItemName = _Name;
		ItemBuyValue = _Buy;
		ItemSellValue = _Sell;
		LookUpIndex = 0;
	}
};
/**
 * 
 */
UCLASS()
class FFCC_API UItemTypeEnum : public UObject
{
	GENERATED_BODY()
	
public:

	static void InitSeed(const ESeedType Type, FString& String, int& Buy, int& Sell);
	static void InitFood(const EFoodType Type, FString& String, int& Buy, int& Sell);
	static void InitMaterial(const EMaterialType Type, FString& String, int& Buy, int& Sell);

	
	
};
