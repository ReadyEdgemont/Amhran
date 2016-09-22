// Fill out your copyright notice in the Description page of Project Settings.

#include "Amhran.h"
#include "Armor.h"

UArmor::UArmor() {
	Type = EItemTypeEnum::Armor;
}

void UArmor::Init(const UArmor * other) {
	ArmorType = other->ArmorType;
	Protection = other->Protection;
}

float UArmor::getProtection() const {
	return Protection;
}

EArmorTypeEnum UArmor::GetArmorType() const {
	return ArmorType;
}