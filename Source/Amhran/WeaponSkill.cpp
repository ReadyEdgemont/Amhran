// Fill out your copyright notice in the Description page of Project Settings.

#include "Amhran.h"
#include "WeaponSkill.h"

UWeaponSkill::UWeaponSkill() : USkill(SKILL_DEFAULT_VALUE) {}

UWeaponSkill::UWeaponSkill(int32 Score) : USkill(Score) {}

int32 UWeaponSkill::ComputeDamage(int32 RawDamage, int32 Strength) {
	return RawDamage + (RawDamage * DEFAULT_WEAPON_SKILL_DMG_MOD * GetCurrentLevel()); // TODO: Create equation w/ STR
}

void UWeaponSkill::AddExpFromDamage(int32 DamageDealt) {
	AddExperience(DamageDealt); // TODO: Create equation
}