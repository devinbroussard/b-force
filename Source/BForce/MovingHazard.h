// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hazard.h"
#include "MovingHazard.generated.h"

UCLASS(Blueprintable)
class BFORCE_API AMovingHazard : public AHazard
{
	GENERATED_BODY()

public:
	AMovingHazard();

public:
	/// <summary>
	/// Updates the location
	/// </summary>
	/// <param name="DeltaTime">The time</param>
	virtual void Tick(float DeltaTime) override;

	/// <summary>
	/// Returns the move forward bool
	/// </summary>
	/// <returns>bool</returns>
	UFUNCTION(BlueprintCallable)
	bool getMoveForward() { return moveforward; }

	
	UFUNCTION(BlueprintCallable)
	/// <summary>
	/// Returns the max distance
	/// </summary>
	/// <returns>FVector</returns>
	FVector getMaxDistance() { return MaxDistance; }

	UFUNCTION(BlueprintCallable)
	/// <summary>
	/// Returns the min distance
	/// </summary>
	/// <returns>FVector</returns>
	FVector getMinDistance() { return MinDistance; }

	// The movement direction.
	UFUNCTION(BlueprintCallable)
	FVector getMovementDirection() { return MovementDirection; }

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	FVector MaxDistance;
	UPROPERTY(EditAnywhere)
	FVector MinDistance;
	bool moveforward;
	UPROPERTY(EditAnywhere)
	float speed;

	FVector MovementDirection;
};
