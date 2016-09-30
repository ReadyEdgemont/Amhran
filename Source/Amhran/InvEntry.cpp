// Fill out your copyright notice in the Description page of Project Settings.

#include "Amhran.h"
#include "InvEntry.h"

void UInvEntry::Init(UItem* i, int32 q) {
	if(Cast<UWeapon>(i))
		Item = NewObject<UWeapon>();
	else if (Cast<UArmor>(i))
		Item = NewObject<UArmor>();
	else
		Item = NewObject<UItem>();
	Item->Init(i);
	Quantity = q;
}

UItem* UInvEntry::GetItem() const {
	return Item;
}

FName UInvEntry::GetName() const {
	return Item->GetName();
}

int32 UInvEntry::GetQuantity() const {
	return Quantity;
}

void UInvEntry::AddQuantity(int32 q) {
	Quantity += q;
}