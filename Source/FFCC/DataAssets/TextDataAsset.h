// Fan Made FFCC - July 28th 2017

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TextDataAsset.generated.h"

USTRUCT()
struct FDialogueData
{

	GENERATED_USTRUCT_BODY()

		/** Song Name to be displayed at the top of the screen*/
	UPROPERTY(EditAnywhere, Category = "Dialogue_Data", meta = (ToolTip = "The NPC Name"))
		FString NPCName;

	/** Image relevant to song being played*/
	UPROPERTY(EditAnywhere, Category = "Dialogue_Data", meta = (ToolTip = "The NPCs Sentences"))
		TArray<FString> Sentences;

	/** Default Constructor*/
	FDialogueData()
	{
		NPCName = "";
		Sentences = { "" };
	}
};
/**
 * 
 */
UCLASS()
class FFCC_API UTextDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
private:
	/** Core of the database - a bunch of dialogue structs*/
	UPROPERTY(EditAnywhere, Category = "Dialogue Database", meta = (Tooltip = "Dialogue Storage"))
		FDialogueData Dialogues;
	
public:

	/** Utility Functions*/
	FORCEINLINE int GetArrayLength() const { return Dialogues.Sentences.Num(); }

	FORCEINLINE TArray<FString> GetSentences() const
	{
		return Dialogues.Sentences;
	}	
};
