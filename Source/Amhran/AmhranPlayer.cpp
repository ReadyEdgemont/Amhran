// Fill out your copyright notice in the Description page of Project Settings.

#include "Amhran.h"
#include "AmhranPlayer.h"
#include "TestProjectile.h"

AAmhranPlayer::AAmhranPlayer(const class FObjectInitializer& PCIP)
	//: Super((PCIP)
{
	FactionID = 0;
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

void AAmhranPlayer::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	InputComponent->BindAxis("WalkForward", this, &AAmhranPlayer::WalkForward);
	InputComponent->BindAxis("WalkRight", this, &AAmhranPlayer::WalkRight);
	InputComponent->BindAxis("TurnPitch", this, &AAmhranPlayer::AddControllerYawInput);
	InputComponent->BindAxis("TurnYaw", this, &AAmhranPlayer::AddControllerPitchInput);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AAmhranPlayer::OnStartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &AAmhranPlayer::OnStopJump);
	InputComponent->BindAction("Fire1", IE_Pressed, this, &AAmhranPlayer::OnFire);
}

void AAmhranPlayer::WalkForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		FRotator Rotation = Controller->GetControlRotation();
		// Limit pitch when walking or falling
		if (GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling())
		{
			Rotation.Pitch = 0.0f;
		}
		// add movement in that direction
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AAmhranPlayer::WalkRight(float Value)
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

void AAmhranPlayer::OnStartJump()
{
	bPressedJump = true;
}

void AAmhranPlayer::OnStopJump()
{
	bPressedJump = false;
}

void AAmhranPlayer::OnFire()
{
	ACharacterPlus *hit = NULL;
	if (CanAttack()) {
		hit = UCombatLibrary::MeleeAttackCheckSingle(250, 30, this);
	}
	if (hit) {
		UE_LOG(GeneralLog, Log, TEXT("Actor has been hit!"));
	}
}