// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Faction.h"
#include "SkillSet.h"
//#include "SkillSetTransient.h"
#include "Equipment.h"
#include "Inventory.h"
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

	UFUNCTION()
	AController* GetController() const;

	UFUNCTION(BlueprintPure, Category = "Combat")
	virtual bool CanAttackQuery() const;
	UFUNCTION(BlueprintImplementableEvent, Category = "Combat")		// Implemented in blueprints
	void CharacterPlusNotifiedParried();
	UFUNCTION(BlueprintImplementableEvent, Category = "Combat")		// Implemented in blueprints
	void CharacterPlusNotifiedParryInitiate();
	UFUNCTION(BlueprintImplementableEvent, Category = "Combat")		// Implemented in blueprints
	void CharacterPlusNotifiedDeath();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void Damage(float DamageAmount);
	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual void Kill();

	UFUNCTION(BlueprintPure, Category = "Stats")
	USkillSet* GetSkillSet() const;
	UFUNCTION(BlueprintPure, Category = "Stats")
	int32 GetCurrentLevel() const;
	UFUNCTION(BlueprintPure, Category = "Stats")
	UAbility* GetAbility(FName AbilityName) const;
	UFUNCTION(BlueprintPure, Category = "Stats")
	USkill* GetSkill(FName SkillName) const;

	UFUNCTION(BlueprintPure, Category = "Stats")
	float GetAnimationSpeedMultiplier() const;

	UFUNCTION(BlueprintPure, Category = "Stats")
	float GetHealthPercentage() const;
	UFUNCTION(BlueprintPure, Category = "Stats")
	float GetHealth() const;
	UFUNCTION(BlueprintPure, Category = "Stats")
	int32 GetMaxHealth() const;
	UFUNCTION(BlueprintPure, Category = "Stats")
	float GetSpiritPercentage() const;
	UFUNCTION(BlueprintPure, Category = "Stats")
	float GetSpirit() const;
	UFUNCTION(BlueprintPure, Category = "Stats")
	int32 GetMaxSpirit() const;

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void RecalculateMaxHealth();
	UFUNCTION(BlueprintCallable, Category = "Stats")
	void RecalculateMaxSpirit();

	UFUNCTION(BlueprintPure, Category = "Faction")
	bool IsCharacterHostileToCharacter(ACharacterPlus *Target) const;
	UFUNCTION(BlueprintPure, Category = "Faction")
	bool IsCharacterHostileToFaction(int32 ID) const;

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void EquipU(UClass * ToEquip);
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void Equip(UItem * ToEquip);

	UFUNCTION(BlueprintPure, Category = "Items")
	UWeapon* GetEquippedWeapon() const;
	UFUNCTION(BlueprintPure, Category = "Items")
	UArmor* GetEquippedHead() const;
	UFUNCTION(BlueprintPure, Category = "Items")
	UArmor* GetEquippedTorso() const;
	UFUNCTION(BlueprintPure, Category = "Items")
	UArmor* GetEquippedArms() const;
	UFUNCTION(BlueprintPure, Category = "Items")
	UArmor* GetEquippedHands() const;
	UFUNCTION(BlueprintPure, Category = "Items")
	UArmor* GetEquippedLegs() const;
	UFUNCTION(BlueprintPure, Category = "Items")
	UArmor* GetEquippedFeet() const;
	UFUNCTION(BlueprintPure, Category = "Items")
	UArmor* GetEquippedRing() const;
	UFUNCTION(BlueprintPure, Category = "Items")
	UArmor* GetEquippedNeck() const;

	UFUNCTION(BlueprintPure, Category = "Combat")
	float GetEffectiveArmorValue() const;
	UFUNCTION(BlueprintPure, Category = "Combat")
	float GetRawArmorValue() const;

	UFUNCTION(BlueprintPure, Category = "Inventory")
	UInventory* GetInventory() const;

	UFUNCTION(BlueprintCallable, Category = Faction)
	int32 GetFactionID() const;

	UFUNCTION(BlueprintPure, Category = "Stats")
	bool IsDead() const;

	UPROPERTY(BlueprintReadWrite, Category = "Combat")
	bool CanAttack;
	UPROPERTY(BlueprintReadWrite, Category = "Combat")
	bool CanParry;
	UPROPERTY(BlueprintReadWrite, Category = "Combat")
	bool CanBeParried;



protected:
	UFUNCTION()
	void initEquips();
	UFUNCTION()
	void initInventory();

	UPROPERTY()
	USkeletalMeshComponent* staticMesh;

	UPROPERTY(SaveGame)
	USkillSet *Skills;

	//UPROPERTY(EditAnywhere, SaveGame, BlueprintReadOnly, Category = "Vitals")
	//int32 MaxHealthOverride;
	UPROPERTY(SaveGame, BlueprintReadOnly, Category = "Vitals")
	int32 MaxHealth;
	UPROPERTY(SaveGame, BlueprintReadOnly, Category = "Vitals")
	float Health;
	UPROPERTY(SaveGame, BlueprintReadOnly, Category = "Vitals")
	int32 MaxSpirit;
	UPROPERTY(SaveGame, BlueprintReadOnly, Category = "Vitals")
	float Spirit;

	UPROPERTY(EditAnywhere, Category = "Abilities")
	int32 Level;
	UPROPERTY(EditAnywhere, Category = "Abilities")
	int32 Strength;
	UPROPERTY(EditAnywhere, Category = "Abilities")
	int32 Dexterity;
	UPROPERTY(EditAnywhere, Category = "Abilities")
	int32 Constitution;
	UPROPERTY(EditAnywhere, Category = "Abilities")
	int32 Intelligence;
	UPROPERTY(EditAnywhere, Category = "Abilities")
	int32 Wisdom;
	UPROPERTY(EditAnywhere, Category = "Abilities")
	int32 Charisma;

	UPROPERTY(EditAnywhere, Category = "Skills")
	int32 LightWeapons;
	UPROPERTY(EditAnywhere, Category = "Skills")
	int32 Parry;
	UPROPERTY(EditAnywhere, Category = "Skills")
	int32 Transmutation;
	UPROPERTY(EditAnywhere, Category = "Skills")
	int32 Speechcraft;

	UPROPERTY(EditAnywhere, SaveGame, Category = "Faction")
	int32 FactionID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")		// The default equipment & inventory information for this character. Only store a Loadout-derived object here!
	UClass* Loadout;
	UPROPERTY(BlueprintReadWrite, SaveGame, Category = "Equipment")
	UEquipment* Equiped;
	UPROPERTY(BlueprintReadOnly, SaveGame, Category = "Inventory")
	UInventory* Inventory;

	UPROPERTY()
	bool isDeadPlus;
	
	UPROPERTY()
	UFaction *staticFaction;
};
