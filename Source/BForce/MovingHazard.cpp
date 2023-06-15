// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingHazard.h"

AMovingHazard::AMovingHazard() 
{
	// Set this actor to call Tick() every frame.
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}

void AMovingHazard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Sets the actors location
	FVector Location = GetActorLocation();
	//Sets the offset location 
	FVector locationOffset = GetActorForwardVector() * speed * DeltaTime;

	//Checks if the Hazard is moving forward
	if (moveforward)
	{
		//Sets the newlocation for the hazard
		FVector newLocation = Location + locationOffset;
		MovementDirection = (Location - newLocation).GetSafeNormal();
		//Moves forward
		Location += locationOffset;
	}
	//If the Hazard is moving in reverse
	else
	{
		//Sets the newlocation for the hazard
		FVector newLocation = Location - locationOffset;
		MovementDirection = (Location - newLocation).GetSafeNormal();
		//Moves backwards
		Location -= locationOffset;
	}

	//Sets the Hazards new Location
	SetActorLocation(Location);

	// Checks if the locations x is greater than MaxDistance x
	if (Location.X > MaxDistance.X)
	{
		//if the max is reached set it to false
		moveforward = false;
	}
	// Checks if the locations x is less than MaxDistance x
	if (Location.X < MinDistance.X)
	{
		//if the min is reached set it to true
		moveforward = true;
	}
		
}

void AMovingHazard::BeginPlay()
{
	Super::BeginPlay();
	moveforward = true;
}
