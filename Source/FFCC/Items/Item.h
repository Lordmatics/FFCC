// Fan Made FFCC - July 28th 2017

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class FFCC_API AItem : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, Category = "Item")
		class USceneComponent* MyRoot;

public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	
	UPROPERTY(EditAnywhere, Category = "Item")
		class UStaticMeshComponent* MyItem;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
