// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Amhran.h"
#include "Item.h"
#include "Armor.generated.h"

/**
 * 
 */
UCLASS()
class AMHRAN_API UArmor : public UItem
{
	GENERATED_BODY()
public:
	UArmor();
	UFUNCTION()
	void Init(const UItem * other) override;
	UFUNCTION()
	float getProtection() const;
	UFUNCTION(BlueprintPure, Category = "Equipment")
	EArmorTypeEnum GetArmorType() const;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Armor)
	EArmorTypeEnum ArmorType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Armor)
	float Protection;
	
	// TODO: Add model support!!!
	
};
