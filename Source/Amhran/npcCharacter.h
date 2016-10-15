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
		// Adds the given integer to the NPC's disposition. Snaps to [0,100]. Can optionally set an absolute disposition value.
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void ModifyDisposition(int32 Amount, bool Set);
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	float GetDispositionPercentage() const;
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	int GetDisposition() const;

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	FName GetName() const;

	UFUNCTION(BlueprintPure, Category = Wrapper)
	float GetAlertTime() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float Awareness;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	int32 Disposition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	int32 BaseSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	FName WaypointPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	float attackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quests")
	bool IsImportant;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior")
	float AlertTime;
};
