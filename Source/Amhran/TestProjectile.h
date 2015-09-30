

#pragma once

#include "GameFramework/Actor.h"
#include "TestProjectile.generated.h"

/**
 * 
 */
UCLASS()
class AMHRAN_API ATestProjectile : public AActor
{
	GENERATED_UCLASS_BODY()

	void InitVelocity(const FVector& ShootDirection);

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	USphereComponent* CollisionComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	class UProjectileMovementComponent* ProjectileMovement;

	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
