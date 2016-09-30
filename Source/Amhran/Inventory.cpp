// Fill out your copyright notice in the Description page of Project Settings.

#include "Amhran.h"
#include "Inventory.h"

UInventory::UInventory() {
	// Nothing to see here.
}

void UInventory::AssignFromLoadout(UClass *other) {
	ULoadout* loadout = Cast<ULoadout>(other->GetDefaultObject());
	if (!loadout)
		return;
	TArray<UClass*> loadoutItems = loadout->Inventory;

	for (auto& itemClass : loadoutItems) {		// For each item class in the loadout's item array . . .
		UItem *toAdd = Cast<UItem>(itemClass->GetDefaultObject());
		AddItemInQuantity(toAdd, toAdd->Quantity);
	}
}

void UInventory::AddItemU(UClass* ToAdd) {
	AddItemInQuantityU(ToAdd, 1);
}

void UInventory::AddItemInQuantityU(UClass* ToAdd, int32 Quantity) {
	UItem* item = Cast<UItem>(ToAdd->GetDefaultObject());
	AddItemInQuantity(item, Quantity);
}

void UInventory::AddItem(UItem* ToAdd) {
	AddItemInQuantity(ToAdd, 1);
}

void UInventory::AddItemInQuantity(UItem* ToAdd, int32 Quantity) {
	if (Quantity < 0) {
		UE_LOG(LogTemp, Warning, TEXT("Warning: Attempt to add negative quantity from inventory! Did you mean to use RemoveItem functions?"));
		return;
	}
	FName NameToAdd = ToAdd->GetName();
	if (items.Contains(NameToAdd)) {
		items[NameToAdd]->AddQuantity(Quantity);
	}
	else {
		UInvEntry *newEntry = NewObject<UInvEntry>();
		newEntry->Init(ToAdd, Quantity);
		items.Add(NameToAdd, newEntry);
	}
}

bool UInventory::RemoveItemU(UClass* ToRemove) {
	return RemoveItemInQuantityU(ToRemove, 1);
}

bool UInventory::RemoveItemInQuantityU(UClass* ToRemove, int32 Quantity) {
	UItem* item = Cast<UItem>(ToRemove->GetDefaultObject());
	return RemoveItemInQuantity(item, Quantity);
}

bool UInventory::RemoveItem(UItem* ToRemove) {
	return RemoveItemInQuantity(ToRemove, 1);
}

bool UInventory::RemoveItemInQuantity(UItem* ToRemove, int32 Quantity) {
	if (Quantity < 0) {
		UE_LOG(LogTemp, Warning, TEXT("Warning: Attempt to remove negative quantity from inventory! Did you mean to use AddItem functions?"));
		return false;
	}
	FName NameToRemove = ToRemove->GetName();
	if(!items.Contains(NameToRemove))
		return false;
	UInvEntry *entry = items[NameToRemove];
	if (entry->GetQuantity() < Quantity)
		return false;
	if (entry->GetQuantity() == Quantity) {
		items.Remove(NameToRemove);
		return true;
	}
	entry->AddQuantity(-Quantity);
	return true;
}

TArray<UItem*> UInventory::GetItemsInTab(EInventoryTabEnum tab) const {		// TODO
	TArray<uint8> targetTypes = getItemTypesInTab(tab);		// Tragically UE4 won't let us get a TArray of enums...
	TArray<UItem*> results;
	for (auto& elem : items) {		// For each item . . .
		UItem* found = elem.Value->GetItem();
		if (targetTypes.Contains((uint8)(found->GetType()))) {		// Add the found item to our result if it's in our tab
			results.Add(found);
		}
	}
	return results;
}

bool UInventory::HasItem(UItem* ToFind) const {
	return HasItemInQuantity(ToFind, 1);
}

bool UInventory::HasItemInQuantity(UItem* ToFind, int32 MinQuantity) const {
	FName NameToFind = ToFind->GetName();
	if(!items.Contains(NameToFind))
		return false;
	return items[NameToFind]->GetQuantity() >= MinQuantity;
}


TArray<uint8> UInventory::getItemTypesInTab(EInventoryTabEnum tab) const {		// I guess there's an engine bug with returning TArrays with enum templates?
//TArray<EItemTypeEnum> UInventory::getItemTypesInTab(EInventoryTabEnum tab) const {
	TArray<uint8> retArray;
	switch(tab) {
	case EInventoryTabEnum::All:
		retArray.Append(allArr, ARRAY_COUNT(allArr));
		break;
	case EInventoryTabEnum::Weapons:
		retArray.Append(weaponArr, ARRAY_COUNT(weaponArr));
		break;
	case EInventoryTabEnum::Armor:
		retArray.Append(armorArr, ARRAY_COUNT(armorArr));
		break;
	case EInventoryTabEnum::Mixtures:
		retArray.Append(mixtureArr, ARRAY_COUNT(mixtureArr));
		break;
	case  EInventoryTabEnum::Scrolls:
		retArray.Append(scrollArr, ARRAY_COUNT(scrollArr));
		break;
	case  EInventoryTabEnum::Materials:
		retArray.Append(materialArr, ARRAY_COUNT(materialArr));
		break;
	case  EInventoryTabEnum::Misc:
		retArray.Append(miscArr, ARRAY_COUNT(miscArr));
		break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("Warning: Attempt to access non-existant EInventoryTabEnum!"));
	};
	return retArray;
}