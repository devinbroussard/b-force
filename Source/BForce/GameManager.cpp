// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"
#include "CheckpointActor.h"
#include "FinishLineActor.h"
#include "BForcePawn.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AGameManager::AGameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AGameManager::Tick(float DeltaTime)
{
	if (!m_nextCheckpoint->getIsActive())
	{
		m_nextCheckpoint->setActive(true);
	}

	if (m_currentCheckpoint->getIsActive())
	{
		m_currentCheckpoint->setActive(false);
	}

	m_nextCheckpoint = m_currentCheckpoint->NextCheckpoint;
}

// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
	Super::BeginPlay();
	m_currentCheckpoint = StartingCheckpoint;
	m_nextCheckpoint = m_currentCheckpoint->NextCheckpoint;
	m_nextCheckpoint->setActive(true);
}

