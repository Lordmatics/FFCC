// Fan Made FFCC - July 28th 2017

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPC.generated.h"

UCLASS()
class FFCC_API ANPC : public ACharacter
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, Category = "NPC")
		class UDialogueComponent* DialogueComp;

	UPROPERTY(EditAnywhere, Category = "NPC")
		class ULookAtComponent* LookAtComp;

	UPROPERTY(EditAnywhere, Category = "NPC")
		class UNPCStatsComponent* NPCStatsComp;

	UPROPERTY(EditAnywhere, Category = "NPC")
		AActor* DebugTarget;

	UPROPERTY(EditAnywhere, Category = "NPC")
		float InterpSpeed = 5.0f; // Just Traces behind the target

public:
	// Sets default values for this character's properties
	ANPC();

	virtual class UDataAsset* GetData();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void LookAtTarget(float DeltaTime);
	
};
