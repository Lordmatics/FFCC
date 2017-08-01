// Fan Made FFCC - July 28th 2017

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PickupComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPickedUp);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FFCC_API UPickupComponent : public UActorComponent
{
	GENERATED_BODY()

private:

public:	
	// Sets default values for this component's properties
	UPickupComponent();

	FOnPickedUp OnPickedUp;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};
