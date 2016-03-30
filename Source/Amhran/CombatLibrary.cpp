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
	UClass *StaticCharacter = ACharacterPlus::StaticClass();

	FVector thisForward = Instigator->GetViewRotation().Vector();
	FVector thisPos = Instigator->GetActorLocation();

	size_t minAngle = 181;
	ACharacterPlus *bestHit = NULL;

	for (size_t i = 0, charaters = 0; i < Hits.Num(); i++) //Pull all CharacterPluses within the given angle to the out array
	{
		AActor *result = Hits[i].GetActor();
		if (result->GetClass()->IsChildOf(StaticCharacter)) //Only process ACharacterPluses
		{
			FVector resultRelativePos = result->GetActorLocation() - thisPos;
			resultRelativePos.Normalize();
			int Angle = abs((int)FMath::RadiansToDegrees(acosf(FVector::DotProduct(thisForward, resultRelativePos))));
			if (Angle <= SweepHalfAngle) //Add any hits within the sweep angle to the out array
			{
				if (SingleResult)
				{
					if (Angle < minAngle)	// Record the "Best" hit-- Closest to the center of cone.
					{
						minAngle = Angle;
						bestHit = Cast<ACharacterPlus>(result);
					}
				}
				else
					CharacterHits.Add(Cast<ACharacterPlus>(result));
			}
		}
	}
	if (SingleResult)
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