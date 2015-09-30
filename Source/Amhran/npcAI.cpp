// Fill out your copyright notice in the Description page of Project Settings.

#include "Amhran.h"
#include "npcAI.h"

AnpcAI::AnpcAI(const class FObjectInitializer & ObjectInitializer)
{
	isAlerted = false;
}

bool AnpcAI::PawnCanBeSeen(ACharacterPlus *target)
{
	if (target == NULL || GetPawn() == NULL)
	{
		return false;
	}
	FVector difference = target->GetActorLocation() - GetPawn()->GetActorLocation();
	float angle = FVector::DotProduct(difference, GetPawn()->GetActorRotation().Vector());

	if (LineOfSightTo(target, GetPawn()->GetActorLocation()) && angle > 0 && difference.Size() <= MAX_DETECTION_RANGE)
	{
		return true;
	}
	else
	{
		return false;
	}
}

float AnpcAI::Detect(ACharacterPlus *target, float ticksPerSec, float Modifier) //Visual detection of pawns, returns true if undetect should not be ticked
{
	if (ticksPerSec <= 0)
	{
		return -1.0;
	}
	float addDetection; //The amount of detection to add this tick
	int32 index;
	UDetectionInfo *DetInfo;

	if (target == NULL || GetPawn() == NULL) //Check our input
	{
		return -1.0;
	}
	
	index = FindDetectionInfo(target); //Find our target DetectionInfo

	if (index != -1) //If an info was found, store it
	{
		DetInfo = DetectionVector[index];
	}
	else //Otherwise, make a new one and store that
	{
		UDetectionInfo *newinfo = NewObject<UDetectionInfo>();
		newinfo->Init(target, 0.0);
		DetectionVector.Add(newinfo);
		DetInfo = DetectionVector.Last();
	}
	
	FVector difference = DetInfo->getTarget()->GetActorLocation() - GetPawn()->GetActorLocation();
	float distance = difference.Size();
	float angle = FMath::Acos(FVector::DotProduct(difference.GetSafeNormal(0.0), GetPawn()->GetActorRotation().Vector()));

	if (angle <= TIGHT_DETECTION_CONE) //Apply the angle penalty
		addDetection = TIGHT_PENALTY;
	else if (angle <= MID_DETECTION_CONE)
		addDetection = MID_PENALTY;
	else if (angle <= LOOSE_DETECTION_CONE)
		addDetection = LOOSE_PENALTY;
	else
	{
		addDetection = 0;
	}
	if (addDetection != 0)
	{
		if (distance >= DISTANCE_BEGIN_DROPOFF)
			addDetection *= CalcDistancePenalty(distance); //Apply the distance penalty

		if (addDetection < MIN_DETECTION_PER_SECOND)
			addDetection = 0;

		addDetection *= Modifier;
		if (isAlerted)
			addDetection *= ALERT_DETECTION_BONUS;

		if (addDetection >= INSTANT_DETECTION) //Instantly detect pawn
		{
			DetInfo->setDetection(100.0);
			return 100.0;
		}
		else //Tick normally
		{
			addDetection /= ticksPerSec;
			if (DetInfo->getDetection() + addDetection >= 100.0) // Did we detect the pawn?
			{
				DetInfo->setDetection(100.0); //Peg to 100 if we overshot
				DetectedEnemies.AddUnique(target);
				endAlert();
			}
			else
				DetInfo->addDetectionValue(addDetection);
			return DetInfo->getDetection();
		}
	}
	return DetInfo->getDetection(); //Return the old detection value: Nothing added.
}

float AnpcAI::Undetect(ACharacterPlus *target, float ticksPerSec, float Modifier) //Returns true if pawn has been fully undetected
{
	if (ticksPerSec <= 0)
	{
		return -1.0;
	}
	UDetectionInfo *DetInfo;
	int index = FindDetectionInfo(target); //Find our target DetectionInfo

	if (index == -1) //Break if no info was found
	{
		return -1.0;
	}
	ValidateInfo(index);
	DetInfo = DetectionVector[index];
	DetInfo->addDetectionValue((-DETECTION_COOLDOWN / ticksPerSec) * Modifier);
	
	if (DetInfo->getDetection() <= 0)
	{
		DetInfo->setDetection(0.0);
		return 0.0; //We have successfully undetected
	}
	return DetInfo->getDetection(); //Still undetecting
}

bool AnpcAI::isDetecting(ACharacterPlus *target)
{
	int index = FindDetectionInfo(target);

	if (index == -1)
	{
		return false;
	}
	else if (DetectionVector[index]->getDetection() > 0)
		return true;

	return false;
}

void AnpcAI::CreateAlertTimer(float SecondsToAlert)
{
	isAlerted = true;
	World->GetTimerManager().SetTimer(AlertTimerHandle, this, &AnpcAI::endAlert, SecondsToAlert, false);
}

void AnpcAI::endAlert()
{
	isAlerted = false;
	if (AlertTimerHandle.IsValid())
		World->GetTimerManager().ClearTimer(AlertTimerHandle);
}

float AnpcAI::getDetection(ACharacterPlus *target)
{
	if (target != NULL)
	{
		int32 index = FindDetectionInfo(target);
		if (index != -1)
			return DetectionVector[index]->getDetection();
	}
	return -1;
}

int32 AnpcAI::getDetectionVectorSize()
{
	return DetectionVector.Num();
}

bool AnpcAI::ValidateInfo(int32 index)
{
	if (DetectionVector[index]->getTarget()->IsPendingKillPending()) //Remove references to actors who are dead or dying
	{
		DetectionVector.RemoveAt(index);
		return false;
	}
	return true;
}

bool AnpcAI::RemoveInfo(ACharacterPlus *target)
{
	int32 index = FindDetectionInfo(target);
	
	if (index != -1)
	{
		DetectionVector.RemoveAt(index);
		return true;
	}
	return false;
}

TArray<UDetectionInfo*> AnpcAI::getDetectionVector()
{
	return DetectionVector;
}

bool AnpcAI::IsEnemyDetected(ACharacterPlus* Target)
{
	return DetectedEnemies.Contains(Target);
}

void AnpcAI::RemoveDetectedEnemy(ACharacterPlus* Target)
{
	DetectedEnemies.Remove(Target);
}

float AnpcAI::CalcDistancePenalty(float distance)
{
	if (distance >= FAR)
		return CalcDistancePercent(MAX_DETECTION_RANGE, FAR, distance, MAX_PENALTY, FAR_PENALTY);
	else if (distance >= PROXIMITY)
		return CalcDistancePercent(FAR, PROXIMITY, distance, FAR_PENALTY, PROXIMITY_PENALTY);
	else if (distance >= NEAR)
		return CalcDistancePercent(PROXIMITY, NEAR, distance, PROXIMITY_PENALTY, NEAR_PENALTY);
	else if (distance >= CLOSE)
		return CalcDistancePercent(NEAR, CLOSE, distance, NEAR_PENALTY, CLOSE_PENALTY);
	else if (distance >= DISTANCE_BEGIN_DROPOFF)
		return CalcDistancePercent(CLOSE, DISTANCE_BEGIN_DROPOFF, distance, CLOSE_PENALTY, 1.0);

	return 1.0;
}

float AnpcAI::CalcDistancePercent(int32 upper, int32 lower, float distance, float upperPenalty, float lowerPenalty)
{
	float relativeDistance = distance - lower;
	float relativeUpper = upper - lower;

	return lowerPenalty + ((relativeDistance / relativeUpper) * upperPenalty);
}

int32 AnpcAI::FindDetectionInfo(ACharacterPlus* target)
{
	bool foundInfo = false;
	int foundIndex = -1;
	for (int i = 0; i < DetectionVector.Num() && !foundInfo; i++) //Iterate through the vector until we find our Info
	{
		if (DetectionVector[i]->getTarget() == target)
		{
			foundInfo = true;
			foundIndex = i;
		}
	}
	return foundIndex;
}