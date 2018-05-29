// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "breachSundialv3.h"
#include "breachSundialv3GameMode.h"
#include "breachSundialv3Character.h"

AbreachSundialv3GameMode::AbreachSundialv3GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
