// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Item.h"
#include "Weapon.h"
#include "Armor.h"
#include "InvEntry.h"
#include "Loadout.h"
#include "Inventory.generated.h"

/**
 * 
 */
UCLASS()
class AMHRAN_API UInventory : public UObject
{
	GENERATED_BODY()
public:
	UInventory();

	UFUNCTION()
	void AssignFromLoadout(UClass *other);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddItemU(UClass* ToAdd);
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddItemInQuantityU(UClass* ToAdd, int32 Quantity);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddItem(UItem* ToAdd);
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddItemInQuantity(UItem* ToAdd, int32 Quantity);

	// Removes 1 quantity of item. Returns false if item does not exist.
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool RemoveItemU(UClass* ToRemove);
	// Returns false if item does not exist in quantity and no change is made
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool RemoveItemInQuantityU(UClass* ToRemove, int32 Quantity);

		// Removes 1 quantity of item. Returns false if item does not exist.
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool RemoveItem(UItem* ToRemove);
		// Returns false if item does not exist in quantity and no change is made
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool RemoveItemInQuantity(UItem* ToRemove, int32 Quantity);

	UFUNCTION(BlueprintPure, Category = "Inventory")
	TArray<UItem*> GetItemsInTab(EInventoryTabEnum tab) const;
	UFUNCTION(BlueprintPure, Category = "Inventory")
	bool HasItem(UItem* ToFind) const;
	UFUNCTION(BlueprintPure, Category = "Inventory")
	bool HasItemInQuantity(UItem* ToFind, int32 MinQuantity) const;

private:
	UFUNCTION()
	TArray<uint8> getItemTypesInTab(EInventoryTabEnum tab) const;
	//TArray<EItemTypeEnum> getItemTypesInTab(EInventoryTabEnum tab) const;

	UPROPERTY(SaveGame)
	TMap<FName, UInvEntry*> items;

		// TODO: Actually use
	UPROPERTY(SaveGame)
	float weight;

	// The only(?) dicey part of the inventory system. Not sure how to make this better...
	const uint8 allArr[7] = { (uint8)EItemTypeEnum::Weapon,  (uint8)(EItemTypeEnum::Armor), (uint8)(EItemTypeEnum::Potion),  (uint8)(EItemTypeEnum::Book),
		(uint8)(EItemTypeEnum::Scroll),  (uint8)(EItemTypeEnum::Material),  (uint8)(EItemTypeEnum::Misc) };
	const uint8 weaponArr[1] = { (uint8)EItemTypeEnum::Weapon };
	const uint8 armorArr[1] = { (uint8)EItemTypeEnum::Armor };
	const uint8 mixtureArr[2] = { (uint8)EItemTypeEnum::Potion, (uint8)EItemTypeEnum::Poison };
	const uint8 scrollArr[1] = { (uint8)EItemTypeEnum::Scroll };
	const uint8 materialArr[1] = { (uint8)EItemTypeEnum::Material };
	const uint8 miscArr[2] = { (uint8)EItemTypeEnum::Misc, (uint8)EItemTypeEnum::Book };
};
