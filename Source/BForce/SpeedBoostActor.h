// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpeedBoostActor.generated.h"

UCLASS()
/// <summary>
/// An actor responsible for giving the player a boost in speed when collided with
/// </summary>
class BFORCE_API ASpeedBoostActor : public AActor
{
	GENERATED_BODY()
	
public:	
	/// <summary>
	/// Sets default values for this actor's properties
	/// </summary>
	ASpeedBoostActor();
	/// <summary>
	/// Called when actor is collided with
	/// </summary>
	/// <param name="OtherActor"></param>
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	/// <summary>
	/// Called every Frame
	/// </summary>
	/// <param name="DeltaTime"></param>
	virtual void Tick(float DeltaTime) override;

protected:
	/// <summary>
	/// Called at the start of the game
	/// </summary>
	virtual void BeginPlay() override;

private:
	/// <summary>
	/// Changes the players forward speed to be maximum speed
	/// </summary>
	void setPlayerSpeed();

public:
	UPROPERTY(VisibleAnywhere)
	/// <summary>
	/// Box Collider
	/// </summary>
	class UBoxComponent* Box;

	UPROPERTY(EditAnywhere)
	/// <summary>
	/// The number the max speed is set to
	/// </summary>
	float SpeedboostSpeedIncrease = 8000;

	UPROPERTY(EditAnywhere)
	/// <summary>
	/// How long it takes for the timer to respawn;
	/// </summary>
	int RespawnTime = 500;

private:
	/// <summary>
	/// A refrence to the player
	/// </summary>
	class ABForcePawn* m_player;
	/// <summary>
	/// The timer that counts up to the respawn time
	/// </summary>
	int m_timer = 0;
	/// <summary>
	/// Determines if the speed boost is active and visible to the player
	/// </summary>
	bool m_isActive;
};
