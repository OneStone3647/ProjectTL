// Fill out your copyright notice in the Description page of Project Settings.

/*=========================================================================*
 * ĳ���� �ִ� �ν��Ͻ� Ŭ�����Դϴ�.
 *=========================================================================*/

#pragma once

#include "ProjectTL.h"
#include "Animation/AnimInstance.h"
#include "PTLCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTL_API UPTLCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPTLCharacterAnimInstance();
	
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere ,BlueprintReadWrite, Category = State, Meta = (AllowPrivateAccess = "true"))
	bool bIsDead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = State, Meta = (AllowPrivateAccess = "true"))
	bool bIsInAir;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = State, Meta = (AllowPrivateAccess = "true"))
	float CurrentCharacterSpeed;
};
