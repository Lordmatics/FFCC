// Fan Made FFCC - July 28th 2017

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Enums.generated.h"

UENUM(BlueprintType)
enum class ECharacterTribe : uint8
{
	E_Clavat,
	E_Lilty,
	E_Yuke,
	E_Selkie
};

UENUM(BlueprintType)
enum class ECharacterTrade : uint8
{
	E_Blacksmith,
	E_Miller,
	E_Tailor,
	E_Fisherman,
	E_Farmer,
	E_Merchant,
	E_Rancher,
	E_Alchemist
};

UENUM(BlueprintType)
enum class ECharacterGender : uint8
{
	E_Male,
	E_Female
};

USTRUCT(BlueprintType)
struct FCharacterStats
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player ATK")
		int Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player DEF")
		int Defence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player MAG")
		int Magic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player MEM")
		int Memories;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player TRB")
		ECharacterTribe Tribe;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player TRD")
		ECharacterTrade Trade;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player GDR")
		ECharacterGender Gender;

	FCharacterStats()
	{
		Attack = 20;
		Defence = 20;
		Magic = 15;
		Memories = 0;
		Tribe = ECharacterTribe::E_Clavat;
		Trade = ECharacterTrade::E_Alchemist;
		Gender = ECharacterGender::E_Male;
	}

	FCharacterStats(const FCharacterStats& Other)
	{
		Attack = Other.Attack;
		Defence = Other.Defence;
		Magic = Other.Magic;
		Memories = Other.Memories;
		Tribe = Other.Tribe;
		Trade = Other.Trade;
		Gender = Other.Gender;
	}

	FCharacterStats(int Atk, int Def, int Mag, int Mem, ECharacterTribe Trb, ECharacterTrade Trd, ECharacterGender Gdr)
	{
		Attack = Atk;
		Defence = Def;
		Magic = Mag;
		Memories = Mem;
		Tribe = Trb;
		Trade = Trd;
		Gender = Gdr;
	}
};

USTRUCT(BlueprintType)
struct FNPCStats
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player TRB")
		ECharacterTribe Tribe;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player TRD")
		ECharacterTrade Trade;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player GDR")
		ECharacterGender Gender;

	FNPCStats()
	{
		Tribe = ECharacterTribe::E_Clavat;
		Trade = ECharacterTrade::E_Alchemist;
		Gender = ECharacterGender::E_Male;
	}

	FNPCStats(const FNPCStats& Other)
	{
		Tribe = Other.Tribe;
		Trade = Other.Trade;
		Gender = Other.Gender;
	}

	FNPCStats(ECharacterTribe Trb, ECharacterTrade Trd, ECharacterGender Gdr)
	{
		Tribe = Trb;
		Trade = Trd;
		Gender = Gdr;
	}
};
/**
 * 
 */
UCLASS()
class FFCC_API UEnums : public UObject
{
	GENERATED_BODY()
	
	
	
	
};
