// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TimerWidget.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class BFORCE_API UTimerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	FString changeTimerText(int secondValue, int minuteValue);
	UFUNCTION(BlueprintCallable)
	FString GetSecondText() { return m_secondText; }
	UFUNCTION(BlueprintCallable)
	FString GetMinuteText() { return m_minuteText; }
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ATimeManager* TimeManager;

private:
	FString m_secondText;
	FString m_minuteText;
};
