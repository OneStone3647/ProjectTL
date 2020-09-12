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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = State, meta = (AllowPrivateAccess = "true"))
	class UPTLStateComponent* StateComponent;

	// Get�Լ� FORCEINLINE ��ũ�η� Inline�Լ��� �ۼ�
public:
	// StateComponent Get�Լ�
	UFUNCTION(BlueprintCallable, Category = "State")			// �ӽ÷� ����ϴ� �������Ʈ �Լ� ����
	FORCEINLINE class UPTLStateComponent* GetStateComponent() const
	{
		return StateComponent;
	}
};
