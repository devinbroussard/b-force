// Fill out your copyright notice in the Description page of Project Settings.


#include "SceneManager.h"
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetSystemLibrary.h>

void ASceneManager::loadScene(FName levelName)
{
	//Load the scene by name
	UGameplayStatics::OpenLevel(GetWorld(), levelName, TRAVEL_Absolute);
}

void ASceneManager::quit()
{
	//Quit the game
	UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, true);
}
