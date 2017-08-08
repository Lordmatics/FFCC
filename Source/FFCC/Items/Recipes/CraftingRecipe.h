// Fan Made FFCC - July 28th 2017

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "FFCC/Items/ItemTypeEnum.h"
#include "CraftingRecipe.generated.h"

/**
 * 
 */
UCLASS()
class FFCC_API ACraftingRecipe : public AItem
{
	GENERATED_BODY()
	
private:

public:
	ACraftingRecipe();

	UPROPERTY(EditAnywhere, Category = "Item")
		EBlacksmithType CraftType;

protected:
	virtual void PostInitializeComponents() override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		virtual void OnPickedUp() override;
	
	
};
