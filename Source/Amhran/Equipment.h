// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Armor.h"
#include "Weapon.h"
#include "Object.h"
#include "Equipment.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class AMHRAN_API UEquipment : public UObject
{
	GENERATED_BODY()
public:
	UEquipment();
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void Assign(UEquipment *other);
	UFUNCTION()
	void AssignFromLoadout(UClass *other);

	UFUNCTION(BlueprintCallable, Category = "Equipment")		// TODO: Hook up correctly to ACharacterPlus and Inventory
	void EquipU(UClass *ToEquip);
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void Equip(UItem *ToEquip);
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	UItem* Unequip(EEquipmentTypeEnum Slot);

	UFUNCTION(BlueprintPure, Category = "Equipment")
	UWeapon* GetWeapon() const;
	UFUNCTION(BlueprintPure, Category = "Equipment")
	UArmor* GetHead() const;
	UFUNCTION(BlueprintPure, Category = "Equipment")
	UArmor* GetTorso() const;
	UFUNCTION(BlueprintPure, Category = "Equipment")
	UArmor* GetArms() const;
	UFUNCTION(BlueprintPure, Category = "Equipment")
	UArmor* GetHands() const;
	UFUNCTION(BlueprintPure, Category = "Equipment")
	UArmor* GetLegs() const;
	UFUNCTION(BlueprintPure, Category = "Equipment")
	UArmor* GetFeet() const;
	UFUNCTION(BlueprintPure, Category = "Equipment")
	UArmor* GetRing() const;
	UFUNCTION(BlueprintPure, Category = "Equipment")
	UArmor* GetNeck() const;

protected:
	UFUNCTION()
	void equipWeaponU(UClass *w);
	UFUNCTION()
	void equipArmorU(UClass *a);
	UFUNCTION()
	void equipWeapon(UWeapon *w);
	UFUNCTION()
	void equipArmor(UArmor *a);

	UFUNCTION()
	void initWeaponU(UWeapon * & w, UClass* other);
	UFUNCTION()
	void initArmorU(UArmor * & a, UClass* other);
	UFUNCTION()
	void initWeapon(UWeapon * & w, UWeapon* other);
	UFUNCTION()
	void initArmor(UArmor * & a, UArmor* other);

	UFUNCTION()
	UWeapon* unequipWeaponSlot(UWeapon * & wSlot);
	UFUNCTION()
	UArmor* unequipArmorSlot(UArmor * & aSlot);

	UPROPERTY()
		UWeapon* Weapon;
	UPROPERTY()
		UArmor* Head;
	UPROPERTY()
		UArmor* Torso;
	UPROPERTY()
		UArmor* Arms;
	UPROPERTY()
		UArmor* Hands;
	UPROPERTY()
		UArmor* Legs;
	UPROPERTY()
		UArmor* Feet;
	UPROPERTY()
		UArmor* Ring;
	UPROPERTY()
		UArmor* Neck;
};
