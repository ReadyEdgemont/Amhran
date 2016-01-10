// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Skill.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType)
class AMHRAN_API USkill : public UObject
{
	GENERATED_BODY()
	
public:
	USkill();
	USkill(int32 Score);
	UFUNCTION(BlueprintPure, Category = Skills)
	int32 GetCurrentLevel() const;
	UFUNCTION(BlueprintPure, Category = Skills)
	int32 GetCurrentExp() const;
	UFUNCTION(BlueprintPure, Category = Skills)
	int32 GetCurrentExpCeiling() const;
	UFUNCTION(BlueprintPure, Category = Skills)
	int32 GetExpToNextLevel() const;
	UFUNCTION(BlueprintCallable, Category = Skills)
	void AddExperience(int32 ExpIncrease);
	UFUNCTION(BlueprintCallable, Category = Skills)
	void AddLevels(int32 LevelIncrease);
	UFUNCTION(BlueprintCallable, Category = Skills)
	void SetLevel(int32 TargetLevel);
private:
	UFUNCTION()
	void levelUp();

	UPROPERTY(EditAnywhere, Category = "Stats")
	int32 curLevel;
	UPROPERTY(EditAnywhere, Category = "Stats")
	int32 curExp;
	
	
};
