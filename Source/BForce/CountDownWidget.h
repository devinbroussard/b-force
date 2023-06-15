// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CountDownWidget.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class BFORCE_API UCountDownWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeConstruct() override;
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void removeSelfFromViewport();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float CountdownTime = 4.0f;

	UPROPERTY(BlueprintReadWrite)
	int CountdownDisplay = 3;

private:
	class ABForcePawn* m_player;
	class APlayerController* m_playerController;
	float m_countdownTimer = 0;

};
