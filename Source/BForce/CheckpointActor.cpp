// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckpointActor.h"
#include "GameManager.h"
#include "FinishLineActor.h"
#include <Components/BoxComponent.h>
#include <Kismet/GameplayStatics.h>

ACheckpointActor::ACheckpointActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACheckpointActor::NotifyActorBeginOverlap(AActor* otherActor)
{
	if (m_isActive)
	{
		//Send checkpoint info to game manager
		m_gameManager->setCurrentCheckpoint(this);
	}
}

void ACheckpointActor::BeginPlay()
{
	if (NextCheckpoint)
	{
		NextCheckpoint->PreviousCheckpoint = this;
	}

	m_gameManager = Cast<AGameManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AGameManager::StaticClass()));

	Super::BeginPlay();
}

