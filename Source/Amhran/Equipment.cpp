// Fill out your copyright notice in the Description page of Project Settings.

#include "Amhran.h"
#include "Equipment.h"
#include "Loadout.h"

UEquipment::UEquipment() {
	Weapon = NULL;
	Head = Torso = Arms = Hands = Legs = Feet = Ring = Neck = NULL;
}

void UEquipment::Assign (UEquipment * other) {
	initWeapon(Weapon, other->Weapon);
	initArmor(Head, other->Head);
	initArmor(Torso, other->Torso);
	initArmor(Arms, other->Arms);
	initArmor(Hands, other->Hands);
	initArmor(Legs, other->Legs);
	initArmor(Feet, other->Feet);
	initArmor(Ring, other->Ring);
	initArmor(Neck, other->Neck);
}

void UEquipment::AssignFromLoadout(UClass * other) {
	ULoadout* loadout = Cast<ULoadout>(other->GetDefaultObject());

	initWeaponU(Weapon, loadout->Weapon);
	initArmorU(Head, loadout->Head);
	initArmorU(Torso, loadout->Torso);
	initArmorU(Arms, loadout->Arms);
	initArmorU(Hands, loadout->Hands);
	initArmorU(Legs, loadout->Legs);
	initArmorU(Feet, loadout->Feet);
	initArmorU(Ring, loadout->Ring);
	initArmorU(Neck, loadout->Neck);
}

void UEquipment::EquipU(UClass *ToEquip) {
	UItem *itemToEquip = Cast<UItem>(ToEquip->GetDefaultObject());
	Equip(itemToEquip);
}

void UEquipment::Equip(UItem *ToEquip) {
	UWeapon *wCast = Cast<UWeapon>(ToEquip);
	if (wCast) {
		equipWeapon(wCast);
		return;
	}
	UArmor *aCast = Cast<UArmor>(ToEquip);
	if (aCast) {
		equipArmor(aCast);
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("WARNING: Attempt to equip non-equippable in UEquipment::Equip!!!"));
}

UItem* UEquipment::Unequip(EEquipmentTypeEnum Slot) {

	switch (Slot) {
	case EEquipmentTypeEnum::Weapon:
		return unequipWeaponSlot(Weapon);
	case EEquipmentTypeEnum::Head:
		return unequipArmorSlot(Head);
	case EEquipmentTypeEnum::Torso:
		return unequipArmorSlot(Torso);
	case EEquipmentTypeEnum::Arms:
		return unequipArmorSlot(Arms);
	case EEquipmentTypeEnum::Hands:
		return unequipArmorSlot(Hands);
	case EEquipmentTypeEnum::Legs:
		return unequipArmorSlot(Legs);
	case EEquipmentTypeEnum::Feet:
		return unequipArmorSlot(Feet);
	case EEquipmentTypeEnum::Ring:
		return unequipArmorSlot(Ring);
	case EEquipmentTypeEnum::Neck:
		return unequipArmorSlot(Neck);
	default:
		UE_LOG(LogTemp, Warning, TEXT("WARNING: Invalid slot detected in UEquipment::Unequip!!!"));
	};
	return NULL;
}

UWeapon* UEquipment::GetWeapon() const{
	return Weapon;
}
UArmor* UEquipment::GetHead() const{
	return Head;
}
UArmor* UEquipment::GetTorso() const{
	return Torso;
}
UArmor* UEquipment::GetArms() const{
	return Arms;
}
UArmor* UEquipment::GetHands() const{
	return Hands;
}
UArmor* UEquipment::GetLegs() const {
	return Legs;
}
UArmor* UEquipment::GetFeet() const {
	return Feet;
}
UArmor* UEquipment::GetRing() const {
	return Ring;
}
UArmor* UEquipment::GetNeck() const {
	return Neck;
}

void UEquipment::equipWeaponU(UClass *w) {
	UWeapon *wOther = Cast<UWeapon>(w->GetDefaultObject());
	equipWeapon(wOther);
}

void UEquipment::equipArmorU(UClass *a) {
	UArmor *armor = Cast<UArmor>(a->GetDefaultObject());
	equipArmor(armor);
}

void UEquipment::equipWeapon(UWeapon *w) {
	initWeapon(Weapon, w);
}

void UEquipment::equipArmor(UArmor *a) {
	EEquipmentTypeEnum aType = a->GetArmorType();
	switch (aType) {
	case EEquipmentTypeEnum::Head:
		initArmor(Head, a);
		break;
	case EEquipmentTypeEnum::Torso:
		initArmor(Torso, a);
		break;
	case EEquipmentTypeEnum::Arms:
		initArmor(Arms, a);
		break;
	case EEquipmentTypeEnum::Hands:
		initArmor(Hands, a);
		break;
	case EEquipmentTypeEnum::Legs:
		initArmor(Legs, a);
		break;
	case EEquipmentTypeEnum::Feet:
		initArmor(Feet, a);
		break;
	case EEquipmentTypeEnum::Ring:
		initArmor(Ring, a);
		break;
	case EEquipmentTypeEnum::Neck:
		initArmor(Neck, a);
		break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("WARNING: Invalid ArmorType detected in UEquipment::equipArmor!!!"));
	};
}

void UEquipment::initWeaponU(UWeapon * & w, UClass* other) {
	if (other) {
		UWeapon *wOther = Cast<UWeapon>(other->GetDefaultObject());
		initWeapon(w, wOther);
	}
}

void UEquipment::initArmorU(UArmor * & a, UClass* other) {
	if (other) {
		UArmor *aOther = Cast<UArmor>(other->GetDefaultObject());
		initArmor(a, aOther);
	}
}

void UEquipment::initWeapon(UWeapon * & w, UWeapon* other) {
	if (other) {
		w = NewObject <UWeapon>();
		w->Init(other);
	}
}

void UEquipment::initArmor(UArmor * & a, UArmor* other) {
	if (other) {
		a = NewObject <UArmor>();
		a->Init(other);
	}
}

UWeapon* UEquipment::unequipWeaponSlot(UWeapon * & wSlot) {
	UWeapon* oldSlot = wSlot;
	wSlot = NULL;
	return oldSlot;
}

UArmor* UEquipment::unequipArmorSlot(UArmor * & aSlot) {
	UArmor* oldSlot = aSlot;
	aSlot = NULL;
	return oldSlot;
}