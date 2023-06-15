// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BForcePawn.generated.h"

UCLASS(Config=Game)
class ABForcePawn : public APawn
{
	GENERATED_BODY()

	/** Used to change the position/rotation of our mesh (the mesh's origin is wrong, so we are using this to compensate). */
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UChildActorComponent* DarbeeMeshParent = nullptr;

	/** Spring arm that will offset the camera */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	UPROPERTY(Category = Collider, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* Collider;

	/** Camera component that will be our viewpoint */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	/** Used to change the position/rotation of our mesh (the mesh's origin is wrong, so we are using this to compensate). */
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UChildActorComponent* IndicatorParentActor;

	/** StatcMesh component that will point towards the next checkpoint in the scene. */
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* NextCheckpointPointer;

public: 
	/** Temporarily changes the player's current and max speeds to the given speed value */
	UFUNCTION(BlueprintCallable)
	void Boost(float Speed);

	UFUNCTION(BlueprintCallable)
	void SetCurrentForwardSpeed(float Speed) { CurrentForwardSpeed = Speed; }

	UFUNCTION(BlueprintCallable)
	float GetForwardSpeed() { return CurrentForwardSpeed; }
	
	UFUNCTION(BlueprintCallable)
	float GetOriginalMaxSpeed() { return OriginalMaxSpeed; }

	UFUNCTION(BlueprintCallable)
	FVector GetMovementDirection() { return MovementDirection; }

	UFUNCTION(BlueprintCallable)
	bool bGetIsDrifting() { return bIsDrifting; }

	UFUNCTION(BlueprintCallable)
	bool bGetIsDriftingRight() { return bIsDriftingRight; }

	UFUNCTION(BlueprintCallable)
	float GetCurrentDriftTime() { return CurrentDriftTime; }

	UFUNCTION(BlueprintCallable)
	bool bGetIsBoosting();


	ABForcePawn();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

protected:

	// Begin APawn overrides
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override; // Allows binding actions/axes to functions
	// End APawn overrides

	/** Bound to the thrust axis */
	void ThrustInput(float Val);

	/** Bound to the horizontal axis */
	void MoveRightInput(float Val);

	/** Bound to the drift axis */
	void DriftInput(float Val);

private:

	/** How quickly forward speed changes */
	UPROPERTY(Category=Plane, EditAnywhere)
	float Acceleration;

	/** How quickly the pawn can steer */
	UPROPERTY(Category = Plane, EditAnywhere)
	float OriginalTurnSpeed;

	/** Max forward speed */
	UPROPERTY(Category = Pitch, EditAnywhere)
	float OriginalMaxSpeed;

	UPROPERTY(Category = Plane, EditAnywhere)
	float OriginalCameraFieldOfView;

	UPROPERTY(Category = Plane, EditAnywhere)
	float DriftingCameraFieldOfView;

	float CurrentMaxSpeed;

	/** Minimum forward speed */
	UPROPERTY(Category=Yaw, EditAnywhere)
	float MinSpeed;

	/** How high the pawn hovers above the terrain below it */
	UPROPERTY(Category = Plane, EditAnywhere)
	float HoverDistance;

	/** How fast the bee decends back down when gliding through the air */
	UPROPERTY(Category = Plane, EditAnywhere)
	float DescendSpeed;

	UPROPERTY(Category = Plane, EditAnywhere)
	float DriftSpeedBoostTime;

	UPROPERTY(Category = Plane, EditAnywhere)
	float DriftTurnSpeed;

	/** How fast the pawn moves while drifting */
	UPROPERTY(Category = Plane, EditAnywhere)
	float DriftMaxSpeed;

	/** How fast the pawn's speed boost is after drifting */
	UPROPERTY(Category = Plane, EditAnywhere)
	float DriftBoostSpeed;

	/** The pawn's current movement direction */
	FVector MovementDirection = { 0.f, 0.f, 0.f };

	/** Whether or not the pawn is drifting */
	bool bIsDrifting = false;

	/** Whether or not the pawn is currently turning */
	bool bIsTurning = false;

	/** Whether or not the pawn is drifting right */
	bool bIsDriftingRight = false;

	/** How long the pawn has been drifting */
	float CurrentDriftTime = 0.f;

	/** Current forward speed */
	float CurrentForwardSpeed;

	/** Current yaw speed */
	float CurrentYawSpeed;

	/** Current pitch speed */
	float CurrentPitchSpeed;

	/** Current roll speed */
	float CurrentRollSpeed;

	float TurnSpeed;

	/** The scene's current game manager */
	class AGameManager* GameManager;

	/** Sets the plane's yaw speed after receiving right input */
	void SetYawSpeed(float RightInput);

	void Hover();

	bool bIsPawnAtMaxTilt();

	/** Sets the pawn's max speed back to the original speed over time */
	void AdjustMaxSpeed();

	void AdjustCameraFieldOfView();

	void AdjustCheckpointPointer();

public:
	/** Returns SpringArm subobject **/
	FORCEINLINE class USpringArmComponent* GetSpringArm() const { return SpringArm; }
	/** Returns Camera subobject **/
	FORCEINLINE class UCameraComponent* GetCamera() const { return Camera; }
};
