// Fill out your copyright notice in the Description page of Project Settings.

#include "Amhran.h"
#include "CharacterPlus.h"


// Sets default values
ACharacterPlus::ACharacterPlus()
{
 	// TODO: Determine if tick is necessary
	PrimaryActorTick.bCanEverTick = true;
	staticFaction = NewObject<UFaction>();

	Strength = Dexterity = Constitution = Intelligence = Wisdom = Charisma = ABILITY_DEFAULT_VALUE;
	LightWeapons = SKILL_DEFAULT_VALUE;
	Weapon = NewObject<UWeapon>();
}

// Called when the game starts or when spawned
void ACharacterPlus::BeginPlay()
{
	Super::BeginPlay();

			//Initialize the SkillSet
	USkillSetTransient *transient = NewObject<USkillSetTransient>();
	transient->makeAbilityArray(Strength, Dexterity, Constitution, Intelligence, Wisdom, Charisma);
	transient->makeWeaponSkillArray(LightWeapons);
	//USkillSetTransient *transient = new USkillSetTransient(Strength, Dexterity, Constitution, Intelligence, Wisdom, Charisma, LightWeapons);
	//Skills = new USkillSet(transient);
	Skills = NewObject<USkillSet>();
	Skills->assignToTransient(transient);
}

// Called every frame
void ACharacterPlus::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ACharacterPlus::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

bool ACharacterPlus::CanAttack() const {
	return true; // TODO: Fix this shit
}

void ACharacterPlus::Damage(int32 DamageAmount)
{
	if (DamageAmount > 0)
	{
		Health -= DamageAmount;
		if (DamageAmount <= 0) //Did we kill the NPC?
		{
			DamageAmount = 0;
		}
	}
}

bool ACharacterPlus::IsCharacterHostileToCharacter(ACharacterPlus *Target)
{
	return staticFaction->IsFactionHostileToFaction(FactionID, Target->GetFactionID());
}

bool ACharacterPlus::IsCharacterHostileToFaction(int32 ID)
{
	return staticFaction->IsFactionHostileToFaction(FactionID, ID);
}

int32 ACharacterPlus::GetFactionID()
{
	return FactionID;
}