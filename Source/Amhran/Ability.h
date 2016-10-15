// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Ability.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class AMHRAN_API UAbility : public UObject
{
	GENERATED_BODY()
	
public:
	UAbility();
	UAbility(int32 Score);
	UFUNCTION(BlueprintPure, Category = "Skills")
	int32 GetScore() const;
	UFUNCTION(BlueprintCallable, Category = "Skills")
	void SetScore(int32 NewScore);
	UFUNCTION(BlueprintCallable, Category = "Skills")
	void Increase();
private:
	UPROPERTY(EditAnywhere, Category = "Vitals")
	int32 AbilityScore;
};
