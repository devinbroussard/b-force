// Copyright Epic Games, Inc. All Rights Reserved.

#include "BForceGameMode.h"
#include "BForcePawn.h"

ABForceGameMode::ABForceGameMode()
{
	// set default pawn class to our flying pawn
	DefaultPawnClass = ABForcePawn::StaticClass();
}
