// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Item.h"
#include "Armor.generated.h"

/**
 * 
 */
UCLASS()
class AMHRAN_API UArmor : public UItem
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Armor)
	int32 Protection;
	
	// TODO: Add model support!!!
	
};
