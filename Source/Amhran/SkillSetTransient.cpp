// Fill out your copyright notice in the Description page of Project Settings.

#include "Amhran.h"
#include "SkillSetTransient.h"


USkillSetTransient::USkillSetTransient() {
	// Don't use this!
}

USkillSetTransient::USkillSetTransient(const int32 Level, const int32 Strength, const int32 Dexterity, const int32 Constitution,
		const int32 Intelligence, const int32 Wisdom, const int32 Charisma, const int32 LightWeapons, const int32 Parry, 
		const int32 Transmutation, const int32 Speechcraft) {

	this->Level = Level;
	makeAbilityArray(Strength, Dexterity, Constitution, Intelligence, Wisdom, Charisma);
	makeSkillArray(LightWeapons, Parry, Transmutation, Speechcraft);
}

TArray<UAbility*> USkillSetTransient::getAbilityArray() const {
	return abilities;
}

TArray<USkill*> USkillSetTransient::getSkillArray() const {
	return skills;
}

/*TArray<UWeaponSkill*> USkillSetTransient::getWeaponSkillArray() const {
	return weaponSkills;
}*/

void USkillSetTransient::makeAbilityArray(const int32 Strength, const int32 Dexterity, const int32 Constitution,
	const int32 Intelligence, const int32 Wisdom, const int32 Charisma) {

	abilities.Add(NewObject<UAbility>());
	abilities[0]->SetScore(Strength);
	abilities.Add(NewObject<UAbility>());
	abilities[1]->SetScore(Dexterity);
	abilities.Add(NewObject<UAbility>());
	abilities[2]->SetScore(Constitution);
	abilities.Add(NewObject<UAbility>());
	abilities[3]->SetScore(Intelligence);
	abilities.Add(NewObject<UAbility>());
	abilities[4]->SetScore(Wisdom);
	abilities.Add(NewObject<UAbility>());
	abilities[5]->SetScore(Charisma);
}

/*void USkillSetTransient::makeWeaponSkillArray(const int32 LightWeapons) {
	weaponSkills.Add(NewObject<ULightWeapons>());
	weaponSkills[0]->SetLevel(LightWeapons);
}*/

void USkillSetTransient::makeSkillArray(const int32 LightWeapons, const int32 Parry, const int32 Transmutation, 
										const int32 Speechcraft) {
	skills.Add(NewObject<USkill>());
	skills[0]->SetLevel(LightWeapons);
	skills.Add(NewObject<USkill>());
	skills[1]->SetLevel(Parry);
	skills.Add(NewObject<USkill>());
	skills[2]->SetLevel(Transmutation);
	skills.Add(NewObject<USkill>());
	skills[3]->SetLevel(Speechcraft);
}