// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Item.generated.h"

/**
 * 
 */
UCLASS()
class AMHRAN_API UItem : public UObject
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	FName Name;
	// TODO: Add Icon support?
	
};
