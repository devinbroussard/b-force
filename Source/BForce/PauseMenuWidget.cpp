// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenuWidget.h"
#include "SceneManager.h"
#include <Kismet/GameplayStatics.h>

void UPauseMenuWidget::toMainMenu(FName sceneName)
{
	//Load Main menu level
	m_sceneManager->loadScene(sceneName);
}

void UPauseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_sceneManager = Cast<ASceneManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ASceneManager::StaticClass()));
}

void UPauseMenuWidget::closePauseMenu()
{
	m_controller->bShowMouseCursor = false;
	this->RemoveFromParent();
	UGameplayStatics::SetGamePaused(GetWorld(), false);
}
