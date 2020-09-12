// Fill out your copyright notice in the Description page of Project Settings.

/*=========================================================================*
 * ĳ������ ���¸� ��Ÿ���� Ŭ�����Դϴ�.
 *=========================================================================*/

#pragma once

#include "ProjectTL.h"
#include "Components/ActorComponent.h"
#include "PTLStateComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTTL_API UPTLStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPTLStateComponent();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = State, meta = (AllowPrivateAccess = "true"))
	bool bIsDead;

	// Get�Լ� FORCEINLINE ��ũ�η� inline�Լ��� �ۼ�
public:
	FORCEINLINE bool GetIsDead() const
	{
		return bIsDead;
	}
	FORCEINLINE void SetIsDead(bool bFlag)
	{
		bIsDead = bFlag;
	}
};
