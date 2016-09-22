// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Amhran.h"
#include "Object.h"
#include "Item.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class AMHRAN_API UItem : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = Item)
		FName GetName();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
		FName Name;				// The displayed and editor name of the item
	UPROPERTY(EditAnywhere, Category = Item)
		EItemTypeEnum Type;		// The category of this item. DO NOT mark a basic item as weapon/armor or unmark a weapon/armor as such!


	// TODO: Add Icon support?
	
};
