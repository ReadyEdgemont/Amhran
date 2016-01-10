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
UCLASS()
class AMHRAN_API USkillSet : public UObject
{
	GENERATED_BODY()

public:
	USkillSet();
	//USkillSet(const USkillSetTransient * const Transient);

	UFUNCTION(BlueprintPure, Category = Skills)
	USkill* GetSkill(FName SkillName);
	UFUNCTION(BlueprintPure, Category = Skills)
	UWeaponSkill* GetWeaponSkill(FName SkillName);
	UFUNCTION(BlueprintPure, Category = Skills)
	UAbility* GetAbility(FName AbilityName);
	//USkill& operator[] (std::size_t idx) override;

protected:
	UFUNCTION()
	void assignToTransient(const USkillSetTransient * const Transient);

	UPROPERTY(EditAnywhere, Category = "Skills")
	TArray<UWeaponSkill*> WeaponSkills;
	UPROPERTY(EditAnywhere, Category = "Skills")
	TArray<USkill*> OtherSkills;
	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<UAbility*> Abilities;

	UPROPERTY()
	TMap<FName, int32> nameDefines;		// Maps the names of skills + abilities to indecies
};
