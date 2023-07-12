// Copyright Epic Games, Inc. All Rights Reserved.

#include "Kouhei_ObstacleRunGameMode.h"
#include "Kouhei_ObstacleRunCharacter.h"
#include "UObject/ConstructorHelpers.h"

AKouhei_ObstacleRunGameMode::AKouhei_ObstacleRunGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
