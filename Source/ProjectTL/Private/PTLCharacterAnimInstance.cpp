// Fill out your copyright notice in the Description page of Project Settings.

/*=========================================================================*
 * ĳ���� �ִ� �ν��Ͻ� Ŭ�����Դϴ�.
 *=========================================================================*/

#include "PTLCharacterAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UPTLCharacterAnimInstance::UPTLCharacterAnimInstance()
{
	bIsDead = false;
	bIsInAir = false;
	CurrentCharacterSpeed = 0.0f;
}

void UPTLCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (IsValid(Pawn))
	{
		CurrentCharacterSpeed = Pawn->GetVelocity().Size();
		auto Character = Cast<ACharacter>(Pawn);
		if (Character)
		{
			bIsInAir = Character->GetMovementComponent()->IsFalling();
		}
	}
}
