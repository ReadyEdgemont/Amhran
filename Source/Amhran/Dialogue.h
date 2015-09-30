// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Dialogue.generated.h"

/**
 * 
 */
UCLASS()
class AMHRAN_API UDialogue : public UObject
{
	GENERATED_BODY()

	//Primary
	UFUNCTION(BluePrintCallable, DisplayName = "Print from File", Category = Dialogue)
	void PrintFromFile(FString File);
	UFUNCTION(BluePrintCallable, DisplayName = "Print from String", Category = Dialogue)
	void PrintFromString(FString Text);

	//Flow Control
	UFUNCTION(BluePrintCallable, Category = DialogueBackend)
	int32 AddResponse(FString Response);
	UFUNCTION(BluePrintCallable, Category = Dialogue)
	void EndDialogue();

	//Interactions
	UFUNCTION(BluePrintCallable, Category = Dialogue)
	void AddInteractions(bool Persudae, bool Barter, bool Train, bool Spells, bool Repair);
	UFUNCTION(BluePrintCallable, Category = Dialogue)
	void RemoveInteractions(bool Persudae, bool Barter, bool Train, bool Spells, bool Repair);
	UFUNCTION(BluePrintCallable, Category = Dialogue)
	void SetInteractions(bool Persudae, bool Barter, bool Train, bool Spells, bool Repair);

	//Topics
	UFUNCTION(BluePrintCallable, Category = Dialogue)
	void AddTopic(FString Topic);
	UFUNCTION(BluePrintCallable, Category = Dialogue)
	void RemoveTopic(FString Topic);
};
