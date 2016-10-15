// Fill out your copyright notice in the Description page of Project Settings.

#include "Amhran.h"
#include "DialogueLibrary.h"

void UDialogueLibrary::ReadTextFromFile(FString FileName, FString & OutString) {
	FString fullPath = FPaths::GameDir() + FileName + ".txt";
	FFileHelper::LoadFileToString(OutString, *fullPath, 0);
}