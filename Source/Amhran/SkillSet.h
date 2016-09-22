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
	USkillSet(const USkillSetTransient * const Transient);


	UFUNCTION(BlueprintPure, Category = Stats)
	int32 GetCurrentLevel() const;
	UFUNCTION(BlueprintPure, Category = Stats)
	USkill* GetSkill(FName SkillName) const;
	/*UFUNCTION(BlueprintPure, Category = Skills)
	UWeaponSkill* GetWeaponSkill(FName SkillName);*/
	UFUNCTION(BlueprintPure, Category = Stats)
	UAbility* GetAbility(FName AbilityName) const;
	//USkill& operator[] (std::size_t idx) override;
	UFUNCTION()
	void assignToTransient(const USkillSetTransient * const Transient);

protected:
	/*UPROPERTY(EditAnywhere, Category = "Skills")
	TArray<UWeaponSkill*> WeaponSkills;*/
	UPROPERTY(EditAnywhere, Category = "Skills")
	TArray<USkill*> Skills;
	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<UAbility*> Abilities;
	UPROPERTY(EditAnywhere, Category = "Vitals")
	int32 Level;

	UPROPERTY()
	TMap<FName, int32> nameDefines;		// Maps the names of skills + abilities to indecies
};
