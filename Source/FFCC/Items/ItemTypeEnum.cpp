// Fan Made FFCC - July 28th 2017

#include "ItemTypeEnum.h"




void UItemTypeEnum::InitSeed(const ESeedType Type, FString& String, int& Buy, int& Sell)
{
	switch (Type)
	{
	case ESeedType::E_FlowerSeed:
	{
		String = FString(TEXT("Flower Seed"));
		Buy = 250;
		Sell = 250;
		break;
	}
	case ESeedType::E_FruitSeed:
	{
		String = FString(TEXT("Fruit Seed"));
		Buy = 25;
		Sell = 25;
		break;
	}
	case ESeedType::E_StrangeSeed:
	{
		String = FString(TEXT("Strange Seed"));
		Buy = 250;
		Sell = 250;
		break;
	}
	case ESeedType::E_VegetableSeed:
	{
		String = FString(TEXT("Vegetable Seed"));
		Buy = 25;
		Sell = 25;
		break;
	}
	case ESeedType::E_WheatSeed:
	{
		String = FString(TEXT("Wheat Seed"));
		Buy = 25;
		Sell = 25;
		break;
	}
	default:
	{
		String = FString(TEXT("Seed"));
		Buy = 25;
		Sell = 25;
		break;
	}
	}
}

void UItemTypeEnum::InitFood(const EFoodType Type,  FString& String, int& Buy, int& Sell)
{
	switch (Type)
	{
	case EFoodType::E_BannockBread:
	{
		String = FString(TEXT("Bannock Bread"));
		Buy = 10;
		Sell = 10;
		break;
	}
	case EFoodType::E_CherryCluster:
	{
		String = FString(TEXT("Cherry Cluster"));
		Buy = 40;
		Sell = 10;
		break;
	}
	case EFoodType::E_Fish:
	{
		String = FString(TEXT("Fish"));
		Buy = 40;
		Sell = 10;
		break;
	}
	case EFoodType::E_Flour:
	{
		String = FString(TEXT("Flour"));
		Buy = 50;
		Sell = 50;
		break;
	}
	case EFoodType::E_Meat:
	{
		String = FString(TEXT("Meat"));
		Buy = 40;
		Sell = 10;
		break;
	}
	case EFoodType::E_Milk:
	{
		String = FString(TEXT("Milk"));
		Buy = 20;
		Sell = 5;
		break;
	}
	case EFoodType::E_RainbowGrapes:
	{
		String = FString(TEXT("Rainbow Grapes"));
		Buy = 40;
		Sell = 10;
		break;
	}
	case EFoodType::E_RoundCorn:
	{
		String = FString(TEXT("Round Corn"));
		Buy = 40;
		Sell = 10;
		break;
	}
	case EFoodType::E_SpringWater:
	{
		String = FString(TEXT("Spring Water"));
		Buy = 20;
		Sell = 5;
		break;
	}
	case EFoodType::E_StarCarrot:
	{
		String = FString(TEXT("Star Carrot"));
		Buy = 40;
		Sell = 10;
		break;
	}
	case EFoodType::E_StrangeLiquid:
	{
		String = FString(TEXT("Strange Liquid"));
		Buy = 20;
		Sell = 5;
		break;
	}
	case EFoodType::E_StripedApple:
	{
		String = FString(TEXT("Striped Apple"));
		Buy = 40;
		Sell = 10;
		break;
	}
	case EFoodType::E_Wheat:
	{
		String = FString(TEXT("Wheat"));
		Buy = 50;
		Sell = 50;
		break;
	}
	default:
	{
		String = FString(TEXT("Meat"));
		Buy = 40;
		Sell = 10;
		break;
	}
	}
}

void UItemTypeEnum::InitMaterial(const EMaterialType Type,  FString& String, int& Buy, int& Sell)
{
	switch (Type)
	{
	case EMaterialType::E_Alloy:
	{
		String = FString(TEXT("Alloy"));
		Buy = 250;
		Sell = 62;
		break;
	}
	case EMaterialType::E_AncientPotion:
	{
		String = FString(TEXT("Ancient Potion"));
		Buy = 0;
		Sell = 5000;
		break;
	}
	case EMaterialType::E_AncientSword:
	{
		String = FString(TEXT("Ancient Sword"));
		Buy = 0;
		Sell = 7500;
		break;
	}
	case EMaterialType::E_AngelsTear:
	{
		String = FString(TEXT("Angels Tear"));
		Buy = 0;
		Sell = 250;
		break;
	}
	case EMaterialType::E_BlueSilk:
	{
		String = FString(TEXT("Blue Silk"));
		Buy = 1000;
		Sell = 250;
		break;
	}
	case EMaterialType::E_Bronze:
	{
		String = FString(TEXT("Bronze"));
		Buy = 300;
		Sell = 75;
		break;
	}
	case EMaterialType::E_BronzeShard:
	{
		String = FString(TEXT("Bronze Shard"));
		Buy = 100;
		Sell = 25;
		break;
	}
	case EMaterialType::E_CerberusFang:
	{
		String = FString(TEXT("Cerberus Fang"));
		Buy = 0;
		Sell = 750;
		break;
	}
	case EMaterialType::E_ChillyGel:
	{
		String = FString(TEXT("Chilly Gel"));
		Buy = 1000;
		Sell = 250;
		break;
	}
	case EMaterialType::E_ChimeraHorn:
	{
		String = FString(TEXT("Chimera Horn"));
		Buy = 0;
		Sell = 625;
		break;
	}
	case EMaterialType::E_CockatriceScale:
	{
		String = FString(TEXT("Cockatrice Scale"));
		Buy = 0;
		Sell = 500;
		break;
	}
	case EMaterialType::E_CoeurlsWhisker:
	{
		String = FString(TEXT("Coeurls Whisker"));
		Buy = 0;
		Sell = 500;
		break;
	}
	case EMaterialType::E_CrystalBall:
	{
		String = FString(TEXT("Crystal Ball"));
		Buy = 100;
		Sell = 25;
		break;
	}
	case EMaterialType::E_CursedCrook:
	{
		String = FString(TEXT("Cursed Crook"));
		Buy = 0;
		Sell = 7500;
		break;
	}
	case EMaterialType::E_DarkSphere:
	{
		String = FString(TEXT("Dark Sphere"));
		Buy = 50000;
		Sell = 12500;
		break;
	}
	case EMaterialType::E_DesertFang:
	{
		String = FString(TEXT("Desert Fang"));
		Buy = 0;
		Sell = 7500;
		break;
	}
	case EMaterialType::E_DevilsClaw:
	{
		String = FString(TEXT("Devils Claw"));
		Buy = 0;
		Sell = 750;
		break;
	}
	case EMaterialType::E_DiamondOre:
	{
		String = FString(TEXT("Diamond Ore"));
		Buy = 0;
		Sell = 750;
		break;
	}
	case EMaterialType::E_DragonFang:
	{
		String = FString(TEXT("Dragon Fang"));
		Buy = 0;
		Sell = 7500;
		break;
	}
	case EMaterialType::E_DweomerSpore:
	{
		String = FString(TEXT("Dweomer Spore"));
		Buy = 0;
		Sell = 7500;
		break;
	}
	case EMaterialType::E_EtherealOrb:
	{
		String = FString(TEXT("Etheral Orb"));
		Buy = 0;
		Sell = 7500;
		break;
	}
	case EMaterialType::E_FaeriesTear:
	{
		String = FString(TEXT("Faeries Tear"));
		Buy = 1000;
		Sell = 250;
		break;
	}
	case EMaterialType::E_FiendsClaw:
	{
		String = FString(TEXT("Fiends Claw"));
		Buy = 1000;
		Sell = 250;
		break;
	}
	case EMaterialType::E_Gear:
	{
		String = FString(TEXT("Gear"));
		Buy = 0;
		Sell = 250;
		break;
	}
	case EMaterialType::E_GigasClaw:
	{
		String = FString(TEXT("Gigas Claw"));
		Buy = 0;
		Sell = 625;
		break;
	}
	case EMaterialType::E_Gold:
	{
		String = FString(TEXT("Gold"));
		Buy = 500;
		Sell = 125;
		break;
	}
	case EMaterialType::E_GreenSphere:
	{
		String = FString(TEXT("Green Sphere"));
		Buy = 0;
		Sell = 7500;
		break;
	}
	case EMaterialType::E_GriffinsWing:
	{
		String = FString(TEXT("Griffins Wing"));
		Buy = 0;
		Sell = 500;
		break;
	}
	case EMaterialType::E_HardShell:
	{
		String = FString(TEXT("Hard Shell"));
		Buy = 0;
		Sell = 500;
		break;
	}
	case EMaterialType::E_HeavenlyDust:
	{
		String = FString(TEXT("Heavenly Dust"));
		Buy = 1000;
		Sell = 250;
		break;
	}
	case EMaterialType::E_HolyWater:
	{
		String = FString(TEXT("Holy Water"));
		Buy = 1000;
		Sell = 250;
		break;
	}
	case EMaterialType::E_Iron:
	{
		String = FString(TEXT("Iron"));
		Buy = 500;
		Sell = 125;
		break;
	}
	case EMaterialType::E_IronShard:
	{
		String = FString(TEXT("Iron Shard"));
		Buy = 100;
		Sell = 25;
		break;
	}
	case EMaterialType::E_Jade:
	{
		String = FString(TEXT("Jade"));
		Buy = 200;
		Sell = 50;
		break;
	}
	case EMaterialType::E_JaggedScythe:
	{
		String = FString(TEXT("Jagged Scythe"));
		Buy = 0;
		Sell = 1000;
		break;
	}
	case EMaterialType::E_KingsScale:
	{
		String = FString(TEXT("Kings Scale"));
		Buy = 0;
		Sell = 7500;
		break;
	}
	case EMaterialType::E_LordsRobe:
	{
		String = FString(TEXT("Lords Robe"));
		Buy = 0;
		Sell = 7500;
		break;
	}
	case EMaterialType::E_MagmaRock:
	{
		String = FString(TEXT("Magma Rock"));
		Buy = 1000;
		Sell = 250;
		break;
	}
	case EMaterialType::E_MalboroSeed:
	{
		String = FString(TEXT("Malboro Seed"));
		Buy = 0;
		Sell = 7500;
		break;
	}
	case EMaterialType::E_Mythril:
	{
		String = FString(TEXT("Mythril"));
		Buy = 5000;
		Sell = 1250;
		break;
	}
	case EMaterialType::E_Needle:
	{
		String = FString(TEXT("Needle"));
		Buy = 0;
		Sell = 625;
		break;
	}
	case EMaterialType::E_OgreFang:
	{
		String = FString(TEXT("Ogre Fang"));
		Buy = 0;
		Sell = 625;
		break;
	}
	case EMaterialType::E_OrcBelt:
	{
		String = FString(TEXT("Orc Belt"));
		Buy = 0;
		Sell = 7500;
		break;
	}
	case EMaterialType::E_Orichalcum:
	{
		String = FString(TEXT("Orichalcum"));
		Buy = 0;
		Sell = 5000;
		break;
	}
	case EMaterialType::E_PressedFlower:
	{
		String = FString(TEXT("Pressed Flower"));
		Buy = 0;
		Sell = 250;
		break;
	}
	case EMaterialType::E_RedEye:
	{
		String = FString(TEXT("Red Eye"));
		Buy = 0;
		Sell = 7500;
		break;
	}
	case EMaterialType::E_Remedy:
	{
		String = FString(TEXT("Remedy"));
		Buy = 0;
		Sell = 250;
		break;
	}
	case EMaterialType::E_Ruby:
	{
		String = FString(TEXT("Ruby"));
		Buy = 200;
		Sell = 50;
		break;
	}
	case EMaterialType::E_ShinyShard:
	{
		String = FString(TEXT("Shiny Shard"));
		Buy = 0;
		Sell = 250;
		break;
	}
	case EMaterialType::E_Silver:
	{
		String = FString(TEXT("Silver"));
		Buy = 500;
		Sell = 125;
		break;
	}
	case EMaterialType::E_Thunderball:
	{
		String = FString(TEXT("Thunderball"));
		Buy = 1000;
		Sell = 250;
		break;
	}
	case EMaterialType::E_TinyCrystal:
	{
		String = FString(TEXT("Tiny Crystal"));
		Buy = 0;
		Sell = 250;
		break;
	}
	case EMaterialType::E_ToadOil:
	{
		String = FString(TEXT("Toad Oil"));
		Buy = 0;
		Sell = 500;
		break;
	}
	case EMaterialType::E_Ultimate:
	{
		String = FString(TEXT("Ultimite"));
		Buy = 50000;
		Sell = 12500;
		break;
	}
	case EMaterialType::E_WhiteSilk:
	{
		String = FString(TEXT("White Silk"));
		Buy = 0;
		Sell = 750;
		break;
	}
	case EMaterialType::E_WindCrystal:
	{
		String = FString(TEXT("Wind Crystal"));
		Buy = 0;
		Sell = 7500;
		break;
	}
	case EMaterialType::E_WormAntenna:
	{
		String = FString(TEXT("Worm Antenna"));
		Buy = 0;
		Sell = 500;
		break;
	}
	case EMaterialType::E_YellowFeather:
	{
		String = FString(TEXT("Yellow Feather"));
		Buy = 0;
		Sell = 1000;
		break;
	}
	case EMaterialType::E_ZusBeak:
	{
		String = FString(TEXT("Zus Beak"));
		Buy = 0;
		Sell = 750;
		break;
	}
	default:
	{
		String = FString(TEXT("Meat"));
		Buy = 40;
		Sell = 10;
		break;
	}
	}
}