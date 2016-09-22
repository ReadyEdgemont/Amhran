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
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void Assign(UEquipment *other);
	UFUNCTION()
	void AssignFromLoadout(UClass *other);

	UFUNCTION()
	void equipWeapon(UClass *w);
	UFUNCTION()
	void equipArmor(UClass *a);

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
	void initWeapon(UWeapon* w, UClass* other);
	UFUNCTION()
	void initArmor(UArmor* a, UClass* other);

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
