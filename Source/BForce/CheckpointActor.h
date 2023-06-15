// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CheckpointActor.generated.h"

UCLASS(Blueprintable)
/// <summary>
/// An actor responsible for colliding with the player when they run into it, guiding them through the level
/// </summary>
class BFORCE_API ACheckpointActor : public AActor
{
	GENERATED_BODY()
	
public:	
	/// <summary>
	/// Sets default values for this actor's properties
	/// </summary>
	ACheckpointActor();
	/// <summary>
	/// Runs when the actor is collidede with by another actor
	/// </summary>
	/// <param name="otherActor">AActor</param>
	virtual void NotifyActorBeginOverlap(AActor* otherActor) override;

	/// <summary>
	/// Sets the game manager variable.
	/// </summary>
	/// <param name="manager">AGameManager</param>
	void setGameManager(class AGameManager* manager) { m_gameManager = manager; }
	/// <summary>
	/// Sets the checkpoint state to be active or inactive
	/// </summary>
	/// <param name="value">boolean</param>
	void setActive(bool value) { m_isActive = value; }

	UFUNCTION(BlueprintCallable)
	/// <summary>
	/// Returns the checkpoint's active state
	/// </summary>
	/// <returns>m_isActive</returns>
	bool getIsActive() { return m_isActive; }

protected:
	/// <summary>
	/// Runs when the level first loads up
	/// </summary>
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	/// <summary>
	/// The next checkpoint this checkpoint leads to
	/// </summary>
	class ACheckpointActor* NextCheckpoint;

	UPROPERTY(EditAnywhere)
	/// <summary>
	/// The previous checkpoint that leads to this checkpoint
	/// </summary>
	class ACheckpointActor* PreviousCheckpoint;

private:
	/// <summary>
	/// The game manager tracking the checkpoints in the scene
	/// </summary>
	class AGameManager* m_gameManager;

	/// <summary>
	/// Determines if the checkpoint can be collided with
	/// </summary>
	bool m_isActive = false;
};
