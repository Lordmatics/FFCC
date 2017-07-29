// Fan Made FFCC - July 28th 2017

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DialogueComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FFCC_API UDialogueComponent : public UActorComponent
{
	GENERATED_BODY()

private:

public:	
	// Sets default values for this component's properties
	UDialogueComponent();

	UPROPERTY(EditAnywhere, Category = "Dialogue Data")
		class UTextDataAsset* DialogueData;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};
