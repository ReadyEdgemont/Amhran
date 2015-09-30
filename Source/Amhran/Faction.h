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
UCLASS()
class AMHRAN_API UFaction : public UObject
{
	GENERATED_BODY()
public:
	UFaction();

	UFUNCTION(BlueprintPure, Category = "Faction")
	bool IsFactionHostileToFaction(int32 id1, int32 id2);

	static enum { PLAYER = 0, CIVILIANS = 1, BANDITS = 2 };

protected:
	void addHostility(int32 id1, int32 id2);
	void correctIds(int32 & id1, int32 & id2);
	
	bool map[NUMFACTIONS][NUMFACTIONS];
};

//#endif