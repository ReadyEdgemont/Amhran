// Fill out your copyright notice in the Description page of Project Settings.

#include "Amhran.h"
#include "Weapon.h"

UWeapon::UWeapon() {
	Type = EItemTypeEnum::Weapon;
	Damage = DEFAULT_WEAPON_DAMAGE;
	Speed = DEFAULT_WEAPON_SPEED;
	Range = DEFAULT_WEAPON_RANGE;
}

void UWeapon::Init(const UWeapon * other) {
	WeaponType = other->WeaponType;
	Damage = other->Damage;
	Speed = other->Speed;
	Range = other->Range;
}