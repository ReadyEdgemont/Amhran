// Fill out your copyright notice in the Description page of Project Settings.

#include "Amhran.h"
#include "Armor.h"

UArmor::UArmor() {
	Type = EItemTypeEnum::Armor;
}

void UArmor::Init(const UItem * other) {
	Super::Init(other);
	const UArmor* otherA = Cast<UArmor>(other);
	ArmorType = otherA->ArmorType;
	Protection = otherA->Protection;
}

float UArmor::getProtection() const {
	return Protection;
}

EArmorTypeEnum UArmor::GetArmorType() const {
	return ArmorType;
}