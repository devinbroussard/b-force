// Fill out your copyright notice in the Description page of Project Settings.


#include "SpiderWebHazard.h"
#include "BForcePawn.h"

ASpiderWebHazard::ASpiderWebHazard() 
{
	//Sets the tick to be active
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}

void ASpiderWebHazard::NotifyActorBeginOverlap(AActor* OtherActor)
{
	//Gets the current player's speed
	float speed = m_player->GetForwardSpeed();
	//Inores spiderweb when going above max speed
	if (speed < m_player->GetOriginalMaxSpeed() * 1.2f)
	{ 
		// Sets the force
		float LaunchForce = knockBack + m_player->GetForwardSpeed() / 4.5f;
		float ReverseForce = knockBack - m_player->GetForwardSpeed();
		//if the player is moving revere
		if (speed <= 100)
		{
			//Checks if the spiderweb is broken
			if(!IsBroken)
			{
				// Moves the player using the force
				m_player->SetCurrentForwardSpeed(ReverseForce);
				IsBroken = true;
			}	
		}
		else
		{
			//Checks if the spiderweb is broken
			if (!IsBroken) 
			{
				// Moves the player using the force
				m_player->SetCurrentForwardSpeed(-LaunchForce);
				IsBroken = true;
			}
		}
	}
	
}

void ASpiderWebHazard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//While spiderweb is broken countdown repair time
	if (IsBroken)
		RepairTime -= DeltaTime;
	//If repair time is zero spiderweb is not broken
	if (RepairTime <= 0)
	{
		IsBroken = false;
		RepairTime = 5;
	}
		
}

void ASpiderWebHazard::BeginPlay()
{
	Super::BeginPlay();
	//Sets the player to the pawn in the scene
	m_player = Cast<ABForcePawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}
