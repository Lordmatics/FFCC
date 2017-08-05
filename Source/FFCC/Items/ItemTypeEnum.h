// Fan Made FFCC - July 28th 2017

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Classes/Engine/Texture2D.h"
#include "Classes/Engine/DataTable.h"
#include "ItemTypeEnum.generated.h"

UENUM(BlueprintType)
enum class EWeaponScrolls : uint8
{
	E_CelestialWeapon,
	E_DarkWeapon,
	E_GreatestWeapon,
	E_HerosWeapon,
	E_LegendaryWeapon,
	E_LunarWeapon,
	E_MastersWeapon,
	E_MightyWeapon,
	E_NovicesWeapon,
	E_ValiantsWeapon,
	E_VictoriousWeapon,
	E_WarriorsWeapon,
	E_MAX
};

UENUM(BlueprintType)
enum class EArmourScrolls : uint8
{
	E_BronzeArmour,
	E_DiamondArmour,
	E_EarthArmour,
	E_EternalArmour,
	E_FlameArmour,
	E_FrostArmour,
	E_GoldArmour,
	E_HolyArmour,
	E_IronArmour,
	E_LightningArmour,
	E_MythrilArmour,
	E_PureArmour,
	E_RadiantArmour,
	E_TimeArmour,
	E_MAX
};

UENUM(BlueprintType)
enum class EShields : uint8
{
	E_DiamondShield,
	E_FlameShield,
	E_FrostShield,
	E_HolyShield,
	E_IronShield,
	E_LegendaryShield,
	E_LightningShield,
	E_MagicShield,
	E_MythrilShield,
	E_MAX
};

UENUM(BlueprintType)
enum class EGloves : uint8
{
	E_BronzeGloves,
	E_DiamondGloves,
	E_FlameGloves,
	E_FrostGloves,
	E_GoldGloves,
	E_IronGloves,
	E_LightningGloves,
	E_MythrilGloves,
	E_MAX
};

UENUM(BlueprintType)
enum class EHelmets : uint8
{
	E_BronzeSallet,
	E_DiamondSallet,
	E_EternalSallet,
	E_FlameSallet,
	E_FrostSallet,
	E_IronSallet,
	E_LightningSallet,
	E_MythrilSallet,
	E_TimeSallet,
	E_MAX
};

UENUM(BlueprintType)
enum class EBelts : uint8
{
	E_BronzeBelt,
	E_DiamondBelt,
	E_EternalBelt,
	E_FlameBelt,
	E_FrostBelt,
	E_IronBelt,
	E_LightningBelt,
	E_MythrilBelt,
	E_PureBelt,
	E_WindBelt,
	E_MAX
};

UENUM(BlueprintType)
enum class EAccessories : uint8
{
	E_AngelKit,
	E_BlueYarn,
	E_Brigandology,
	E_DaemonKit,
	E_DesignerGlasses,
	E_DesignerGoggles,
	E_EyewearTechniques,
	E_FairieKit,
	E_FashionKit,
	E_FiendKit,
	E_FlameCraft,
	E_ForbiddenTome,
	E_FrostCraft,
	E_GoggleTechniques,
	E_GoldCraft,
	E_HealingKit,
	E_LadysAccessories,
	E_LightningCraft,
	E_NewClockwork,
	E_RingOfInvincibilty,
	E_RingOfLight,
	E_SecretsOfSpeed,
	E_SecretsOfWisdom,
	E_SoulOfTheDragon,
	E_SoulOfTheLion,
	E_TomeOfMagic,
	E_TomeOfSorcery,
	E_TomeOfSpeed,
	E_TomeOfWisdom,
	E_WhiteYarn,
	E_ZealKit,
	E_MAX
};

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
	E_PheonixDown,
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
enum class EArtefactTypes : uint8
{
	E_Strength,
	E_Magic,
	E_Defence,
	E_Command,
	E_Health,
	E_Rings,
	E_MAX
};

UENUM(BlueprintType)
enum class EArtefactStrength : uint8
{
	E_Ashura,
	E_DoubleAxe,
	E_Engetsurin,
	E_FangCharm,
	E_Flametongue,
	E_Gekkabijin,
	E_GiantsGlove,
	E_GreenBeret,
	E_HeavyArmband,
	E_IceBrand,
	E_KaiserKnuckles,
	E_LoadedDice,
	E_Maneater,
	E_Masamune,
	E_Masquerade,
	E_Mjolinir,
	E_Murasame,
	E_OgreKiller,
	E_OnionSword,
	E_PowerWristband,
	E_SasukesBlade,
	E_Shuriken,
	E_TwistedHeadband,
	E_MAX
};

UENUM(BlueprintType)
enum class EArtefactMagic : uint8
{
	E_BookOfLight,
	E_CandyRing,
	E_CatsBell,
	E_DarkMatter,
	E_DragonsWhisker,
	E_FaerieRing,
	E_Galatyn,
	E_GoldHairpin,
	E_Kris,
	E_MageMasher,
	E_MagesStaff,
	E_NoahsLute,
	E_RedSlippers,
	E_Ribbon,
	E_RuneBell,
	E_RuneStaff,
	E_SagesStaff,
	E_SilverBracer,
	E_TaotieMotif,
	E_TomeOfUltima,
	E_WingedCap,
	E_WonderWand,
	E_MAX
};

UENUM(BlueprintType)
enum class EArtefactDefence : uint8
{
	E_Aegis,
	E_BlackHood,
	E_Buckler,
	E_ChickenKnife,
	E_Drill,
	E_ElvenMantle,
	E_HelmOfArai,
	E_MainGauche,
	E_RatsTail,
	E_RingOfProtection,
	E_SaveTheQueen,
	E_SilverSpectacles,
	E_SparklingBracer,
	E_TeddyBear,
	E_WonderBracer,
	E_MAX
};

UENUM(BlueprintType)
enum class EArtefactCommandSlot : uint8
{
	E_ChocoboPocket,
	E_MooglePocket,
	E_GobbiePocket,
	E_UltimatePocket,
	E_MAX
};

UENUM(BlueprintType)
enum class EArtefactPendants : uint8
{
	E_EarthPendant,
	E_MoonPendant,
	E_StarPendant,
	E_SunPendant,
	E_MAX
};

UENUM(BlueprintType)
enum class EArtefactRings : uint8
{
	E_RingOfBlizzard,
	E_RingOfThunder,
	E_RingOfFire,
	E_RingOfCure,
	E_RingOfLife,
	E_MAX
};

UENUM(BlueprintType)
enum class EKeyItem : uint8
{
	E_CactusFlower,
	E_KilandaSulfur,
	E_MarkOfShella,
	E_WornBandana,
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		UTexture2D* ItemIcon;

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
		ItemIcon = nullptr;
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
		ItemIcon = Other.ItemIcon;
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
		ItemIcon = nullptr;
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
		ItemIcon = nullptr;
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
		ItemIcon = nullptr;
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
