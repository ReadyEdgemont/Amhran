

#pragma once

#include "GameFramework/Character.h"
#include "AmhranCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AMHRAN_API AAmhranCharacter : public ACharacter
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
	void OnFire();

	//Set up the camera property
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
    UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ATestProjectile> ProjectileClass;

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* FirstPersonMesh;
};
