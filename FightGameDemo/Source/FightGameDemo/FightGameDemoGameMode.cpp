// Copyright Epic Games, Inc. All Rights Reserved.

#include "FightGameDemoGameMode.h"
#include "FightGameDemoCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFightGameDemoGameMode::AFightGameDemoGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
