// Fill out your copyright notice in the Description page of Project Settings.

#include "Amhran.h"
#include "CharacterPlus.h"


// Sets default values
ACharacterPlus::ACharacterPlus()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	staticFaction = NewObject<UFaction>();

	Strength = Dexterity = Constitution = Intelligence = Wisdom = Charisma = ABILITY_DEFAULT_VALUE;
	LightWeapons = SKILL_DEFAULT_VALUE;
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
	//Skills = new USkillSet(&transient);
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

TArray<ACharacterPlus*> ACharacterPlus::MeleeCheck(float AttackRange, int32 SweepHalfAngle, bool SingleResult)
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
			int Angle = abs((int)FMath::RadiansToDegrees(acosf(FVector::DotProduct(thisForward, resultRelativePos))));
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