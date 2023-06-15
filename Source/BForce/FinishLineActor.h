// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CheckpointActor.h"
#include <Components/BoxComponent.h>
#include "FinishLineActor.generated.h"

UCLASS(Blueprintable)
class BFORCE_API AFinishLineActor : public ACheckpointActor
{
	GENERATED_BODY()
	
public:	
	/// <summary>
	/// Sets default values for this actor's properties
	/// </summary>
	AFinishLineActor();

public:	
	/// <summary>
	/// Checks when an actor overlaps its collision
	/// Sets the timer to stop once overlapped
	/// </summary>
	/// <param name="OtherActor">The actor the overlapped the collider</param>
	void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:
	/// <summary>
	/// Gets the TimeManager in scene
	/// </summary>
	UPROPERTY(EditAnywhere)
	class ATimeManager* TimeManager;
};
