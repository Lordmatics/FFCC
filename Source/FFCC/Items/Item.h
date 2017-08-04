// Fan Made FFCC - July 28th 2017

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FFCC/Items/ItemTypeEnum.h"
#include "Item.generated.h"

UCLASS()
class FFCC_API AItem : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Item")
		class USceneComponent* MyRoot;

public:	
	// Sets default values for this actor's properties
	AItem();

	UPROPERTY(EditAnywhere, Category = "Item")
		class UItemDataAsset* ItemDataAsset;

	FItemData GetItemData() const;

	UFUNCTION()
		virtual void OnPickedUp();

protected:
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Item")
		class USphereComponent* MyCollision;

	UPROPERTY(VisibleDefaultsOnly, Category = "Item")
		class UStaticMeshComponent* MyItem;

	virtual void PostInitializeComponents() override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	//template<typename T>
	//FString EnumToString(const FString& enumName, const T value, const FString& defaultValue) const
	//{
	//	UEnum* pEnum = FindObject<UEnum>(ANY_PACKAGE, *enumName, true);
	//	return pEnum
	//		? ExpandEnumString(pEnum->GetNameByIndex(static_cast<uint8>(value)).ToString(), enumName)
	//		: defaultValue;
	//}

	//FString ExpandEnumString(const FString& name, const FString& enumName)
	//{
	//	FString expanded(name);
	//	FString spaceLetter("");
	//	FString spaceNumber("");
	//	FString search("");
	//	expanded.ReplaceInline(*enumName, TEXT(""), ESearchCase::CaseSensitive);
	//	expanded.ReplaceInline(TEXT("::"), TEXT(""), ESearchCase::CaseSensitive);
	//	for (TCHAR letter = 'A'; letter <= 'Z'; ++letter)
	//	{
	//		search = FString::Printf(TEXT("%c"), letter);
	//		spaceLetter = FString::Printf(TEXT(" %c"), letter);
	//		expanded.ReplaceInline(*search, *spaceLetter, ESearchCase::CaseSensitive);
	//	}
	//	for (TCHAR number = '0'; number <= '9'; ++number)
	//	{
	//		search = FString::Printf(TEXT("%c"), number);
	//		spaceNumber = FString::Printf(TEXT(" %c"), number);
	//		expanded.ReplaceInline(*search, *spaceNumber, ESearchCase::CaseSensitive);
	//	}
	//	expanded.ReplaceInline(TEXT("_"), TEXT(" -"), ESearchCase::CaseSensitive);
	//	expanded = expanded.RightChop(1).Trim().TrimTrailing();
	//	return expanded;
	//}
	
};
