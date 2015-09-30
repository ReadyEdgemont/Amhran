// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Faction.h"
#include "GameFramework/Character.h"
#include "CharacterPlus.generated.h"

UCLASS()
class AMHRAN_API ACharacterPlus : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterPlus();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UFUNCTION(BlueprintCallable, Category = Combat)
	TArray<ACharacterPlus*> MeleeAttackCheckMulti(float AttackRange, float SweepHalfAngle);
	UFUNCTION(BlueprintCallable, Category = Combat)
	ACharacterPlus* MeleeAttackCheckSingle(float AttackRange, float SweepHalfAngle);
	UFUNCTION(BlueprintCallable, Category = Combat)
	void Damage(float Amount);

	UFUNCTION(BlueprintPure, Category = Faction)
	bool IsCharacterHostileToCharacter(ACharacterPlus *Target);
	UFUNCTION(BlueprintPure, Category = Faction)
	bool IsCharacterHostileToFaction(int32 ID);

	UFUNCTION(BlueprintCallable, Category = Faction)
	int32 GetFactionID();

protected:
	UFUNCTION()
	TArray<ACharacterPlus*> MeleeCheck(float AttackRange, float SweepHalfAngle, bool SingleResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float Spirit;

	UPROPERTY(EditAnywhere, Category = "Faction")
	int32 FactionID;
	
	UFaction *staticFaction;
};
