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
	//FirstPersonCameraComponent->AttachParent = GetCapsuleComponent();			//Obsoleted in 4.13
	FirstPersonCameraComponent->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::KeepWorldTransform);
	FirstPersonCameraComponent->RelativeLocation = FVector(0, 0, 50.0f + BaseEyeHeight); //Adjust camera height

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	FirstPersonMesh = PCIP.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("FirstPersonMesh"));
	FirstPersonMesh->SetOnlyOwnerSee(true);         // only the owning player will see this mesh
	//FirstPersonMesh->AttachParent = FirstPersonCameraComponent;
	FirstPersonMesh->AttachToComponent(FirstPersonCameraComponent, FAttachmentTransformRules::KeepWorldTransform);
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
	InputComponent->BindAction("Fire1", IE_Pressed, this, &AAmhranPlayer::OnFire1);
	InputComponent->BindAction("Fire2", IE_Pressed, this, &AAmhranPlayer::OnFire2);
	InputComponent->BindAction("Use", IE_Pressed, this, &AAmhranPlayer::OnUse);
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

void AAmhranPlayer::OnFire1()
{
	ACharacterPlus *hit = NULL;
	if (CanAttack) {
		hit = UCombatLibrary::MeleeAttackCheckSingle(GetEquippedWeapon()->GetAttackRange(), 30, this);
	}
	if (hit) {
		UWeapon* wep = GetEquippedWeapon();
		float dmg = UCombatLibrary::ComputeDamageFromWeapon(Skills, wep);
		hit->Damage(dmg);
		UCombatLibrary::AddExpFromDamage(dmg, wep, Skills);
	}
}

void AAmhranPlayer::OnFire2() {
	CharacterPlusNotifiedParryInitiate();
	UCombatLibrary::Parry(200, 30, false, this);		// TODO: Call this from an AnimMontage, block parry?
}

void AAmhranPlayer::OnUse() {
	UWorld *curWorld = GetWorld();
		// https://answers.unrealengine.com/questions/3446/how-would-i-use-line-trace-in-c.html
	FCollisionQueryParams TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
	TraceParams.bTraceComplex = true;
	TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = false;
	TraceParams.AddIgnoredActor(this);

	//Re-initialize hit info
	FHitResult Hit(ForceInit);
	FVector StartTrace; //= Instigator->GetActorLocation();
	//FVector ShootDir; //= Instigator->GetActorRotation().Vector();
	FRotator ShootDir;
	GetActorEyesViewPoint(StartTrace, ShootDir);
	const FVector EndTrace = StartTrace + ShootDir.Vector() * PLAYER_USE_RANGE;

		// Container Trace
	curWorld->LineTraceSingleByChannel(
		Hit,			//result
		StartTrace,		//start
		EndTrace,		//end
		COLLISION_CONTAINER,	//collision channel
		TraceParams);
	AActor *hitActor = Hit.GetActor();
	if (hitActor) {
		ACharacterPlus *hitCharacter = Cast<ACharacterPlus>(hitActor);
		if (hitCharacter) {
			PlayerNotifiedContainerOpened(hitCharacter->GetInventory());
		}
	}
		// Dialogue Initiation Trace
	else {
		curWorld->LineTraceSingleByChannel(
			Hit,			//result
			StartTrace,		//start
			EndTrace,		//end
			ECC_Pawn,		//collision channel
			TraceParams);
		hitActor = Hit.GetActor();
		if (hitActor) {
			AnpcCharacter *hitNPC = Cast<AnpcCharacter>(hitActor);
			if (hitNPC && !hitNPC->IsDead() && !hitNPC->IsCharacterHostileToCharacter(this)) {
				PlayerNotifiedDialogueInitiated(hitNPC);
			}
		}
	}
}

void AAmhranPlayer::Kill() {
	Super::Kill();
	(Cast<AAmhranPlayerController>(GetController()))->OnKill();
}