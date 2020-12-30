// Fill out your copyright notice in the Description page of Project Settings.

/*=========================================================================*
 * ĳ������ �⺻ ���̽� Ŭ�����Դϴ�.
 *=========================================================================*/

#include "PTLCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

APTLCharacterBase::APTLCharacterBase()
{
	// Tick �Լ��� ������� �ʽ��ϴ�.
	PrimaryActorTick.bCanEverTick = false;

	// SkeletalMesh ����
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -97.0f), FRotator(0.0f, -90.0f, 0.0f));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Mannequin(TEXT("/Game/Mannequin/Character/Mesh/SK_Mannequin"));
	if (SK_Mannequin.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_Mannequin.Object);
	}
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	// AnimInstance ����
	static ConstructorHelpers::FClassFinder<UAnimInstance> Character_Anim(TEXT("/Game/Blueprints/AnimBP_PTLCharacterAnim"));
	if (Character_Anim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(Character_Anim.Class);
	}

	// Collision ����
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	// CharacterMovement ����
	GetCharacterMovement()->bOrientRotationToMovement = true;		// �����̴� �������� ĳ���͸� ȸ���մϴ�.
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.f, 0.0f);	// ĳ������ ȸ�� �ӵ��Դϴ�.
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->AirControl = 0.2f;

	// StateComponent ���� �� ����
	StateComponent = CreateDefaultSubobject<UPTLStateComponent>(TEXT("StateComponent"));
	StateComponent->SetIsDead(false);
}
