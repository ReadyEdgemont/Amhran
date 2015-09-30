// Fill out your copyright notice in the Description page of Project Settings.

#include "Amhran.h"
#include "CharacterPlus.h"


// Sets default values
ACharacterPlus::ACharacterPlus()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	staticFaction = NewObject<UFaction>();
}

// Called when the game starts or when spawned
void ACharacterPlus::BeginPlay()
{
	Super::BeginPlay();
	
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

TArray<ACharacterPlus*> ACharacterPlus::MeleeCheck(float AttackRange, float SweepHalfAngle, bool SingleResult)
{
	const FVector StartTrace = GetActorLocation();
	const FVector ShootDir = GetActorRotation().Vector();
	const FVector EndTrace = StartTrace + ShootDir * AttackRange;



	//  We perform a sphere sweep, checking if there is something in the cylinder that trace creates.
	static FName WeaponFireTag = FName(TEXT("WeaponTrace"));
	FCollisionQueryParams TraceParams(WeaponFireTag, true);
	TraceParams.AddIgnoredActor(this);
	TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = true;

	//player + V = OBJ -> V = OBJ - player
	TArray<FHitResult> Hits;
	GetWorld()->SweepMultiByChannel(Hits, StartTrace, EndTrace, FQuat::Identity, ECollisionChannel::ECC_Pawn, FCollisionShape::MakeSphere(AttackRange), TraceParams);

	TArray <ACharacterPlus*> CharacterHits;
	UClass *StaticCharacter = ACharacterPlus::StaticClass();

	FVector thisForward = GetViewRotation().Vector();
	FVector thisPos = GetActorLocation();

	size_t minAngle = 181;
	ACharacterPlus *bestHit = NULL;

	for (size_t i = 0, charaters = 0; i < Hits.Num(); i++) //Pull all CharacterPluses within the given angle to the out array
	{
		AActor *result = Hits[i].GetActor();
		if (result->GetClass()->IsChildOf(StaticCharacter)) //Only process ACharacterPluses
		{
			FVector resultRelativePos = result->GetActorLocation() - thisPos;
			resultRelativePos.Normalize();
			float Angle = abs(FMath::RadiansToDegrees(acosf(FVector::DotProduct(thisForward, resultRelativePos))));
			if (Angle <= SweepHalfAngle) //Add any hits within the sweep angle to the out array
			{
				if (SingleResult)
				{
					if (Angle < minAngle)
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

TArray<ACharacterPlus*> ACharacterPlus::MeleeAttackCheckMulti(float AttackRange, float SweepHalfAngle)
{
	return MeleeCheck(AttackRange, SweepHalfAngle, false);
}

ACharacterPlus* ACharacterPlus::MeleeAttackCheckSingle(float AttackRange, float SweepHalfAngle)
{
	return (MeleeCheck(AttackRange, SweepHalfAngle, true))[0];
}

void ACharacterPlus::Damage(float Amount)
{
	if (Amount > 0)
	{
		Health -= Amount;
		if (Health <= 0) //Did we kill the NPC?
		{
			Health = 0;
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