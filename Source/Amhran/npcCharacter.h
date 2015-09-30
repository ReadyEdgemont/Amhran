// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CharacterPlus.h"
#include "Faction.h"
#include "npcCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AMHRAN_API AnpcCharacter : public ACharacterPlus
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintPure, Category = Wrapper)
	float GetAlertTime();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float Awareness;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	int32 BaseSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	FName WaypointPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	int32 attackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quests")
	bool IsImportant;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior")
	float AlertTime;
};
