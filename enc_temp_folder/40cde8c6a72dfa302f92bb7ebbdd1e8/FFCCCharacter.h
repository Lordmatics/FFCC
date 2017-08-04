// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FFCC/Character/Enums.h"
#include "FFCCCharacter.generated.h"

UCLASS(config=Game)
class AFFCCCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* InteractSphere;

	UFUNCTION()
		void OnOverlapEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherbodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherbodyIndex);

	UFUNCTION()
		void BeginInteract();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop", meta = (AllowPrivateAccess = "true"))
		int ShopItemIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop", meta = (AllowPrivateAccess = "true"))
		int MaxShopItemIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop", meta = (AllowPrivateAccess = "true"))
		bool bShowMerchantStock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop", meta = (AllowPrivateAccess = "true"))
		bool bShowPlayerStock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop", meta = (AllowPrivateAccess = "true"))
		bool bMenuScroll;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop", meta = (AllowPrivateAccess = "true"))
		int IndexForTopElementInPlayersInventory;

	//UFUNCTION(BlueprintCallable, Category = "Shop")
	//	int GetInventorySize() const;

	UFUNCTION()
		void ShopUp();

	UFUNCTION()
		void ShopDown();

	UFUNCTION()
		void ShopSelect();

	UFUNCTION()
		void ShopBack();

	void OpenMerchantShop();
	void OpenTailorShop();
	void OpenBlacksmithShop();
	void AlchemistDrop();
	void CloseMerchantShop();
	void CloseTailorShop();
	void CloseBlacksmithShop();

	UPROPERTY()
		AActor* CurrentTargetActor;

	UPROPERTY(VisibleAnywhere, Category = "Interact Target Debug")
		class ULookAtComponent* LookAtComp;

	UPROPERTY(VisibleAnywhere, Category = "Interact Target Debug")
		class ULookAtComponent* CurrentLookAtTarget;

	UPROPERTY(VisibleAnywhere, Category = "Interact Target Debug")
		class UDialogueComponent* CurrentDialogueComponent;

	//UPROPERTY(/*VisibleAnywhere,*/ BlueprintReadOnly, Category = "Interact Target Debug", meta = (AllowPrivateAccess = "true"))
	//	class UShopComponent* ShopComponent;

	//UPROPERTY(VisibleAnywhere, Category = "Interact Target Debug")
	//	class UShopComponent* TestShopComponent;

	UPROPERTY(EditAnywhere, Category = "Interact Target Debug")
		class UInventoryDataAsset* InventoryData;

	UPROPERTY(EditAnywhere, Category = "Interact Target Debug")
		class UMerchShopDataAsset* CurrentShopData;

	UPROPERTY(VisibleAnywhere, Category = "Interact Target Debug")
		uint32 bInInteractRange : 1;

	UPROPERTY(VisibleAnywhere, Category = "Interact Target Debug")
		FString InteractTargetName;

	UPROPERTY(VisibleAnywhere, Category = "Interact Target Debug")
		FString InteractTargetCurrentSentence;

	UPROPERTY(VisibleAnywhere, Category = "Interact Target Debug")
		int InteractIndexInDialogue;

	UPROPERTY(VisibleAnywhere, Category = "Interact Target Debug")
		uint32 bShowChat : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop", meta = (AllowPrivateAccess = "true"))
		bool bShowMerchantShop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop", meta = (AllowPrivateAccess = "true"))
		bool bShowTailorShop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop", meta = (AllowPrivateAccess = "true"))
		bool bShowBlacksmithShop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop", meta = (AllowPrivateAccess = "true"))
		bool bInAShop;

	FString EmptyString;
	FString QMString;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop", meta = (AllowPrivateAccess = "true"))
		int MerchantLevel;

	int GetMaxShopIndex() const;

	UFUNCTION()
		void UpgradeMerchantLevel();


	enum Flags
	{
		E_Merchant = 0,// 0x1 << 0,
		E_Blacksmith = 1,//0x1 << 1,
		E_Tailor = 2,//0x1 << 2,
		E_Alchemist = 3,//0x1 << 3
		E_Other = 4
	};

	Flags TradeFlags;

	int MerchantHierarchy;
	void MenuReset();

public:
	AFFCCCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(EditAnywhere, Category = "Character Stats")
		FCharacterStats CharacterStats;

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
		FString GetTargetName() const;

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
		FString GetTargetSentence() const;
	
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
		bool ShouldShowChat() const;

	UFUNCTION(BlueprintCallable, Category = "Items")
		class UMerchShopDataAsset* GetMerchData() const;
protected:

	void MoveForward(float Value);

	void MoveRight(float Value);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	public: 

		// SHOP STUFF
		UFUNCTION(BlueprintCallable, Category = "Inventory")
			FString GetItemNameAtIndex(int Index);

		UFUNCTION(BlueprintCallable, Category = "Inventory")
			int GetItemSellValueAtIndex(int Index);

		UFUNCTION(BlueprintCallable, Category = "Inventory")
			int GetItemBuyValueAtIndex(int Index);

		UFUNCTION(BlueprintCallable, Category = "Inventory")
			int GetInventorySize() const;

		UFUNCTION(BlueprintCallable, Category = "Inventory")
			FString GetMerchNameAtRow(int Row);

		UFUNCTION(BlueprintCallable, Category = "Inventory")
			int GetMerchBuyAtRow(int Row);

		UFUNCTION(BlueprintCallable, Category = "Inventory")
			int GetMerchSellAtRow(int Row);

		UFUNCTION(BlueprintCallable, Category = "Inventory")
			UTexture2D* GetMerchIconAtRow(int Row);
};

