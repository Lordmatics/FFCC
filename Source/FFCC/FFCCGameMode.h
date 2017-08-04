// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FFCC/Items/ItemTypeEnum.h"
#include "Classes/Engine/DataTable.h"
#include "FFCCGameMode.generated.h"

UCLASS(minimalapi)
class AFFCCGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFFCCGameMode();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemDatabase")
		UDataTable* ItemDatabase;
};



