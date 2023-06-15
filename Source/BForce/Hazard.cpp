// Fill out your copyright notice in the Description page of Project Settings.


#include "Hazard.h"
#include "BForcePawn.h"

// Sets default values
AHazard::AHazard()
{
	// Sets the box collider to the pawn
	collisionMesh = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	collisionMesh->SetupAttachment(RootComponent);
}

void AHazard::NotifyActorBeginOverlap(AActor* OtherActor)
{
	//Returns if the other actor is not teh player
	if (OtherActor != m_player)
	{
		return;
	}

	m_player->GetMovementDirection();
	// Sets the forces for forwards and backwards
	float LaunchForce = knockBack + m_player->GetForwardSpeed() / 2;
	float ReverseForce = knockBack - m_player->GetForwardSpeed();
	//if the player is moving revere
	if (m_player->GetForwardSpeed() <= 100)
	{
		// Moves the player using the force
		m_player->SetCurrentForwardSpeed(ReverseForce);
	}
	else 
	{
		// Moves the player using the force
		m_player->SetCurrentForwardSpeed(-LaunchForce);
	}
	
}

void AHazard::BeginPlay()
{
	Super::BeginPlay();
	m_player = Cast<ABForcePawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}
