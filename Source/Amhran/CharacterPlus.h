// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Faction.h"
#include "SkillSet.h"
#include "SkillSetTransient.h"
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
	void Damage(int32 DamageAmount);

	UFUNCTION(BlueprintPure, Category = Faction)
	bool IsCharacterHostileToCharacter(ACharacterPlus *Target);
	UFUNCTION(BlueprintPure, Category = Faction)
	bool IsCharacterHostileToFaction(int32 ID);

	UFUNCTION(BlueprintCallable, Category = Faction)
	int32 GetFactionID();

protected:
	UFUNCTION()
	TArray<ACharacterPlus*> MeleeCheck(float AttackRange, int32 SweepHalfAngle, bool SingleResult);

	UPROPERTY(SaveGame)
	USkillSet* Skills;	//Holds information about every skill & attribute the actor has
						//The below editable values are simply defaults-- they are not saved

	UPROPERTY(EditAnywhere, SaveGame, BlueprintReadOnly, Category = "Vitals")
	int32 MaxHealthOverride;
	UPROPERTY(SaveGame, BlueprintReadOnly, Category = "Vitals")
	int32 Health;
	UPROPERTY(EditAnywhere, SaveGame, BlueprintReadOnly, Category = "Vitals")
	int32 MaxSpiritOverride;
	UPROPERTY(SaveGame, BlueprintReadOnly, Category = "Vitals")
	int32 Spirit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	int32 Strength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	int32 Dexterity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	int32 Constitution;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	int32 Intelligence;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	int32 Wisdom;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	int32 Charisma;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skills")
	int32 LightWeapons;

	UPROPERTY(EditAnywhere, SaveGame, Category = "Faction")
	int32 FactionID;
	
	UFaction *staticFaction;
};
