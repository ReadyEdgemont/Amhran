// Fill out your copyright notice in the Description page of Project Settings.

#include "Amhran.h"
#include "SkillSet.h"

USkillSet::USkillSet() {
	Level = 1;
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
	Level = Transient->Level;
	Abilities = Transient->getAbilityArray();
	Skills = Transient->getSkillArray();
	//WeaponSkills = Transient->getWeaponSkillArray();
}

int32 USkillSet::GetCurrentLevel() const {
	return Level;
}

USkill* USkillSet::GetSkill(FName SkillName) const {
	if(nameDefines.Contains(SkillName))
		return Skills[nameDefines[SkillName]];
	UE_LOG(LogTemp, Warning, TEXT("Warning: Attempt to access non-existant Skillname!"));
	return NULL;
}

/*UWeaponSkill* USkillSet::GetWeaponSkill(FName SkillName) {
	return WeaponSkills[nameDefines[SkillName]];
}*/

UAbility* USkillSet::GetAbility(FName AbilityName) const {
	if (nameDefines.Contains(AbilityName))
		return Abilities[nameDefines[AbilityName]];
	UE_LOG(LogTemp, Warning, TEXT("Warning: Attempt to access non-existant Abilityname!"));
	return NULL;
}