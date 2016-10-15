// Fill out your copyright notice in the Description page of Project Settings.

#include "Amhran.h"
#include "Skill.h"

USkill::USkill() {
	curLevel = 1;
	curExp = 0.0;
}

USkill::USkill(int32 Score) {
	curLevel = Score >= 1 ? Score : 1;
	curExp = 0.0;
}

int32 USkill::GetCurrentLevel() const {
	return curLevel;
}

float USkill::GetCurrentExp() const {
	return curExp;
}

int32 USkill::GetCurrentExpCeiling() const {
	return (pow((float)curLevel, SKILL_EXP_GROWTH) * SKILL_MULT_GROWTH) + SKILL_OFFSET;	// MULT_GROWTH * (Level ^ EXP_GROWTH) + OFFSET
}

float USkill::GetExpToNextLevel() const {
	return GetCurrentExpCeiling() - curExp;
}

float USkill::GetCurrentExpPercentage() const {
	return GetCurrentExp() / GetCurrentExpCeiling();
}

void USkill::AddExperience(float ExpIncrease) {
	curExp += ExpIncrease;
	while (curExp >= GetCurrentExpCeiling()) {	//Level up as much as is appropriate
		levelUp();
	}
}

void USkill::AddLevels(int32 LevelIncrease) {
	while (LevelIncrease != 0) {
		curExp += GetCurrentExpCeiling();
		levelUp();
	}
}

void USkill::SetLevel(int32 TargetLevel) {
	curLevel = TargetLevel;
	// TODO: This will probably need updating.
}

void USkill::levelUp() {
	curExp -= GetCurrentExpCeiling();	//Remove the EXP used to level-up
	curLevel++;							//Add the level
	// TODO: Notify player of level-up via interface
}