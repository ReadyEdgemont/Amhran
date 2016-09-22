// Fill out your copyright notice in the Description page of Project Settings.

#include "Amhran.h"
#include "CombatLibrary.h"

TArray<ACharacterPlus*> UCombatLibrary::MeleeCheck(float AttackRange, int32 SweepHalfAngle, ACharacterPlus *Instigator, bool SingleResult)
{
	const FVector StartTrace = Instigator->GetActorLocation();
	const FVector ShootDir = Instigator->GetActorRotation().Vector();
	const FVector EndTrace = StartTrace + ShootDir * AttackRange;



	//  We perform a sphere sweep, checking if there is something in the cylinder that trace creates.
	static FName WeaponFireTag = FName(TEXT("WeaponTrace"));
	FCollisionQueryParams TraceParams(WeaponFireTag, true);
	TraceParams.AddIgnoredActor(Instigator);
	TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = true;

	//player + V = OBJ -> V = OBJ - player
	TArray<FHitResult> Hits;
	Instigator->GetWorld()->SweepMultiByChannel(Hits, StartTrace, EndTrace, FQuat::Identity, ECollisionChannel::ECC_Pawn, FCollisionShape::MakeSphere(AttackRange), TraceParams);

	TArray <ACharacterPlus*> CharacterHits;

	FVector thisForward = Instigator->GetViewRotation().Vector();
	FVector thisPos = Instigator->GetActorLocation();

	size_t minAngle = 181;
	ACharacterPlus *bestHit = NULL;

	for (size_t i = 0, charaters = 0; i < Hits.Num(); i++) //Pull all CharacterPluses within the given angle to the out array
	{
		AActor *result = Hits[i].GetActor();
		ACharacterPlus* charpResult = Cast<ACharacterPlus>(result);
		if (charpResult) //Only process ACharacterPluses
		{
			FVector resultRelativePos = charpResult->GetActorLocation() - thisPos;
			resultRelativePos.Normalize();
			int Angle = abs((int)FMath::RadiansToDegrees(acosf(FVector::DotProduct(thisForward, resultRelativePos))));
			if (Angle <= SweepHalfAngle) //Add any hits within the sweep angle to the out array
			{
				if (SingleResult)
				{
					if (Angle < minAngle)	// Record the "Best" hit-- Closest to the center of cone.
					{
						minAngle = Angle;
						bestHit = charpResult;
					}
				}
				else
					CharacterHits.Add(charpResult);
			}
		}
	}
	if (SingleResult && bestHit)
		CharacterHits.Add(bestHit);
	return CharacterHits; //NULL if no hit actors
}

TArray<ACharacterPlus*> UCombatLibrary::MeleeAttackCheckMulti(float AttackRange, float SweepHalfAngle, ACharacterPlus *Instigator)
{
	return MeleeCheck(AttackRange, SweepHalfAngle, Instigator, false);
}

ACharacterPlus* UCombatLibrary::MeleeAttackCheckSingle(float AttackRange, float SweepHalfAngle, ACharacterPlus *Instigator)
{
	TArray<ACharacterPlus*> results = MeleeCheck(AttackRange, SweepHalfAngle, Instigator, true);
	if(results.Num() != 0)
		return results[0];
	return NULL;
}

bool UCombatLibrary::Parry(float Range, float SweepHalfAngle, bool CanMultiParry, ACharacterPlus *Instigator) {
	if (!Instigator->CanParry)
		return false;
	TArray<ACharacterPlus*> results;
	if (CanMultiParry) {
		results = MeleeCheck(Range, SweepHalfAngle, Instigator, false);
		for (int i = 0; i < results.Num(); i++) {
			results[i]->CharacterPlusNotifiedParried();		// Notify the AI that we just parried the attack of
		}
		if (results.Num() != 0)
			return true;
	}
	else {
		results = MeleeCheck(Range, SweepHalfAngle, Instigator, true);
		if (results.Num() != 0) {
			results[0]->CharacterPlusNotifiedParried();		// Notify the AI that we just parried the attack of
			return true;
		}
	}
	return false;
}

int32 UCombatLibrary::ComputeDamageFromRaw(int32 RawDamage, USkillSet* Skills, UWeapon* Weapon) {
	return RawDamage + (RawDamage * DEFAULT_WEAPON_SKILL_DMG_MOD); // TODO: Create equation w/ STR and crap
}

void UCombatLibrary::AddExpFromDamage(int32 DamageDealt, UWeapon* Weapon) {
	//AddExperience(DamageDealt); // TODO: Create equation
}