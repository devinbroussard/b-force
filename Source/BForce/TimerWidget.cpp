// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerWidget.h"

FString UTimerWidget::changeTimerText(int secondValue, int minuteValue)
{
	FString finalTime;
	if (secondValue < 10)
	{
		m_secondText = "0" + FString::FromInt(secondValue);
	}
	else
	{
		m_secondText = FString::FromInt(secondValue);
	}
	
	if (minuteValue < 10)
	{
		m_minuteText = "0" + FString::FromInt(minuteValue);
	}
	else
	{
		m_minuteText = FString::FromInt(minuteValue);
	}

	finalTime = m_minuteText + ":" + m_secondText;

	return finalTime;
}
