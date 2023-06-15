// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SceneManager.generated.h"

UCLASS()
/// <summary>
/// An actor responsible for the loading of scenes.
/// </summary>
class BFORCE_API ASceneManager : public AActor
{
	GENERATED_BODY()
	
public:
	/// <summary>
	/// Loads a level by level name
	/// </summary>
	void loadScene(FName levelName);
	/// <summary>
	/// Closes the game
	/// </summary>
	void quit();
};
