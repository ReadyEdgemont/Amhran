// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Item.h"
#include "Armor.h"
#include "Weapon.h"
#include "InvEntry.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class AMHRAN_API UInvEntry : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void Init(UItem* i, int32 q);
	UFUNCTION(BlueprintPure, Category = "Inventory")
	UItem* GetItem() const;
	UFUNCTION(BlueprintPure, Category = "Inventory")
	FName GetName() const;
	UFUNCTION(BlueprintPure, Category = "Inventory")
	int32 GetQuantity() const;
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddQuantity(int32 q);

private:
	UPROPERTY()
	UItem* Item;
	UPROPERTY()
	int32 Quantity;
};
