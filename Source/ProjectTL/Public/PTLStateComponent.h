// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectTL.h"
#include "Components/ActorComponent.h"
#include "PTLStateComponent.generated.h"

/*=========================================================================*
 * ĳ������ ���¸� ��Ÿ���� Ŭ�����Դϴ�.
 *=========================================================================*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTTL_API UPTLStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPTLStateComponent();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = State, meta = (AllowPrivateAccess = "true"))
	bool bIsDead;

public:
	bool GetIsDead() const;
	void SetIsDead(bool bFlag);
};
