// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenuWidget.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
/// <summary>
/// The class responsible for the pause menu
/// </summary>
class BFORCE_API UPauseMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	/// <summary>
	/// Removes the pause menu from the screen and from the players view.
	/// </summary>
	void closePauseMenu();
	UFUNCTION(BlueprintCallable)
	/// <summary>
	/// Loads the main menu screen
	/// </summary>
	/// <param name="sceneName">The name of the main menu level</param>
	void toMainMenu(FName sceneName);

	UFUNCTION(BlueprintCallable)
	/// <summary>
	/// Sets the value of the player controller
	/// </summary>
	/// <param name="value"> APlayerController</param>
	void setController(class APlayerController* value) { m_controller = value; }
	UFUNCTION(BlueprintCallable)
	/// <summary>
	/// Returns the value of the player controller
	/// </summary>
	/// <returns>APlayerController</returns>
	class APlayerController* getController() { return m_controller; }

private:
	/// <summary>
	/// Runs when the widget is first constructed on the screen
	/// </summary>
	void NativeConstruct() override;

private:
	/// <summary>
	/// a refrence to the player controller
	/// </summary>
	class APlayerController* m_controller;
	/// <summary>
	/// a refrence to the scene manager actor
	/// </summary>
	class ASceneManager* m_sceneManager;
};
