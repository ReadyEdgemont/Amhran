// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "DialogueLibrary.generated.h"

/**
 * 
 */
UCLASS()
class AMHRAN_API UDialogueLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "Dialogue")
	static void ReadTextFromFile(FString FileName, FString & OutString);
};
