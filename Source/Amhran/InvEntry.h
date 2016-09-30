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
UCLASS()
class AMHRAN_API UInvEntry : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION()
	void Init(UItem* i, int32 q);
	UFUNCTION()
	UItem* GetItem() const;
		// Useless?
	UFUNCTION()
	FName GetName() const;
	UFUNCTION()
	int32 GetQuantity() const;
	UFUNCTION()
	void AddQuantity(int32 q);

private:
	UItem* Item;
	int32 Quantity;
};
