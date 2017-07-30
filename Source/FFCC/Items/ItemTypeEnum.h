// Fan Made FFCC - July 28th 2017

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
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
	E_ZusBeak
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
	E_Flour
};

UENUM(BlueprintType)
enum class ESeedType : uint8
{
	E_FruitSeed,
	E_VegetableSeed,
	E_StrangeSeed,
	E_WheatSeed,
	E_FlowerSeed
};
/**
 * 
 */
UCLASS()
class FFCC_API UItemTypeEnum : public UObject
{
	GENERATED_BODY()
	
	
	
	
};
