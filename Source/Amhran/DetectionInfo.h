// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "CharacterPlus.h"
#include "DetectionInfo.generated.h"

/**
 * 
 */
UCLASS()
class AMHRAN_API UDetectionInfo : public UObject
{
	GENERATED_BODY()
public:
	//UDetectionInfo(APawn *target, float detection, bool isVisible, bool success);
	//UDetectionInfo(APawn *target, float detection);
	//UDetectionInfo(); //Bad constructor. Shouldn't use.

	UFUNCTION()
	void Init(ACharacterPlus *target, float detection);

	//UFUNCTION()
	//UDetectionInfo(const UDetectionInfo & other);
//	UFUNCTION()
//	~UDetectionInfo();

	UFUNCTION(BlueprintCallable, Category = Behaviour)
	UDetectionInfo* makeDetectionInfo(ACharacterPlus *target, float detection);

	UFUNCTION(BlueprintCallable, Category = Behaviour)
	void addDetectionValue(float value);
	UFUNCTION(BlueprintCallable, Category = Behaviour)
	void setDetection(float value);

	UFUNCTION(BlueprintCallable, Category = Behaviour)
	ACharacterPlus* getTarget();
	UFUNCTION(BlueprintCallable, Category = Behaviour)
	float getDetection();
	//UFUNCTION(BlueprintCallable, Category = Behaviour)
	//bool getIsVisible();
	//UFUNCTION(BlueprintCallable, Category = Behaviour)
	//bool getSuccess();

protected:
	UPROPERTY()
	ACharacterPlus *Target;
	UPROPERTY()
	float Detection;
	//bool IsVisible;
	//bool Success;
};
