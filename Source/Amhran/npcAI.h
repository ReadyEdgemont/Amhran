// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "DetectionInfo.h"
#include "CharacterPlus.h"
#include "npcAI.generated.h"

/**
 * 
 */
UCLASS()
class AMHRAN_API AnpcAI : public AAIController
{
	GENERATED_BODY()
public:
	AnpcAI(const class FObjectInitializer & ObjectInitializer);

	UFUNCTION(BlueprintPure, Category = Behavior)
	bool PawnCanBeSeen(ACharacterPlus *target);

	UFUNCTION(BlueprintCallable, Category = Behavior)
	float Detect(ACharacterPlus *target, float ticksPerSec, float Modifier);
	UFUNCTION(BlueprintCallable, Category = Behavior)
	float Undetect(ACharacterPlus *target, float ticksPerSec, float Modifier);

	UFUNCTION(BlueprintPure, Category = Behavior)
	bool isDetecting(ACharacterPlus *target);

	UFUNCTION(BlueprintCallable, Category = Behavior)
	bool ValidateInfo(int32 index);
	UFUNCTION(BlueprintCallable, Category = Behavior)
	bool RemoveInfo(ACharacterPlus *target);

	UFUNCTION(BlueprintCallable, Category = Behavior)
	void CreateAlertTimer(float SecondsToAlert);

	UFUNCTION(BlueprintPure, Category = Debug)
	float getDetection(ACharacterPlus *target);
	UFUNCTION(BlueprintPure, Category = Debug)
	int32 getDetectionVectorSize();

	UFUNCTION()
	TArray<UDetectionInfo*> getDetectionVector();

	UFUNCTION(BlueprintPure, Category = Behavior)
	bool IsEnemyDetected(ACharacterPlus *Target);
	UFUNCTION(BlueprintCallable, Category = Behavior)
	void RemoveDetectedEnemy(ACharacterPlus *Target);

protected:
	UFUNCTION()
	float CalcDistancePenalty(float distance);
	UFUNCTION()
	float CalcDistancePercent(int32 upper, int32 lower, float distance, float upperPenalty, float lowerPenalty);

	UFUNCTION()
	int32 FindDetectionInfo(ACharacterPlus* target);

	UFUNCTION()
	void endAlert();

	UPROPERTY()
	TArray<UDetectionInfo*> DetectionVector;
	UPROPERTY(BlueprintReadWrite)
	TArray<ACharacterPlus*> DetectedEnemies;

	UPROPERTY()
	bool isAlerted;

	FTimerHandle AlertTimerHandle;

	UWorld *World = GetWorld();
};
