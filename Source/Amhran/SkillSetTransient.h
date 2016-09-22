// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Ability.h"
#include "WeaponSkill.h"
#include "LightWeapons.h"
#include "SkillSetTransient.generated.h"

/**
 * 
 */
UCLASS()
class AMHRAN_API USkillSetTransient : public UObject
{
	GENERATED_BODY()
	
public:
	USkillSetTransient();	//Meaningless. DO NOT USE!!!
	USkillSetTransient(const int32 Level, const int32 Strength, const int32 Dexterity, const int32 Constitution,
			const int32 Intelligence, const int32 Wisdom, const int32 Charisma, const int32 LightWeapons);

	UFUNCTION()
	void makeAbilityArray(const int32 Strength, const int32 Dexterity, const int32 Constitution,
			const int32 Intelligence, const int32 Wisdom, const int32 Charisma);
	UFUNCTION()
	void makeSkillArray(const int32 LightWeapons);
	/*UFUNCTION()
	void makeWeaponSkillArray(const int32 Smithing);*/

	UFUNCTION()
	TArray<UAbility*> getAbilityArray() const;
	UFUNCTION()
	TArray<USkill*> getSkillArray() const;
	//TArray<UWeaponSkill*> getWeaponSkillArray() const;

	UPROPERTY()
	int32 Level;
private:

	UPROPERTY()
	TArray<UAbility*> abilities;
	UPROPERTY()
	TArray<USkill*> skills;
	/*TArray<UWeaponSkill*> weaponSkills;
	UPROPERTY()*/
};
