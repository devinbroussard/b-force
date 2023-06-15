// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameManager.generated.h"

UCLASS()
/// <summary>
/// An actor responsible for tracking the current checkpoint the player is at and the next checkpoint
/// the player is required to go to.
/// </summary>
class BFORCE_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	/// <summary>
	/// Sets default values for this actor's properties
	/// </summary>
	AGameManager();
	/// <summary>
	/// // Called every frame
	/// </summary>
	/// <param name="DeltaTime"> float</param>
	virtual void Tick(float DeltaTime) override;
	
	/// <summary>
	/// Sets the current checkpoint the game manager is tracking
	/// </summary>
	/// <param name="checkpoint"> ACheckpointActor </param>
	void setCurrentCheckpoint(class ACheckpointActor* checkpoint) { m_currentCheckpoint = checkpoint; }
	/// <summary>
	/// Returns the current checkpoint actor the game manager is tracking
	/// </summary>
	/// <returns> m_currentCheckpoint </returns>
	class ACheckpointActor* getCurrentCheckpoint() { return m_currentCheckpoint; }
	/// <summary>
	/// Returns the next checkpoint actor the game manager is tracking
	/// </summary>
	/// <returns>m_nextCheckpoint</returns>
	class ACheckpointActor* getNextCheckpoint() { return m_nextCheckpoint; }

protected:
	/// <summary>
	/// Called when the game starts or when spawned
	/// </summary>
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	/// <summary>
	/// The checkpoint the player is meant to start at
	/// </summary>
	class ACheckpointActor* StartingCheckpoint;

private:
	/// <summary>
	/// The current checkpoint being tracked by the game manager
	/// </summary>
	class ACheckpointActor* m_currentCheckpoint;
	/// <summary>
	/// The next checkpoint being tracked by the game manager
	/// </summary>
	class ACheckpointActor* m_nextCheckpoint;
};
