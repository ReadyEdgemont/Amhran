// Fill out your copyright notice in the Description page of Project Settings.

#include "Amhran.h"
#include "Item.h"

UItem::UItem() {
	Type = EItemTypeEnum::Misc;
	Quantity = 1;
}

void UItem::Init(const UItem * other) {
	Name = other->GetName();
	Type = other->GetType();
}

FName UItem::GetName() const {
	return Name;
}

EItemTypeEnum UItem::GetType() const {
	return Type;
}