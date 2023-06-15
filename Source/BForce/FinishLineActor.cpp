// Fill out your copyright notice in the Description page of Project Settings.


#include "FinishLineActor.h"
#include "TimeManager.h"

// Sets default values
AFinishLineActor::AFinishLineActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AFinishLineActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	//Checks if the FinishLine is active
	if (this->getIsActive())
	{
		//On collision stops the timer
		TimeManager->TimerStopped = true;
	}

	//Call the parents collision function
	Super::NotifyActorBeginOverlap(OtherActor);
}
