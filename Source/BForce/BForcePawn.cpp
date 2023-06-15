// Copyright Epic Games, Inc. All Rights Reserved.

#include "BForcePawn.h"
#include "UObject/ConstructorHelpers.h"
#include "Math/UnrealMathUtility.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"
#include "Engine/StaticMesh.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/SkeletalMesh.h"
#include <BForce/GameManager.h>
#include "Components/ChildActorComponent.h"
#include <BForce/CheckpointActor.h>
#include "Engine/EngineTypes.h"
#include "Hazard.h"

ABForcePawn::ABForcePawn()
{
	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
		FConstructorStatics()
			: PlaneMesh(TEXT("/Game/Flying/Meshes/UFO.UFO"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("PlaneCollider0"));
	RootComponent = Collider;
	
	// Create a spring arm component
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm0"));
	SpringArm->SetupAttachment(RootComponent);	// Attach SpringArm to RootComponent
	SpringArm->TargetArmLength = 170.f; // The camera follows at this distance behind the character	
	SpringArm->SocketOffset = FVector(0.f,0.f,70.f);
	SpringArm->bEnableCameraLag = true;	// Do not allow camera to lag
	SpringArm->CameraLagSpeed = 5.f;
	SpringArm->CameraLagMaxDistance = 20.f;

	// Create camera component 
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera0"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);	// Attach the camera
	Camera->bUsePawnControlRotation = false; // Don't rotate camera with controller
	OriginalCameraFieldOfView = 115.f;
	Camera->FieldOfView = OriginalCameraFieldOfView;

	// Set handling parameters
	HoverDistance = 130.f;
	DescendSpeed = 500.f;
	Acceleration = 750.f;
	OriginalTurnSpeed = 75.f;
	TurnSpeed = OriginalTurnSpeed;
	OriginalMaxSpeed = 3000.f;
	CurrentMaxSpeed = OriginalMaxSpeed;
	DriftBoostSpeed = 5000.f;
	MinSpeed = -4000.f;
	CurrentForwardSpeed = 0.f;
	DriftSpeedBoostTime = 2.f;
	DriftTurnSpeed = 115.f;
	DriftMaxSpeed = 2800.f;
	DriftingCameraFieldOfView = 110.f;
}

void ABForcePawn::BeginPlay()
{
	Super::BeginPlay();
	CurrentForwardSpeed = 0.f;
	CurrentMaxSpeed = OriginalMaxSpeed;
	GameManager = Cast<AGameManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AGameManager::StaticClass()));
}

bool ABForcePawn::bGetIsBoosting()
{
	return CurrentMaxSpeed > OriginalMaxSpeed * 1.05f;
}

void ABForcePawn::Tick(float DeltaSeconds)
{
	if (!DarbeeMeshParent) {
		Super::Tick(DeltaSeconds);
		return;
	}

	const FVector WorldOffset = MovementDirection.GetSafeNormal() * CurrentForwardSpeed * DeltaSeconds;
	// Move plan forwards (with sweep so we stop when we collide with things)
	AddActorWorldOffset(WorldOffset, true);
	// Calculate change in rotation this frame
	FRotator MeshDeltaRotation(0, 0, 0);
	MeshDeltaRotation.Roll = CurrentRollSpeed * DeltaSeconds;
	// Rotate plane
	DarbeeMeshParent->AddLocalRotation(MeshDeltaRotation);
	
	FRotator DeltaRotation(0, 0, 0);
	DeltaRotation.Yaw = CurrentYawSpeed * DeltaSeconds;

	AddActorLocalRotation(DeltaRotation);

	AdjustMaxSpeed();
	AdjustCheckpointPointer();
	
	Hover();

	// Call any parent class Tick implementation
	Super::Tick(DeltaSeconds);
}
 
void ABForcePawn::NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	// Deflect along the surface when we collide.
	FRotator CurrentRotation = GetActorRotation();

	if (CurrentForwardSpeed > 0)
	{
		SetActorRotation(FMath::QInterpTo(CurrentRotation.Quaternion(), HitNormal.ToOrientationQuat(), GetWorld()->GetDeltaSeconds(), 3.f));
	}
	else if (CurrentForwardSpeed < 0)
	{
		// If the pawn is going backwards, deflect in the opposite direction
		FVector rightVector = HitNormal.ToOrientationQuat().GetRightVector();
		FVector currentVector = CurrentRotation.Vector() * -1.f;

		float distance1 = (rightVector - currentVector).Size();
		float distance2 = ((rightVector * -1.f) - currentVector).Size();

		int isRight = distance1 < distance2 ? -1.f : 1.f;
		
		FQuat newRotation = FMath::QInterpTo(CurrentRotation.Quaternion(), (HitNormal.ToOrientationQuat().Vector() * -1.f).ToOrientationQuat(), GetWorld()->GetDeltaSeconds(), 3.f);
		SetActorRotation(newRotation);
	}
}

void ABForcePawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    // Check if PlayerInputComponent is valid (not NULL)
	check(PlayerInputComponent);

	// Bind our control axis' to callback functions
	PlayerInputComponent->BindAxis("Thrust", this, &ABForcePawn::ThrustInput);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABForcePawn::MoveRightInput);
	PlayerInputComponent->BindAxis("Drift", this, &ABForcePawn::DriftInput);
}

void ABForcePawn::ThrustInput(float Val)
{
	if (!DarbeeMeshParent) {
		return;
	}

	Val = FMath::Clamp(Val, -1.f, 1.f);
	// Is there any input?
	bool bHasInput = !FMath::IsNearlyEqual(Val, 0.f);

	float deacceleration = FMath::IsNearlyEqual(CurrentForwardSpeed, 0.f, 0.5f) ? 0.f : -1.f * FMath::FInterpTo(CurrentForwardSpeed, 0, GetWorld()->GetDeltaSeconds(), 5.f);

	if (Val < 0.f)
	{
		Val = Val * 3.f;
	}

	// If input is not held down, reduce speed
	float CurrentAcc = bHasInput ? (Val * Acceleration) : deacceleration;
	// Calculate new speed
	float NewForwardSpeed = CurrentForwardSpeed + (GetWorld()->GetDeltaSeconds() * CurrentAcc);
	// Clamp between MinSpeed and MaxSpeed
	CurrentForwardSpeed = FMath::Clamp(NewForwardSpeed, MinSpeed, CurrentMaxSpeed);
}

void ABForcePawn::MoveRightInput(float Val)
{
	if (!DarbeeMeshParent) {
		return;
	}

	Val = FMath::Clamp(Val, -1.f, 1.f);
	bIsTurning = FMath::Abs(Val) > 0.2f;

	if (bIsDrifting)
	{
		Val = bIsDriftingRight ? FMath::Clamp(Val, -0.7f, 1.f) : FMath::Clamp(Val, -1.f, 0.7f);
	}
	else
	{
		bIsDriftingRight = Val > 0.f;
	}

	// Target yaw speed is based on input
	float TargetYawSpeed = (Val * TurnSpeed);

	// Smoothly interpolate to target yaw speed
	CurrentYawSpeed = FMath::FInterpTo(CurrentYawSpeed, TargetYawSpeed, GetWorld()->GetDeltaSeconds(), 2.f);

	float negativeRoll = FMath::FInterpTo(DarbeeMeshParent->GetRelativeRotation().Roll, 0, GetWorld()->GetDeltaSeconds(), 2.f) * -1.f;
	
	// If turning, yaw value is used to influence roll
	// If not turning, roll to reverse current roll value.
	float TargetRollSpeed = bIsTurning && !bIsPawnAtMaxTilt() ? (CurrentYawSpeed * 2.f) : negativeRoll;

	// Smoothly interpolate roll speed
	CurrentRollSpeed = FMath::FInterpTo(CurrentRollSpeed, TargetRollSpeed, GetWorld()->GetDeltaSeconds(), 10.f);
}

void ABForcePawn::DriftInput(float Val)
{
	if (!DarbeeMeshParent) {
		return;
	}

	Val = FMath::Clamp(Val, 0.f, 1.f);

	bool isDrifting = Val > 0 && CurrentForwardSpeed > (OriginalMaxSpeed * 0.4f);

	if (!bIsDrifting)
	{
		isDrifting = isDrifting && bIsTurning;
	}

	bIsDrifting = isDrifting;

	if (!bIsDrifting)
	{
		MovementDirection = FMath::VInterpTo(MovementDirection, GetActorForwardVector(), GetWorld()->GetDeltaSeconds(), 15.f);

		if (CurrentDriftTime > DriftSpeedBoostTime && CurrentForwardSpeed > (OriginalMaxSpeed * 0.7f) && CurrentMaxSpeed < OriginalMaxSpeed)
		{
			Boost(DriftBoostSpeed);
		}

		TurnSpeed = OriginalTurnSpeed;
		CurrentDriftTime = 0.f;
		return;
	}

	bIsDrifting = true;
	CurrentDriftTime += GetWorld()->GetDeltaSeconds();
	MovementDirection = FMath::VInterpTo(MovementDirection, GetActorForwardVector(), GetWorld()->GetDeltaSeconds(), 1.f);
	TurnSpeed = DriftTurnSpeed;
}

void ABForcePawn::Boost(float Speed)
{
	CurrentMaxSpeed = Speed;
	CurrentForwardSpeed = Speed;
}

void ABForcePawn::SetYawSpeed(float RightInput)
{
	float TargetYawSpeed = RightInput * TurnSpeed;

	// Smoothly interpolate to target yaw speed
	CurrentYawSpeed = FMath::FInterpTo(CurrentYawSpeed, TargetYawSpeed, GetWorld()->GetDeltaSeconds(), 3.f);
}

void ABForcePawn::Hover()
{
	FHitResult Hit;

	FVector belowPawn = GetActorLocation() + (GetActorUpVector() * HoverDistance * -1.5f);
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	//const FName TraceTag("MyTraceTag");
	//GetWorld()->DebugDrawTraceTag = TraceTag;
	//QueryParams.TraceTag = TraceTag;
	GetWorld()->LineTraceSingleByChannel(Hit, GetActorLocation(), belowPawn, ECC_Visibility, QueryParams);

	if (Hit.bBlockingHit && IsValid(Hit.GetActor()))
	{
		if (!FMath::IsNearlyEqual(Hit.Distance, HoverDistance, 5.f))
		{
			/* Setting the pawn's distance from the hit point. */
			FVector hitDirection = (GetActorLocation() - Hit.ImpactPoint).GetSafeNormal();
			FVector desiredLocation = Hit.ImpactPoint + (hitDirection * HoverDistance);

			/* FVector newLocation = FMath::Lerp(GetActorLocation(), desiredLocation, 0.15f); */
			FVector newLocation = FMath::VInterpTo(GetActorLocation(), desiredLocation, GetWorld()->GetDeltaSeconds(), 5.f);
			SetActorLocation(newLocation);
		}

		/* Setting the pawn's rotation based on the hit point. */
		FVector x = FVector::CrossProduct(Hit.Normal, GetActorUpVector()).GetSafeNormal();
		float yDegrees = FMath::Acos(FVector::DotProduct(Hit.Normal, GetActorUpVector())) * (180 / PI) * -1.f;
		FVector desiredRotation = GetActorForwardVector().RotateAngleAxis(yDegrees, x);

		FRotator y = FRotationMatrix::MakeFromZX(Hit.Normal, desiredRotation).Rotator();

		/* FRotator newRotation = FMath::Lerp(GetActorRotation(), y, 0.05f); */
		FRotator newRotation = FMath::RInterpTo(GetActorRotation(), y, GetWorld()->GetDeltaSeconds(), 5.f);
		SetActorRotation(newRotation);

		return;
	}

	/* Gradually reset rotation and lower to the ground */
	FRotator desiredRotation = GetActorRotation();
	desiredRotation.Pitch = 0.f;
	desiredRotation.Roll = 0.f;
	FRotator newRotation = FMath::RInterpTo(GetActorRotation(), desiredRotation, GetWorld()->GetDeltaSeconds(), 1.f);
	SetActorRotation(newRotation);

	FVector desiredLocation = GetActorLocation() + (FVector::UpVector * -1 * DescendSpeed);
	FVector newLocation = FMath::VInterpTo(GetActorLocation(), desiredLocation, GetWorld()->GetDeltaSeconds(), 3.f);
	SetActorLocation(newLocation);
}

bool ABForcePawn::bIsPawnAtMaxTilt()
{
	return DarbeeMeshParent->GetRelativeRotation().Roll > 20.f || DarbeeMeshParent->GetRelativeRotation().Roll < -20.f;
}

void ABForcePawn::AdjustMaxSpeed()
{
	if (CurrentMaxSpeed > OriginalMaxSpeed * 1.05 && !bIsDrifting)
	{
		CurrentRollSpeed = 900.f;
	}

	AdjustCameraFieldOfView();

	CurrentMaxSpeed = FMath::FInterpTo(CurrentMaxSpeed, bIsDrifting ? DriftMaxSpeed :OriginalMaxSpeed, GetWorld()->GetDeltaSeconds(), 2.f);
}

void ABForcePawn::AdjustCameraFieldOfView()
{
	Camera->FieldOfView = FMath::FInterpTo(
		Camera->FieldOfView,
		FMath::Clamp(
		(CurrentMaxSpeed / OriginalMaxSpeed) * OriginalCameraFieldOfView,
		OriginalCameraFieldOfView * 0.7f, bIsDrifting ? DriftingCameraFieldOfView : (OriginalCameraFieldOfView * 1.15f)),
		GetWorld()->GetDeltaSeconds(), 3.f
	);
}

void ABForcePawn::AdjustCheckpointPointer()
{
	if (!GameManager || !GameManager->getCurrentCheckpoint() || !IndicatorParentActor || !NextCheckpointPointer)
	{
		if (NextCheckpointPointer)
		{
			NextCheckpointPointer->SetVisibility(false);
		}

		return;
	}

	FVector checkpointLocation = GameManager->getNextCheckpoint()->GetActorLocation();
	FVector pointerLocation = IndicatorParentActor->GetComponentLocation();

	FVector pointerToCheckpointDirection = (checkpointLocation - pointerLocation).GetSafeNormal();
	FVector newRotationVector = FMath::VInterpTo(IndicatorParentActor->GetComponentRotation().Vector(), pointerToCheckpointDirection, GetWorld()->GetDeltaSeconds(), 5.f);
	FRotator newRotation = FVector(newRotationVector.X, newRotationVector.Y, 0).Rotation();
	IndicatorParentActor->SetWorldRotation(newRotation);
}
