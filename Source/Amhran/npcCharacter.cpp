// Fill out your copyright notice in the Description page of Project Settings.

#include "Amhran.h"
#include "npcCharacter.h"

void AnpcCharacter::ModifyDisposition(int32 Amount, bool Set) {
	if (Set)
		Disposition = Amount;
	else
		Disposition += Amount;
	FMath::Clamp(Disposition, 0, 100);
}

float AnpcCharacter::GetDispositionPercentage() const {
	return (float)Disposition / (float)100;
}

int AnpcCharacter::GetDisposition() const {
	return Disposition;
}

FName AnpcCharacter::GetName() const {
	return Name;
}

float AnpcCharacter::GetAlertTime() const {
	return AlertTime;
}