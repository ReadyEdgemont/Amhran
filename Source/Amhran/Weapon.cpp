// Fill out your copyright notice in the Description page of Project Settings.

#include "Amhran.h"
#include "Weapon.h"

UWeapon::UWeapon() {
	Type = EItemTypeEnum::Weapon;
	Damage = DEFAULT_WEAPON_DAMAGE;
	Speed = DEFAULT_WEAPON_SPEED;
	Range = DEFAULT_WEAPON_RANGE;
}

void UWeapon::Init(const UItem * other) {
	Super::Init(other);
	const UWeapon* otherW = Cast<UWeapon>(other);
	WeaponType = otherW->WeaponType;
	Damage = otherW->Damage;
	Speed = otherW->Speed;
	Range = otherW->Range;
}

float UWeapon::GetAttackRange() const {
	return Range;
}

float UWeapon::GetDamage() const {
	return Damage;
}