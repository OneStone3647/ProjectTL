// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectTL.h"
#include "GameFramework/PlayerController.h"
#include "PTLPlayerController.generated.h"

/*=========================================================================*
 * �÷��̾� ĳ������ ��Ʈ�ѷ� Ŭ�����Դϴ�.
 *=========================================================================*/
UCLASS()
class PROJECTTL_API APTLPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
};
