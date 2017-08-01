// Fan Made FFCC - July 28th 2017

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "FFCC/Items/ItemTypeEnum.h"
#include "Food.generated.h"

/**
 * 
 */
UCLASS()
class FFCC_API AFood : public AItem
{
	GENERATED_BODY()
	
private:

public:
	AFood();

	UPROPERTY(EditAnywhere, Category = "Item")
		EFoodType FoodType;
protected:
	virtual void PostInitializeComponents() override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
		virtual void OnPickedUp() override;

};
