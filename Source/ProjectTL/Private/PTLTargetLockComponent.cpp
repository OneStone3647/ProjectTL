// Fill out your copyright notice in the Description page of Project Settings.

/*=========================================================================*
 * Ÿ�ٶ� ����� ���� ���� ������Ʈ�Դϴ�.
 * ���� ���� ���� Ÿ���� �˻��ϰ� �� �� �� Ÿ���� ���������� ���� �ٶ󺸰� �մϴ�.
 *=========================================================================*/

#include "PTLTargetLockComponent.h"
#include "PTLStateComponent.h"
#include "PTLTargetComponent.h"
#include "PTLEnemy.h"
#include "PTLPlayer.h"
#include "PTLPlayerController.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"		// FindLookAtRotation() �Լ��� ����ϱ� ���� �ʿ��� ��� ����
#include "Kismet/GameplayStatics.h"			// GetPlayerCameraManager() �Լ��� ����ϱ� ���� �ʿ��� ��� ����


UPTLTargetLockComponent::UPTLTargetLockComponent()
{
	// TickComponent�Լ��� ��������� �ʱ� ������ false�� �����մϴ�.
	PrimaryComponentTick.bCanEverTick = false;

	TargetActor = nullptr;
	bLockedOnTarget = false;

	bDrawDebug = false;
	DebugLifeTime = 2.0f;
	MaxTargetDistance = 1000.0f;
}

// Target�� �����մϴ�.
void UPTLTargetLockComponent::LockOnTarget()
{
	if (TargetActor && bLockedOnTarget)
	{
		// Target�� ���� ��� TargetActor�� ���ϴ�.
		UnlockTarget();
	}
	else
	{
		AActor* NewTargetActor = SetTarget(GetTargetableActors());
		if (NewTargetActor)
		{
			TargetActor = NewTargetActor;
			bLockedOnTarget = true;

			if (bDrawDebug)
			{
				APTLEnemy* TargetEnemy = Cast<APTLEnemy>(TargetActor);
				DrawDebugPoint(GetWorld(), TargetEnemy->GetTargetComponent()->GetComponentLocation(), 30.0f, FColor::Red, false, DebugLifeTime);
			}
		}
	}
}

// ����� Target�� �����մϴ�.
void UPTLTargetLockComponent::LockOnSwitchTarget(EDirection Direction)
{
}

// Target�� �����մϴ�.
void UPTLTargetLockComponent::UnlockTarget()
{
	TargetActor = nullptr;
	bLockedOnTarget = false;
}

// ���� ������ Target�� �迭 �����մϴ�.
TArray<AActor*> UPTLTargetLockComponent::GetTargetableActors()
{
	TArray<FHitResult> HitResult;
	FVector PlayerLocation = GetOwner()->GetActorLocation();

	// Ÿ�ٹ����� ��ο� ������մϴ�.
	if (bDrawDebug)
	{
		DrawDebugSphere(GetWorld(), PlayerLocation, MaxTargetDistance, 50.0f, FColor::Green, false, DebugLifeTime);
	}

	// ECollisionChannel�� DefaultEngine.ini���Ͽ��� Ȯ�� �����մϴ�.
	// ECollisionChannel::ECC_GameTraceChannel1: Target Trace Channel�Դϴ�.
	bool bIsHit = GetWorld()->SweepMultiByChannel(HitResult, PlayerLocation, PlayerLocation, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel1, FCollisionShape::MakeSphere(MaxTargetDistance));

	TArray<AActor*> TargetLockableActors;
	if (bIsHit)
	{
		for (auto& Hit : HitResult)
		{
			APTLEnemy* HitedActor = Cast<APTLEnemy>(Hit.Actor);
			if (Hit.Actor.IsValid() && !HitedActor->GetStateComponent()->GetIsDead())
			{
				if (bDrawDebug)
				{
					DrawDebugPoint(GetWorld(), HitedActor->GetTargetComponent()->GetComponentLocation(), 30.0f, FColor::Green, false, DebugLifeTime);
					LOG_SCREEN("Hit Actor: %s", *HitedActor->GetName());
				}

				// �ߺ����� �ʰ� TargetLockableActors �迭�� �ֽ��ϴ�.
				TargetLockableActors.AddUnique(Cast<AActor>(Hit.Actor));
			}
		}
	}
	else
	{
		LOG_SCREEN("Hit Failed!!");
	}

	return TargetLockableActors;
}

// Target�� �����մϴ�.
AActor * UPTLTargetLockComponent::SetTarget(TArray<AActor*> TargetableActors)
{
	// ���� ������ Target�� ���� ��� nullptr�� ��ȯ�մϴ�.
	if (TargetableActors.Num() == 0)
	{
		return nullptr;
	}

	float NearestDot = 0.0f;
	AActor* NearestTargetActor = nullptr;
	APlayerCameraManager* PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(this, 0);
	for (int32 i = 0; i < TargetableActors.Num(); i++)
	{
		/*-----------------------------------------------------------------------------------------------------------------------------------*
		 * float GetDotProductTo
		 *	(
		 *		const AActor * OtherActor
		 *	) const
		 * OtherActor�� ���� ���� ��ȯ�մϴ�.
		 * �� ������ ������ ���� ����
		 * ������ ���(0)�� ��� 1, ���� ������ ���(90) 0, �����̸鼭 �ݴ� ������ ���(180) -1�� ��ȯ�մϴ�.
		 * �����ϸ� -2.0�� ��ȯ�մϴ�.
		 *-----------------------------------------------------------------------------------------------------------------------------------*/
		float Dot = PlayerCameraManager->GetDotProductTo(TargetableActors[i]);
		if (i == 0)
		{
			NearestDot = Dot;
			NearestTargetActor = TargetableActors[i];
		}
		else
		{
			// ���� ����� Actor�� ã���ϴ�.
			if (Dot > NearestDot)
			{
				NearestDot = Dot;
				NearestTargetActor = TargetableActors[i];
			}
		}
	}

	LOG_SCREEN("TargetActor: %s", *NearestTargetActor->GetName());

	return NearestTargetActor;
}

// Target�� �����մϴ�.
AActor * UPTLTargetLockComponent::SwitchTarget(EDirection Direction)
{
	return nullptr;
}

// Target�� ���� ȸ���������� ����մϴ�.
FRotator UPTLTargetLockComponent::RInterpToTarget()
{
	//APTLPlayerController* PlayerController = Cast<APTLPlayerController>(GetWorld()->GetFirstPlayerController());
	APTLPlayerController* PlayerController = Cast<APTLPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	FRotator PlayerControllerRotator = PlayerController->GetControlRotation();
	FVector PlayerLocation = GetOwner()->GetActorLocation();
	FVector TargetActorLocation = TargetActor->GetActorLocation();

	// 2���� ��ġ ���͸� �Է��Ͽ� 2��° ��ġ ���͸� �ٶ󺸴� ��������(Rotator)�� �����մϴ�.
	FRotator TargetRotator = UKismetMathLibrary::FindLookAtRotation(PlayerLocation, TargetActorLocation);

	FRotator RInterpToRotator = FMath::RInterpTo(PlayerControllerRotator, TargetRotator, GetWorld()->GetDeltaSeconds(), 5.0f);

	return RInterpToRotator;
}

// ����׸� �����մϴ�.
void UPTLTargetLockComponent::SetDebug()
{	
	if (bDrawDebug)
	{
		bDrawDebug = false;
		LOG_SCREEN("DrawDebug Disabled!!");
	}
	else
	{
		bDrawDebug = true;
		LOG_SCREEN("DrawDebug Enabled!!");
	}
}