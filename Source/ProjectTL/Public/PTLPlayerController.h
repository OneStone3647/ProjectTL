// Fill out your copyright notice in the Description page of Project Settings.

/*=========================================================================*
 * �÷��̾� ĳ������ ��Ʈ�ѷ� Ŭ�����Դϴ�.
 *=========================================================================*/

#pragma once

#include "ProjectTL.h"
#include "GameFramework/PlayerController.h"
#include "PTLPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTL_API APTLPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
};
