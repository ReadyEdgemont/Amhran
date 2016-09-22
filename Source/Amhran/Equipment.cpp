// Fill out your copyright notice in the Description page of Project Settings.

#include "Amhran.h"
#include "Equipment.h"
#include "Loadout.h"

void UEquipment::Assign (UEquipment * other) {
	Weapon = NewObject<UWeapon>();
	Weapon->Init(other->Weapon);

	Head = NewObject<UArmor>();
	Head->Init(other->Head);

	Torso = NewObject<UArmor>();
	Torso->Init(other->Torso);

	Arms = NewObject<UArmor>();
	Arms->Init(other->Arms);

	Hands = NewObject<UArmor>();
	Hands->Init(other->Hands);

	Legs = NewObject<UArmor>();
	Legs->Init(other->Legs);

	Feet = NewObject<UArmor>();
	Feet->Init(other->Feet);

	Neck = NewObject<UArmor>();
	Neck->Init(other->Neck);
}

void UEquipment::AssignFromLoadout(UClass * other) {
	ULoadout* loadout = Cast<ULoadout>(other->GetDefaultObject());

	Weapon = NewObject<UWeapon>();
	initWeapon(Weapon, loadout->Weapon);

	Head = NewObject<UArmor>();
	initArmor(Head, loadout->Head);

	Torso = NewObject<UArmor>();
	initArmor(Torso, loadout->Torso);

	Arms = NewObject<UArmor>();
	initArmor(Arms, loadout->Arms);

	Hands = NewObject<UArmor>();
	initArmor(Hands, loadout->Hands);

	Legs = NewObject<UArmor>();
	initArmor(Legs, loadout->Legs);

	Feet = NewObject<UArmor>();
	initArmor(Feet, loadout->Feet);

	Ring = NewObject<UArmor>();
	initArmor(Ring, loadout->Ring);

	Neck = NewObject<UArmor>();
	initArmor(Neck, loadout->Neck);
}

void UEquipment::initWeapon(UWeapon* w, UClass* other) {
	if(other)
		w->Init(Cast<UWeapon>(other->GetDefaultObject()));
}

void UEquipment::initArmor(UArmor* a, UClass* other) {
	if (other)
		a->Init(Cast<UArmor>(other->GetDefaultObject()));
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

void UEquipment::equipWeapon(UClass *w) {
	initWeapon(Weapon, w);
}

void UEquipment::equipArmor(UClass *a) {
	UArmor *armor = Cast<UArmor>(a->GetDefaultObject());
	EArmorTypeEnum aType = armor->GetArmorType();
	switch (aType) {
	case EArmorTypeEnum::Head:
		initArmor(Head, a);
		break;
	case EArmorTypeEnum::Torso:
		initArmor(Torso, a);
		break;
	case EArmorTypeEnum::Arms:
		initArmor(Arms, a);
		break;
	case EArmorTypeEnum::Hands:
		initArmor(Hands, a);
		break;
	case EArmorTypeEnum::Legs:
		initArmor(Legs, a);
		break;
	case EArmorTypeEnum::Feet:
		initArmor(Feet, a);
		break;
	case EArmorTypeEnum::Ring:
		initArmor(Ring, a);
		break;
	case EArmorTypeEnum::Neck:
		initArmor(Neck, a);
		break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("WARNING: Invalid ArmorType detected in UEquipment::equipArmor!!!"));
	};
}