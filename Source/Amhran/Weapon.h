// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Item.h"
#include "Weapon.generated.h"

/**
 * 
 */
UCLASS()
class AMHRAN_API UWeapon : public UItem
{
	GENERATED_BODY()
public:
	UWeapon();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	int32 Damage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	int32 Speed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	int32 Range;
	// TODO: Add animation file support!!!
};
