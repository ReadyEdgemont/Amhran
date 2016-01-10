// Fill out your copyright notice in the Description page of Project Settings.

#include "Amhran.h"
#include "SkillSet.h"

USkillSet::USkillSet() {
	nameDefines.Add(FName("Strength"), 0);
	nameDefines.Add(FName("Dexterity"), 1);
	nameDefines.Add(FName("Constitution"), 2);
	nameDefines.Add(FName("Intelligence"), 3);
	nameDefines.Add(FName("Wisdom"), 4);
	nameDefines.Add(FName("Charisma"), 5);

	nameDefines.Add(FName("LightWeapons"), 0);
}

/*USkillSet::USkillSet(const USkillSetTransient * const Transient) {
	assignToTransient(Transient);
}*/

void USkillSet::assignToTransient(const USkillSetTransient * const Transient) {
	Abilities = Transient->getAbilityArray();
	WeaponSkills = Transient->getWeaponSkillArray();
}

USkill* USkillSet::GetSkill(FName SkillName) {
	return new USkill(); // TODO: Do something with this?
}

UWeaponSkill* USkillSet::GetWeaponSkill(FName SkillName) {
	return WeaponSkills[nameDefines[SkillName]];
}

UAbility* USkillSet::GetAbility(FName AbilityName) {
	return Abilities[nameDefines[AbilityName]];
}