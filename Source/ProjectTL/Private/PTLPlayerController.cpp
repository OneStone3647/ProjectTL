// Fill out your copyright notice in the Description page of Project Settings.

/*=========================================================================*
 * �÷��̾� ĳ������ ��Ʈ�ѷ� Ŭ�����Դϴ�.
 *=========================================================================*/

#include "PTLPlayerController.h"

void APTLPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// ����Ʈ�� ���콺�� ���Ӵϴ�.
	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
}
