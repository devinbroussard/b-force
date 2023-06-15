// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hazard.h"
#include "SpiderWebHazard.generated.h"

/**
 * 
 */
UCLASS()
class BFORCE_API ASpiderWebHazard : public AHazard
{
	GENERATED_BODY()

public:
	/// <summary>
	/// The constructor for the spiderweb
	/// </summary>
	ASpiderWebHazard();
	/// <summary>
	/// Checks when an actor overlaps collision
	/// Launches the other actor with force based on their speed
	/// </summary>
	/// <param name="OtherActor">The actor that overlapped collision</param>
	void NotifyActorBeginOverlap(AActor* OtherActor) override;

	/// <summary>
	/// Ticks how long the spiderweb takes to rebuild from being broken 
	/// </summary>
	/// <param name="DeltaTime">The time it takes per tick</param>
	virtual void Tick(float DeltaTime) override;

	/// <summary>
	/// Gets whether or not the spiderweb is broken or not
	/// </summary>
	UFUNCTION(BlueprintCallable)
	bool GetIsBroken() { return IsBroken; }
protected:
	/// <summary>
	/// Gets the player from the scene
	/// </summary>
	virtual void BeginPlay() override;

private:
	/// <summary>
	/// Gets the player pawn
	/// </summary>
	class ABForcePawn* m_player;
	
	//Is the spiderwbe broken or not
	bool IsBroken = false;
	UPROPERTY(EditAnywhere)
	//Time it takes to repair the broken spiderweb
	float RepairTime = 3;
};
