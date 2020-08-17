// Fill out your copyright notice in the Description page of Project Settings.

/*=========================================================================*
 * ĳ������ �⺻ ���̽� Ŭ�����Դϴ�.
 *=========================================================================*/

#include "PTLCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PTLCharacterAnimInstance.h"
#include "..\Public\PTLCharacterBase.h"

APTLCharacterBase::APTLCharacterBase()
{
	// Tick�� ������� �ʱ� ������ false�� �����մϴ�.
	PrimaryActorTick.bCanEverTick = false;

	// �޽� ����
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -97.0f), FRotator(0.0f, -90.0f, 0.0f));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Mannequin(TEXT("SkeletalMesh'/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'"));
	if (SK_Mannequin.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_Mannequin.Object);
	}
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);		// �ִϸ��̼� �������Ʈ�� ����Ͽ� �ִϸ��̼��� ����մϴ�.

	// �ִϸ��̼� ����
	static ConstructorHelpers::FClassFinder<UAnimInstance> PTLCharacter_Anim(TEXT("AnimBlueprint'/Game/Blueprints/AnimBP_PTLCharacterAnim.AnimBP_PTLCharacterAnim_C'"));
	if (PTLCharacter_Anim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(PTLCharacter_Anim.Class);
	}

	// ĸ�� �ݸ��� ũ�� ����
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);					// ĸ���� �ݰ�� ĸ���� ���� ���̸� �����մϴ�.

	// CharacterMovement ����
	GetCharacterMovement()->bOrientRotationToMovement = true;		// �����̴� �������� ĳ���͸� ȸ���մϴ�.
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.f, 0.0f);	// ĳ������ ȸ�� �ӵ��Դϴ�.
	GetCharacterMovement()->JumpZVelocity = 600.0f;						// ������ �� �ʱ� �ӵ��Դϴ�.
	GetCharacterMovement()->AirControl = 0.2f;								// ������ �� ĳ���Ϳ��� ��� ������ ���� �̵� ������ ���Դϴ�
}

void APTLCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}
