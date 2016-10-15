// Fill out your copyright notice in the Description page of Project Settings.

#include "Amhran.h"
#include "SkillSet.h"

USkillSet::USkillSet() {
	Level = 1;
	unspentAbilityPoints = 5;
		// Define Abilities before skills by convention, please!
	registerAbility(FName("Strength"), 0);
	registerAbility(FName("Dexterity"), 1);
	registerAbility(FName("Constitution"), 2);
	registerAbility(FName("Intelligence"), 3);
	registerAbility(FName("Wisdom"), 4);
	registerAbility(FName("Charisma"), 5);

	registerSkill(FName("Light Weapons"), 0);
	registerSkill(FName("Parry"), 1);
	registerSkill(FName("Transmutation"), 2);
	registerSkill(FName("Speechcraft"), 3);
}

void USkillSet::assignToTransient(const USkillSetTransient * const Transient) {
	Level = Transient->Level;
	Abilities = Transient->getAbilityArray();
	Skills = Transient->getSkillArray();
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

float USkillSet::GetSkillLevelPercentage(FName SkillName) const {
	USkill* reqSkill;
	if (nameDefines.Contains(SkillName)) {
		reqSkill = Skills[nameDefines[SkillName]];
		return reqSkill->GetCurrentExp() / reqSkill->GetCurrentExpCeiling();
	}
	UE_LOG(LogTemp, Warning, TEXT("Warning: Attempt to access non-existant Skillname!"));
	return NULL;
}

UAbility* USkillSet::GetAbility(FName AbilityName) const {
	if (nameDefines.Contains(AbilityName))
		return Abilities[nameDefines[AbilityName]];
	UE_LOG(LogTemp, Warning, TEXT("Warning: Attempt to access non-existant Abilityname!"));
	return NULL;
}

bool USkillSet::HasUnspentAbilityPoints() const {
	return unspentAbilityPoints != 0;
}

int32 USkillSet::GetUnspentAbilityPoints() const {
	return unspentAbilityPoints;
}

void USkillSet::IncreaseUnspentAbilityPoints(int32 Amount) {
	unspentAbilityPoints += Amount;
}

void USkillSet::SpendAbilityPoint() {
	unspentAbilityPoints--;
}

void USkillSet::registerAbility(FName abilityName, int32 id) {
	nameDefines.Add(abilityName, id);
	abilityNames.Add(FText::FromName(abilityName));
}

void USkillSet::registerSkill(FName skillName, int32 id) {
	nameDefines.Add(skillName, id);
	skillNames.Add(FText::FromName(skillName));
}

TArray<FText> USkillSet::GetAbilityNames() const {
	return abilityNames;
}

TArray<FText> USkillSet::GetSkillNames() const {
	return skillNames;
}