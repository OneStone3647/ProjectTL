// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ProjectTLGameMode.h"
#include "ProjectTLCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "PTLPlayerController.h"

AProjectTLGameMode::AProjectTLGameMode()
{
	// PlayerBP�� DefaultPawnClass�� �����մϴ�
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// PTLPlayerController�� PlayerController �����մϴ�.
	PlayerControllerClass = APTLPlayerController::StaticClass();
}
