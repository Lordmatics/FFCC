// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FFCCGameMode.h"
#include "FFCCCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFFCCGameMode::AFFCCGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/BP_Extensions/Player/BP_Character"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
