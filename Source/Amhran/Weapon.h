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
	UFUNCTION()
		void Init(const UWeapon * other);
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	EWeaponTypeEnum WeaponType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float Damage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float Range;
	// TODO: Add animation file support!!!
};
