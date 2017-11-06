// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "RPGGameMode.h"
#include "UI/RPGHUD.h"
#include "Characters/RPGCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARPGGameMode::ARPGGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ARPGHUD::StaticClass();
}
