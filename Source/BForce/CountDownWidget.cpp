// Fill out your copyright notice in the Description page of Project Settings.


#include "CountDownWidget.h"
#include "BForcePawn.h"
#include <Kismet/GameplayStatics.h>

void UCountDownWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_playerController = GetWorld()->GetFirstPlayerController();

	m_player = Cast<ABForcePawn>(UGameplayStatics::GetActorOfClass(GetWorld(), ABForcePawn::StaticClass()));

	//Disable the players input
	m_player->DisableInput(m_playerController);
}

void UCountDownWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	m_countdownTimer += InDeltaTime;

	if (m_countdownTimer >= CountdownTime)
	{
		CountdownDisplay--;
		m_countdownTimer = 0;

		if (CountdownDisplay == 0)
		{
			m_player->EnableInput(m_playerController);
			removeSelfFromViewport();
		}
	}
}

void UCountDownWidget::removeSelfFromViewport()
{
	this->RemoveFromParent();
}
