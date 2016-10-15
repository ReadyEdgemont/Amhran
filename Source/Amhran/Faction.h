// Fill out your copyright notice in the Description page of Project Settings.
//#ifndef FACTION_H
//#define FACTION_H
#pragma once

//#include "TMap"
#include "Object.h"
#include "Faction.generated.h"

#define NUMFACTIONS 3

/**
 * 
 */

USTRUCT()
struct FInnerMap {
	TArray<bool> imap;
	GENERATED_BODY()
};

UENUM()
enum class EFactions : uint8 {
	PLAYER			UMETA(DisplayName = "Player"),
	CIVILIANS		UMETA(DisplayName = "Civilians"),
	BANDITS			UMETA(DisplayName = "Bandits")
};

UCLASS()
class AMHRAN_API UFaction : public UObject
{
	GENERATED_BODY()
public:
	UFaction();

	UFUNCTION(BlueprintPure, Category = "Faction")
	bool IsFactionHostileToFaction(int32 id1, int32 id2);

protected:
	UFUNCTION()
	void addHostility(int32 id1, int32 id2);
	UFUNCTION()
	void correctIds(int32 & id1, int32 & id2);
	
	UPROPERTY()
	TArray<FInnerMap> map;
};

//#endif