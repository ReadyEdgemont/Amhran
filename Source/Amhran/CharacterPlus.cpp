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
}

// Called when the game starts or when spawned
void ACharacterPlus::BeginPlay()
{
	Super::BeginPlay();

	CanAttack = true;
	CanBeParried = false;
	CanParry = true;

	// Grab the static mesh
	TArray<USkeletalMeshComponent*> Components;
	GetComponents<USkeletalMeshComponent>(Components);
	if (Components.Num() == 0) {
		staticMesh = NULL;
		
	}
	else
		staticMesh = Components[0];

			//Initialize the SkillSet
	USkillSetTransient *transient = NewObject<USkillSetTransient>();
	transient->Level = 1;
	transient->makeAbilityArray(Strength, Dexterity, Constitution, Intelligence, Wisdom, Charisma);
	transient->makeSkillArray(LightWeapons);
	Skills = NewObject<USkillSet>();
	Skills->assignToTransient(transient);

	RecalculateMaxHealth();
	RecalculateMaxSpirit();
	Health = MaxHealth;
	Spirit = MaxSpirit;

	initEquips();
	initInventory();

	CharacterPlusNotifiedParryInitiate();
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

AController* ACharacterPlus::GetController() const {
	return Cast<AController>(Controller);
}

bool ACharacterPlus::CanAttackQuery() const {
	return CanAttack;
}

void ACharacterPlus::Damage(float DamageAmount)
{
	Health -= DamageAmount;
	if (DamageAmount > 0)
	{
		if (Health <= 0) //Did we kill the NPC?
		{
			Health = 0;
			Kill();
		}
	}
	else {	// TODO: Clamp to max HP!

	}
}

void ACharacterPlus::Kill() {
	UE_LOG(LogTemp, Warning, TEXT("Actor has been Killed!"));
	if (staticMesh) {
		GetWorld()->GetFirstPlayerController()->ClientMessage(TEXT("Physics is being simulated on deadified mesh!"));
		UE_LOG(LogTemp, Warning, TEXT("Physics is being Simulated"));
		staticMesh->SetSimulatePhysics(true);
		//staticMesh->PutAllRigidBodiesToSleep();		// The nuke
	}
	CharacterPlusNotifiedDeath();
}

int32 ACharacterPlus::GetCurrentLevel() const {
	return Skills->GetCurrentLevel();
}

UAbility* ACharacterPlus::GetAbility(FName AbilityName) const {
	return Skills->GetAbility(AbilityName);
}

USkill* ACharacterPlus::GetSkill(FName SkillName) const {
	return Skills->GetSkill(SkillName);
}

float ACharacterPlus::GetHealthPercentage() const {
	return Health / (float)MaxHealth;
}

float ACharacterPlus::GetHealth() const {
	return Health;
}

float ACharacterPlus::GetSpiritPercentage() const {
	return Spirit / (float)MaxSpirit;
}

float ACharacterPlus::GetSpirit() const {
	return Spirit;
}

float ACharacterPlus::GetAnimationSpeedMultiplier() const {		// TODO: Make logarithmic
	return 1 - ((GetAbility("Dexterity")->GetScore() - 10) / 15);
}

void ACharacterPlus::RecalculateMaxHealth() {
	MaxHealth = 5 + (GetAbility("Constitution")->GetScore() / 2) * GetCurrentLevel();
}

void ACharacterPlus::RecalculateMaxSpirit() {
	MaxSpirit = GetAbility("Intelligence")->GetScore() * GetCurrentLevel();
}

bool ACharacterPlus::IsCharacterHostileToCharacter(ACharacterPlus *Target) const {
	return staticFaction->IsFactionHostileToFaction(FactionID, Target->GetFactionID());
}

bool ACharacterPlus::IsCharacterHostileToFaction(int32 ID) const {
	return staticFaction->IsFactionHostileToFaction(FactionID, ID);
}

void ACharacterPlus::Equip(UClass * toEquip) {
	if (toEquip->IsChildOf<UWeapon>()) {
		Equiped->equipWeapon(toEquip);
	}
	else if (toEquip->IsChildOf<UArmor>()) {
		Equiped->equipArmor(toEquip);
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("WARNING: Attempted to equip non-weapon, non-armor UClass from ACharacterPlus::Equip!!!"));
}

UWeapon* ACharacterPlus::GetEquippedWeapon() const {
	return Equiped->GetWeapon();
}

UArmor* ACharacterPlus::GetEquippedHead() const {
	return Equiped->GetHead();
}

UArmor* ACharacterPlus::GetEquippedTorso() const {
	return Equiped->GetTorso();
}

UArmor* ACharacterPlus::GetEquippedArms() const {
	return Equiped->GetArms();
}

UArmor* ACharacterPlus::GetEquippedHands() const {
	return Equiped->GetHands();
}

UArmor* ACharacterPlus::GetEquippedLegs() const {
	return Equiped->GetLegs();
}

UArmor* ACharacterPlus::GetEquippedFeet() const {
	return Equiped->GetFeet();
}

UArmor* ACharacterPlus::GetEquippedRing() const {
	return Equiped->GetRing();
}

UArmor* ACharacterPlus::GetEquippedNeck() const {
	return Equiped->GetNeck();
}

void ACharacterPlus::initEquips() {
	Equiped = NewObject<UEquipment>();
	Equiped->AssignFromLoadout(Loadout);
}

void ACharacterPlus::initInventory() {
	Inventory = NewObject<UInventory>();
	Inventory->AssignFromLoadout(Loadout);
}

float ACharacterPlus::GetEffectiveArmorValue() const {
	UEquipment* equips = Cast<UEquipment>(Loadout->GetDefaultObject());
	float totalVal = 0;

	return 0; // TODO: NOPE
}

float ACharacterPlus::GetRawArmorValue() const {
	UEquipment* equips = Cast<UEquipment>(Loadout->GetDefaultObject());
	float totalVal = 0;

	return totalVal; // TODO: NOPE
}

int32 ACharacterPlus::GetFactionID() const {
	return FactionID;
}