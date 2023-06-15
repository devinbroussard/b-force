// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
/// <summary>
/// The class responsible for managing the main menu blueprint
/// </summary>
class BFORCE_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	/// <summary>
	/// Starts the game by going to the scene with the name passed through the function
	/// </summary>
	void startGame(FName sceneName);

	UFUNCTION(BlueprintCallable)
	/// <summary>
	/// Quits the game from the main menu
	/// </summary>
	void quitGame();

private:
	/// <summary>
	/// Runs when the widget is first constructed on the screen
	/// </summary>
	void NativeConstruct() override;

private:
	/// <summary>
	/// A variable containing the scene manager
	/// </summary>
	class ASceneManager* m_sceneManager;
};
