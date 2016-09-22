// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "AmhranPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class AMHRAN_API AAmhranPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "User Interface")
	void CenterMouse();
	
	
};
