

#include "Amhran.h"
#include "AmhranCharacter.h"
#include "TestProjectile.h"


AAmhranCharacter::AAmhranCharacter(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	//Setting up the camera
	FirstPersonCameraComponent = PCIP.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->AttachParent = GetCapsuleComponent();
	FirstPersonCameraComponent->RelativeLocation = FVector(0, 0, 50.0f + BaseEyeHeight); //Adjust camera height

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	FirstPersonMesh = PCIP.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("FirstPersonMesh"));
	FirstPersonMesh->SetOnlyOwnerSee(true);         // only the owning player will see this mesh
	FirstPersonMesh->AttachParent = FirstPersonCameraComponent;
	FirstPersonMesh->bCastDynamicShadow = false;
	FirstPersonMesh->CastShadow = false;

	// everyone but the owner can see the regular body mesh
	GetMesh()->SetOwnerNoSee(true);
}

void AAmhranCharacter::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	InputComponent->BindAxis("WalkForward", this, &AAmhranCharacter::WalkForward);
	InputComponent->BindAxis("WalkRight", this, &AAmhranCharacter::WalkRight);
	InputComponent->BindAxis("TurnPitch", this, &AAmhranCharacter::AddControllerYawInput);
	InputComponent->BindAxis("TurnYaw", this, &AAmhranCharacter::AddControllerPitchInput);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AAmhranCharacter::OnStartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &AAmhranCharacter::OnStopJump);
	InputComponent->BindAction("Fire1", IE_Pressed, this, &AAmhranCharacter::OnFire);
}

void AAmhranCharacter::WalkForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		FRotator Rotation = Controller->GetControlRotation();
		// Limit pitch when walking or falling
		if (GetCharacterMovement()->IsMovingOnGround() || CharacterMovement->IsFalling())
		{
			Rotation.Pitch = 0.0f;
		}
		// add movement in that direction
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AAmhranCharacter::WalkRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AAmhranCharacter::OnStartJump()
{
	bPressedJump = true;
}

void AAmhranCharacter::OnStopJump()
{
	bPressedJump = false;
}

void AAmhranCharacter::OnFire()
{
	// try and fire a projectile
	if (ProjectileClass != NULL)
	{
		// Get the camera transform
		FVector CameraLoc;
		FRotator CameraRot;
		GetActorEyesViewPoint(CameraLoc, CameraRot);
		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the camera to find the final muzzle position
		FVector const MuzzleLocation = CameraLoc + FTransform(CameraRot).TransformVector(MuzzleOffset);
		FRotator MuzzleRotation = CameraRot;
		MuzzleRotation.Pitch += 10.0f;          // skew the aim upwards a bit
		UWorld* const World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;
			// spawn the projectile at the muzzle
			ATestProjectile* const Projectile = World->SpawnActor<ATestProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile)
			{
				// find launch direction
				FVector const LaunchDir = MuzzleRotation.Vector();
				Projectile->InitVelocity(LaunchDir);
			}
		}
	}
}