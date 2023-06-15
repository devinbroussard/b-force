// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/BoxComponent.h>
#include "Kismet/GameplayStatics.h"
#include "Hazard.generated.h"

UCLASS()
class BFORCE_API AHazard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHazard();

public:	
	/// <summary>
	/// Checks if the player collides
	/// </summary>
	/// <param name="OtherActor">The actor that collided with</param>
	void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UPROPERTY(EditAnywhere)
	/// <summary>
	/// The force to knock the player back
	/// </summary>
	float knockBack = 9000;
protected:
	/// <summary>
	/// Gets the pawn from the scene
	/// </summary>
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	/// <summary>
	/// Gets the collider
	/// </summary>
	class UBoxComponent* collisionMesh;
	UPROPERTY(EditAnywhere)
	/// <summary>
	/// Gets the player pawn
	/// </summary>
	class ABForcePawn* m_player;
};
