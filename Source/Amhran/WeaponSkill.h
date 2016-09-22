// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Skill.h"
#include "WeaponSkill.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType)
class AMHRAN_API UWeaponSkill : public USkill
{
	GENERATED_BODY()
	
//public:
	//UWeaponSkill();
	//UWeaponSkill(int32 Score);
	/*UFUNCTION(BlueprintCallable, Category = Skills)
	int32 ComputeDamage(int32 RawDamage, int32 Strength);
	UFUNCTION(BlueprintCallable, Category = Skills)
	void AddExpFromDamage(int32 DamageDealt);*/
};
