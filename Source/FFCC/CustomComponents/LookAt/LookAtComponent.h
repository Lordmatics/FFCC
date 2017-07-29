// Fan Made FFCC - July 28th 2017

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LookAtComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FFCC_API ULookAtComponent : public UActorComponent
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, Category = "LookAt")
		uint32 bLookAtTarget : 1;

	UPROPERTY(EditAnywhere, Category = "LookAt")
		AActor* LookAtTarget;

public:	
	// Sets default values for this component's properties
	ULookAtComponent();

	FORCEINLINE void SetLookingAtTarget(const bool LookAt) { bLookAtTarget = LookAt; }
	FORCEINLINE bool IsLookingAtTarget() const { return bLookAtTarget; }

	FORCEINLINE void SetLookingAtTarget(AActor* LookAt) { LookAtTarget = LookAt; }
	FORCEINLINE AActor* GetLookAtTarget() const { return LookAtTarget; }

	void GetRotationToLookAt(const FVector& You, const FVector& Target, FRotator& OutRotation);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};
