// Fill out your copyright notice in the Description page of Project Settings.

#include "Amhran.h"
#include "Ability.h"

UAbility::UAbility() {
	AbilityScore = ABILITY_DEFAULT_VALUE;
}

UAbility::UAbility(int32 Score) {
	AbilityScore = Score;
}

int32 UAbility::GetScore() const {
	return AbilityScore;
}

void UAbility::SetScore(int32 NewScore) {
	AbilityScore = NewScore;
}

void UAbility::Increase() {
	AbilityScore++;
}