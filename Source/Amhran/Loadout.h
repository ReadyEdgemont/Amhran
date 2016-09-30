// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Loadout.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class AMHRAN_API ULoadout : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
		UClass* Weapon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
		UClass* Head;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
		UClass* Torso;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
		UClass* Arms;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
		UClass* Hands;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
		UClass* Legs;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
		UClass* Feet;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
		UClass* Ring;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
		UClass* Neck;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		TArray<UClass*> Inventory;
};
