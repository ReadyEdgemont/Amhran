// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CharacterPlus.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CombatLibrary.generated.h"

/**
 * 
 */
UCLASS()
class AMHRAN_API UCombatLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Combat)
	static TArray<ACharacterPlus*> MeleeAttackCheckMulti(float AttackRange, float SweepHalfAngle, ACharacterPlus *Instigator);
	UFUNCTION(BlueprintCallable, Category = Combat)
	static ACharacterPlus* MeleeAttackCheckSingle(float AttackRange, float SweepHalfAngle, ACharacterPlus *Instigator);
	
private:
	UFUNCTION()
	static TArray<ACharacterPlus*> MeleeCheck(float AttackRange, int32 SweepHalfAngle, ACharacterPlus *Instigator, bool SingleResult);
};
