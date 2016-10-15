// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Ability.h"
#include "WeaponSkill.h"
#include "SkillSetTransient.h"
#include "Skill.h"
#include "SkillSet.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class AMHRAN_API USkillSet : public UObject
{
	GENERATED_BODY()

public:
	USkillSet();
	USkillSet(const USkillSetTransient * const Transient);


	UFUNCTION(BlueprintPure, Category = "Stats")
	int32 GetCurrentLevel() const;
	UFUNCTION(BlueprintPure, Category = "Stats")
	USkill* GetSkill(FName SkillName) const;
	UFUNCTION(BlueprintPure, Category = "Stats")
	float GetSkillLevelPercentage(FName SkillName) const;
	UFUNCTION(BlueprintPure, Category = "Stats")
	UAbility* GetAbility(FName AbilityName) const;

	UFUNCTION(BlueprintPure, Category = "Stats")
	bool HasUnspentAbilityPoints() const;
	UFUNCTION(BlueprintPure, Category = "Stats")
	int32 GetUnspentAbilityPoints() const;
	UFUNCTION(BlueprintCallable, Category = "Stats")
	void IncreaseUnspentAbilityPoints(int32 Amount);
	UFUNCTION(BlueprintCallable, Category = "Stats")
	void SpendAbilityPoint();

	UFUNCTION(BlueprintPure, Category = "Stats")
	TArray<FText> GetAbilityNames() const;
	UFUNCTION(BlueprintPure, Category = "Stats")
	TArray<FText> GetSkillNames() const;

	UFUNCTION()
	void assignToTransient(const USkillSetTransient * const Transient);

protected:
	UFUNCTION()
	void registerAbility(FName abilityName, int32 id);
	UFUNCTION()
	void registerSkill(FName skillName, int32 id);

	UPROPERTY(EditAnywhere, Category = "Skills", SaveGame)
	TArray<USkill*> Skills;
	UPROPERTY(EditAnywhere, Category = "Abilities", SaveGame)
	TArray<UAbility*> Abilities;
	UPROPERTY(EditAnywhere, Category = "Skills", SaveGame)
	int32 Level;

	UPROPERTY(SaveGame)
	int32 unspentAbilityPoints;

	UPROPERTY()
	TMap<FName, int32> nameDefines;		// Maps the names of skills + abilities to indecies
	UPROPERTY()
	TArray<FText> abilityNames;
	UPROPERTY()
	TArray<FText> skillNames;
};
