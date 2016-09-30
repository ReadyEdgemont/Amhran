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
	UItem();
	UFUNCTION()
	virtual void Init(const UItem * other);
	UFUNCTION(BlueprintPure, Category = "Item")
	FName GetName() const;
	UFUNCTION(BlueprintPure, Category = "Item")
	EItemTypeEnum GetType() const;

	UPROPERTY(EditAnywhere, Category = "Inventory")
	int32 Quantity;			// The quantity of this item to added to a character's inventory. Only used if attached as default inventory item in a loadout blueprint.
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FName Name;				// The displayed name of the item (do NOT duplicate item names unless changing ONLY the quantity entry!!!)
	UPROPERTY(EditAnywhere, Category = "Item")
	EItemTypeEnum Type;		// The category of this item. DO NOT mark a basic item as weapon/armor or unmark a weapon/armor as such! EVER!!!

	// TODO: Add Icon support?
	
};
