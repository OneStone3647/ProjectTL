// Fill out your copyright notice in the Description page of Project Settings.

/*=========================================================================*
 * ĳ������ �⺻ ���̽� Ŭ�����Դϴ�.
 *=========================================================================*/

#pragma once

#include "ProjectTL.h"
#include "GameFramework/Character.h"
#include "PTLCharacterBase.generated.h"

UCLASS()
class PROJECTTL_API APTLCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	APTLCharacterBase();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	class UPTLCharacterAnimInstance* PTLCharacterAnim;
};
