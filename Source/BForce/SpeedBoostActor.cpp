// Fill out your copyright notice in the Description page of Project Settings.
 
#include "SpeedBoostActor.h"
#include <Components/SkeletalMeshComponent.h>
#include <Components/BoxComponent.h>
#include <Kismet/GameplayStatics.h>
#include "BForcePawn.h"

// Sets default values
ASpeedBoostActor::ASpeedBoostActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetWorldLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FQuat(0.0f, 0.0f, 0.0f, 0.0f));
	Box->SetupAttachment(RootComponent);
}

void ASpeedBoostActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	//Calls the set player speed method
	setPlayerSpeed();
}

void ASpeedBoostActor::Tick(float DeltaTime)
{
	if (!m_isActive)
	{
		m_timer++;
		// GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Green, FString::FromInt(m_timer));

		if (m_timer >= RespawnTime)
		{
			// GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Green, TEXT("Speed Boost should respawn"));
			m_timer = 0;
			this->SetActorHiddenInGame(false);
			m_isActive = true;
		}
	}

	Super::Tick(DeltaTime);
}

void ASpeedBoostActor::BeginPlay()
{
	m_player = Cast<ABForcePawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	m_isActive = true;
	Super::BeginPlay();
}

void ASpeedBoostActor::setPlayerSpeed()
{
	if (m_isActive)
	{
		//Calls the boost function
		m_player->Boost(SpeedboostSpeedIncrease);

		//Hide the actor
		this->SetActorHiddenInGame(true);

		//set the speedboost to inactive
		m_isActive = false;
	}
}
