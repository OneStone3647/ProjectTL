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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State)
	class UPTLStateComponent* StateComponent;

public:
	FORCEINLINE class UPTLStateComponent* GetStateComponent() const
	{
		return StateComponent;
	}
};
