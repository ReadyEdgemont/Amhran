// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CombatLibrary.h"
#include "CharacterPlus.h"
#include "AmhranPlayer.generated.h"

/**
 * 
 */
UCLASS()
class AMHRAN_API AAmhranPlayer : public ACharacterPlus
{
	GENERATED_UCLASS_BODY()
protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UFUNCTION()
	void WalkForward(float Val);
	UFUNCTION()
	void WalkRight(float Val);
	UFUNCTION()
	void OnStartJump();
	UFUNCTION()
	void OnStopJump();
	UFUNCTION()
	void OnFire1();
	UFUNCTION()
	void OnFire2();

	//Set up the camera property
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ATestProjectile> ProjectileClass;

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* FirstPersonMesh;
};
