// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WrongWayIndicatorWidget.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class BFORCE_API UWrongWayIndicatorWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	FString changeIndicatorText() { return m_wrongWayText; };

private:
	FString m_wrongWayText;
};
