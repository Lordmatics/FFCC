// Fan Made FFCC - July 28th 2017

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FFCC/Items/ItemTypeEnum.h"
#include "PickupComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPickedUp);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FFCC_API UPickupComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	//UPROPERTY(EditAnywhere, Category = "ItemName")
	//	FString ItemName;
public:
	// Sets default values for this component's properties
	UPickupComponent();

	//UPROPERTY(EditAnywhere, Category = "Item Asset")
	//	class UItemDataAsset* ItemDataAsset;

	//FOnPickedUp OnPickedUp;


	//FORCEINLINE FString GetItemName() const
	//{
	//	return ItemName;
	//}

	//void RegisterItem(const FItemData& ItemToRegister);



	//FItemData GetItemData();

	////FItemData* ItemPtr;
	//FItemData ItemData;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};
