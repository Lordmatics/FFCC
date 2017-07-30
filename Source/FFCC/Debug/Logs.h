// Fan Made FFCC - July 28th 2017

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Logs.generated.h"

//General Log
DECLARE_LOG_CATEGORY_EXTERN(GenLog, Log, All);

//Logging during game startup
DECLARE_LOG_CATEGORY_EXTERN(AILog, Log, All);

//Logging for your AI system
DECLARE_LOG_CATEGORY_EXTERN(PlayerLog, Log, All);

//Logging for Critical Errors that must always be addressed
DECLARE_LOG_CATEGORY_EXTERN(BadLog, Log, All);

/**
 * 
 */
UCLASS()
class FFCC_API ULogs : public UObject
{
	GENERATED_BODY()
	
	
	
	
};
