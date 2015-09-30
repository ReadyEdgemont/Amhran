// Fill out your copyright notice in the Description page of Project Settings.

#include "Amhran.h"
#include "DetectionInfo.h"

/*UDetectionInfo::UDetectionInfo(APawn *target, float detection, bool isVisible, bool success)
{
	Target = target;
	Detection = detection;
	IsVisible = isVisible;
	Success = success;
}*/
//UDetectionInfo::UDetectionInfo(const UDetectionInfo & other)
//{
	
//}

/*UDetectionInfo::UDetectionInfo(APawn *target, float detection)
{
	Target = target;
	Detection = detection;
	//IsVisible = isVisible;
}

UDetectionInfo::UDetectionInfo() //Bad constructer. Shouldn't use.
{
	Target = NULL;
	Detection = 0.0;
	//IsVisible = false;
	//Success = false;
}*/

/*UDetectionInfo::UDetectionInfo(UDetectionInfo & other)
{
	Detection = other.getDetection();
	Target = other.Target;
}*/

void UDetectionInfo::Init(ACharacterPlus *target, float detection)
{
	Target = target;
	Detection = detection;
}

/*UDetectionInfo* UDetectionInfo::makeDetectionInfo(APawn *target, float detection, bool isVisible, bool success)
{
	return new UDetectionInfo(target, detection, isVisible, success);
}*/

UDetectionInfo* UDetectionInfo::makeDetectionInfo(ACharacterPlus *target, float detection)
{
	UDetectionInfo *newinfo = NewObject<UDetectionInfo>();
	newinfo->Init(target, detection);
	return newinfo;
}

/*UDetectionInfo::~UDetectionInfo()
{
	
}*/

void UDetectionInfo::addDetectionValue(float value)
{
	Detection += value;
}

void UDetectionInfo::setDetection(float value)
{
	Detection = value;
}

ACharacterPlus* UDetectionInfo::getTarget()
{
	return Target;
}

float UDetectionInfo::getDetection()
{
	return Detection;
}

/*bool UDetectionInfo::getIsVisible()
{
	return IsVisible;
}*/

/*bool UDetectionInfo::getSuccess()
{
	return Success;
}*/