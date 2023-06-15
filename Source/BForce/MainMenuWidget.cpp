// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "SceneManager.h"
#include <Kismet/GameplayStatics.h>
 
void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_sceneManager = Cast<ASceneManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ASceneManager::StaticClass()));
}

void UMainMenuWidget::startGame(FName sceneName)
{
	//Remove from viewport
	this->RemoveFromParent();

	//Load the Bforce race level
	m_sceneManager->loadScene(sceneName);
}

void UMainMenuWidget::quitGame()
{
	//Quit the game
	m_sceneManager->quit();
}
