// Fill out your copyright notice in the Description page of Project Settings.


#include "PTLGameMode.h"
#include "PTLPlayer.h"
#include "PTLPlayerController.h"

APTLGameMode::APTLGameMode()
{
	// DefaultPawnClass ����
	static ConstructorHelpers::FClassFinder<APawn> BP_PTLPlayer(TEXT("Blueprint'/Game/Blueprints/BP_PTLPlayer.BP_PTLPlayer_C'"));
	if (BP_PTLPlayer.Class != NULL)
	{
		DefaultPawnClass = BP_PTLPlayer.Class;
	}

	// PlayerController ����
	PlayerControllerClass = APTLPlayerController::StaticClass();
}
