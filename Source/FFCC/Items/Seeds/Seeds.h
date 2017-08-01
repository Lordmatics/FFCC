// Fan Made FFCC - July 28th 2017

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "FFCC/Items/ItemTypeEnum.h"
#include "Seeds.generated.h"

UCLASS()
class FFCC_API ASeeds : public AItem
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASeeds();

	UPROPERTY(EditAnywhere, Category = "Item")
		ESeedType SeedType;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		virtual void OnPickedUp() override;

	
};
