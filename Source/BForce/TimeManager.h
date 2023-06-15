// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimeManager.generated.h"

/**
 * 
 */
UCLASS()
class BFORCE_API ATimeManager : public AActor
{
	GENERATED_BODY()
	
public:
	/// <summary>
	/// The value for minutes
	/// </summary>
	UPROPERTY(BlueprintReadWrite)
	int MinValue = 0;
	/// <summary>
	/// The value for seconds
	/// </summary>
	UPROPERTY(BlueprintReadWrite)
	int SecValue = 0;
	/// <summary>
	/// Checks if the timer has been stopped
	/// </summary>
	UPROPERTY(BlueprintReadWrite)
	bool TimerStopped;
	/// <summary>
	/// Value for the current lap
	/// </summary>
	UPROPERTY(BlueprintReadWrite)
	float CurrentLap = 0;
	/// <summary>
	/// The string to place the highscore
	/// </summary>
	UPROPERTY(BlueprintReadWrite)
	FString CurrentHighScore;
	/// <summary>
	/// Checks to stop the timer at any point
	/// </summary>
	UPROPERTY(BlueprintReadWrite)
	bool StopTime;
	/// <summary>
	/// The current value for deltaTime
	/// </summary>
	UPROPERTY(BlueprintReadWrite)
	float AddedDeltaTime = 0;
	UPROPERTY(BlueprintReadWrite)
	int CountdownTime;

private:
	/// <summary>
	/// Caculates the time by increaseing the seconds and minute values based on the deltaTime
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void CaculateCurrentTime(float DeltaSeconds);

	/// <summary>
	/// Resets the Timer values 
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void ResetTimer();
};
