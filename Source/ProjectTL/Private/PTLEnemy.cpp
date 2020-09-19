// Fill out your copyright notice in the Description page of Project Settings.

/*=========================================================================*
 * �� Ŭ�����Դϴ�.
 *=========================================================================*/

#include "PTLEnemy.h"
#include "PTLTargetComponent.h"
#include "PTLStateComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"

APTLEnemy::APTLEnemy()
{
	// Tick�Լ��� ����ϱ� ������ true�� �����մϴ�.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));

	// TargetComponent ����
	TargetComponent = CreateDefaultSubobject<UPTLTargetComponent>(TEXT("TargetComponent"));
	TargetComponent->SetupAttachment(RootComponent);

	// TextRender ����
	ActorNameText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ActorNameText"));
	ActorNameText->SetupAttachment(RootComponent);
	ActorNameText->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 90.0f), FRotator(0.0f, 0.0f, 0.0f));
	ActorNameText->SetWorldSize(30.0f);
	ActorNameText->SetTextRenderColor(FColor::Blue);
	ActorNameText->SetHorizontalAlignment(EHTA_Center);			// �ؽ�Ʈ ���� ����
	ActorNameText->SetVerticalAlignment(EVRTA_TextCenter);		// �ؽ�Ʈ ���� ����
	ActorNameText->SetText(TEXT("Enemy"));
}

void APTLEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PrintText();
}

// TextRender�� �÷��̾� ī�޶� �ٶ󺸵��� ����մϴ�.
void APTLEnemy::PrintText()
{
	APlayerCameraManager* PlayerCameraManager = Cast<APlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));
	if (PlayerCameraManager)
	{
		FRotator NewRotation = PlayerCameraManager->GetCameraRotation();

		ActorNameText->SetRelativeRotation(FRotator(0.0f, NewRotation.Yaw, 0.0f));
	}
}

void APTLEnemy::IsDead()
{
	if (StateComponent->GetIsDead() != true)
	{
		// ���׵� ����
		GetMesh()->SetCollisionProfileName("Ragdoll");
		GetMesh()->SetSimulatePhysics(true);

		// CapsuleComponent�� �����մϴ�.
		GetCapsuleComponent()->DestroyComponent();

		StateComponent->SetIsDead(true);
	}
}
