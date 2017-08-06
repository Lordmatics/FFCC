// Fan Made FFCC - July 28th 2017

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraFollow.generated.h"

USTRUCT(BlueprintType)
struct FCameraBoundaries
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAM MIN X")
		float Min_X;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAM MAX X")
		float Max_X;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAM MIN Y")
		float Min_Y;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CAM MAX Y")
		float Max_Y;

	FCameraBoundaries()
	{
		Min_X = -1000.0f;
		Max_X = -1000.0f;
		Min_Y = 400.0f;
		Max_Y = 800.0f;
	}

};

UCLASS()
class FFCC_API ACameraFollow : public AActor
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditAnywhere, Category = "Target")
		class AFFCCCharacter* TargetToFollow;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* Root;

		/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Target")
		float xOffset;

	UPROPERTY(EditAnywhere, Category = "Target")
		float yOffset;

	UPROPERTY(EditAnywhere, Category = "Target")
		float zOffset;

	UPROPERTY(EditAnywhere, Category = "Target")
		float InterpSpeed;

	UPROPERTY(EditAnywhere, Category = "Camera")
		FCameraBoundaries CameraBounds;
public:	
	// Sets default values for this actor's properties
	ACameraFollow();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
