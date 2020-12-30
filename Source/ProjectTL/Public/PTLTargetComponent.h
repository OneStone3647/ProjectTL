// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectTL.h"
#include "Components/SceneComponent.h"
#include "PTLTargetComponent.generated.h"

/*=========================================================================*
 * �÷��̾��� HUD�� ������ ǥ���� ��ġ�� ��� SceneComponent�Դϴ�.
 *=========================================================================*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTTL_API UPTLTargetComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	UPTLTargetComponent();
};
