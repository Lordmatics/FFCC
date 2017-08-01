// Fan Made FFCC - July 28th 2017

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShopComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FFCC_API UShopComponent : public UActorComponent
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, Category = "Inventory")
		int MaxInventorySize;

	UPROPERTY(EditAnywhere, Category = "Inventory")
		int CurrentSlotsFilled;

	UPROPERTY(EditAnywhere, Category = "Inventory")
		TArray<class AItem*> Inventory;

	UPROPERTY(EditAnywhere, Category = "Inventory")
		class UMerchShopDataAsset* CurrentStock;

public:	
	// Sets default values for this component's properties
	UShopComponent();

	bool AddItem(class AItem* ItemToAdd);

	void RemoveItem(class AItem* ItemToRemove);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		FString GetItemNameAtIndex(int Index);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		int GetItemSellValueAtIndex(int Index);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		int GetItemBuyValueAtIndex(int Index);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		FString GetMerchNameAtRow(int Row);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		int GetMerchBuyAtRow(int Row);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		int GetMerchSellAtRow(int Row);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		UTexture2D* GetMerchIconAtRow(int Row);

	void SetMerchantStock(class UMerchShopDataAsset& Data);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
		
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};
