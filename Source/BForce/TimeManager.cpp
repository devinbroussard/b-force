// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeManager.h"
#include "GameFramework/GamestateBase.h"

void ATimeManager::CaculateCurrentTime(float DeltaSeconds)
{
	//Returns when the timer has stopped
	if (TimerStopped)
	{
		return;
	}
	//Sets the added deltaTime to be the DeltaSeconds
	AddedDeltaTime += DeltaSeconds;

	//If the deltaTime equal 1
	if (AddedDeltaTime >= 1)
	{
		//Increment teh seconds and reset the deltaTime
		SecValue++;
		AddedDeltaTime = 0;
	}
	//If seconds are greater than or equal to 60
	if (SecValue >= 60)
	{
		//Increment the minutes and reset the seconds
		MinValue++;
		SecValue = 0;
	}
}

void ATimeManager::ResetTimer()
{
	//resets the values to 0
	SecValue = 0;
	MinValue = 0;
	AddedDeltaTime = 0.0f;
}
