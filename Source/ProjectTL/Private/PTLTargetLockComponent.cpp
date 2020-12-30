// Fill out your copyright notice in the Description page of Project Settings.

#include "PTLTargetLockComponent.h"
#include "PTLPlayer.h"
#include "PTLPlayerController.h"
#include "PTLEnemy.h"
#include "PTLStateComponent.h"
#include "PTLTargetComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

UPTLTargetLockComponent::UPTLTargetLockComponent()
{
	// TickComponent�� ������� �ʽ��ϴ�.
	PrimaryComponentTick.bCanEverTick = false;

	bDrawDebug = false;
	DrawDebugTime = 2.0f;

	bIsLockOnTarget = false;
	TargetActor = nullptr;
	MaxTargetDistance = 1000.0f;
}

void UPTLTargetLockComponent::SetDebug()
{	
	if (bDrawDebug)
	{
		bDrawDebug = false;
		PTL_LOG_SCREEN("DrawDebug Disabled!!");
	}
	else
	{
		bDrawDebug = true;
		PTL_LOG_SCREEN("DrawDebug Enabled!!");
	}
}

void UPTLTargetLockComponent::LockOnTarget()
{
	// Traget�� LockOn�ϰ� ���� ��� LockOn�� �����մϴ�.
	if (TargetActor && bIsLockOnTarget)
	{
		UnLockOnTarget();
	}
	else
	{
		TArray<AActor*> TargetableActors = GetTargetableActors();
		AActor* NewTargetActor = GetNearestTargetActor(TargetableActors);

		SetTargetActor(NewTargetActor);
	}
}

void UPTLTargetLockComponent::SwitchLockOnTarget(EDirection NewDirection)
{
	AActor* NewTargetActor = GetNearestTargetActorToDirection(NewDirection);

	SetTargetActor(NewTargetActor);
}

void UPTLTargetLockComponent::UnLockOnTarget()
{
	TargetActor = nullptr;
	bIsLockOnTarget = false;

	APTLCharacterBase* Player = Cast<APTLCharacterBase>(GetOwner());
	if (Player)
	{
		Player->GetCharacterMovement()->bOrientRotationToMovement = true;
		Player->GetCharacterMovement()->bUseControllerDesiredRotation = false;
	}
}

FRotator UPTLTargetLockComponent::RInterpToTarget()
{
	FRotator RInterpToRotator;
	float InterpSpeed = 5.0f;

	APTLPlayerController* PlayerController = Cast<APTLPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PlayerController)
	{
		FRotator PlayerControllerRotator = PlayerController->GetControlRotation();
		FVector PlayerLocation = GetOwner()->GetActorLocation();
		FVector TargetLocation = TargetActor->GetActorLocation();

		// 2���� ��ġ ���͸� �Է��Ͽ� 2��° ��ġ ���͸� �ٶ󺸴� ��������(Rotator)�� ��ȯ�մϴ�.
		FRotator TargetRotator = UKismetMathLibrary::FindLookAtRotation(PlayerLocation, TargetLocation);

		RInterpToRotator = FMath::RInterpTo(PlayerControllerRotator, TargetRotator, GetWorld()->GetDeltaSeconds(), InterpSpeed);
	}

	return RInterpToRotator;
}

TArray<AActor*> UPTLTargetLockComponent::GetTargetableActors()
{
	FVector PlayerLocation = GetOwner()->GetActorLocation();

	// Ž�� ������ ������ ��ο� ������մϴ�.
	if (bDrawDebug)
	{
		float DebugSize = 50.0f;

		DrawDebugSphere(GetWorld(), PlayerLocation, MaxTargetDistance, DebugSize, FColor::Green, false, DrawDebugTime);
	}

	TArray<FHitResult> HitResults;
	TArray<AActor*> TargetableActors;
	// ECC_GameTraceChannel1 = Target Trace Channel
	bool bIsHit = GetWorld()->SweepMultiByChannel(HitResults, PlayerLocation, PlayerLocation, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel1, FCollisionShape::MakeSphere(MaxTargetDistance));
	if (bIsHit)
	{
		for (auto& Hit : HitResults)
		{
			APTLEnemy* HitedEnemy = Cast<APTLEnemy>(Hit.Actor);
			if (HitedEnemy && HitedEnemy->GetStateComponent()->GetIsDead() != true)
			{
				if (bDrawDebug)
				{
					float DebugSize = 30.0f;

					DrawDebugPoint(GetWorld(), HitedEnemy->GetTargetComponent()->GetComponentLocation(), DebugSize, FColor::Green, false, DrawDebugTime);
				}

				// �ߺ����� �ʰ� TargetalbeActors �迭�� �ֽ��ϴ�.
				TargetableActors.AddUnique(Cast<AActor>(Hit.Actor));
			}
		}
	}

	return TargetableActors;
}

AActor * UPTLTargetLockComponent::GetNearestTargetActor(TArray<AActor*> TargetableActors)
{
	// ���� ������ Target�� ���� ��� nullptr�� ��ȯ�մϴ�.
	if (TargetableActors.Num() == 0)
	{
		return nullptr;
	}

	float NearestDot = 0.0f;
	AActor* NearestTargetActor = nullptr;
	APlayerCameraManager* PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);

	for (int32 i = 0; i < TargetableActors.Num(); ++i)
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

	if (bDrawDebug)
	{
		PTL_LOG_SCREEN("TargetActor: %s", *NearestTargetActor->GetName());
	}

	return NearestTargetActor;
}

AActor * UPTLTargetLockComponent::GetNearestTargetActorToDirection(EDirection Direction)
{
	AActor* NearestTargetActor = nullptr;

	if (bIsLockOnTarget)
	{
		TArray<AActor*> TargetableActors = GetTargetableActors();
		int32 CurrentTargetIndex = TargetableActors.Find(TargetActor);
		// ���� Target�� Index�� �߰��Ͽ��ٸ� �迭���� �����մϴ�.
		if (CurrentTargetIndex != INDEX_NONE)
		{
			TargetableActors.Remove(TargetActor);
		}

		// ���� Ÿ���� �������� �¿쿡 �ִ� Ÿ���� Ž���մϴ�.
		TArray<AActor*> LeftTargetableActors;
		TArray<AActor*> RightTargetableActors;
		APlayerCameraManager* PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);

		for (AActor* TargetableActor : TargetableActors)
		{
			/*-----------------------------------------------------------------------------------------------------------------------------------*
			 * ������ ������ Ȱ���Ͽ� ���� Ÿ���� �ٶ󺸴� ������ ���մϴ�.
			 * ���� Ÿ���� �ٶ󺸴� ���� = Ÿ���� ��ġ - �ڽ��� ��ġ
			 *-----------------------------------------------------------------------------------------------------------------------------------*/

			FVector LookAtTargetableActorVector = TargetableActor->GetActorLocation() - PlayerCameraManager->GetCameraLocation();
			FVector LookAtCurrentTargetActorVector = TargetActor->GetActorLocation() - PlayerCameraManager->GetCameraLocation();

			// �� ������ ������ ��ȯ�մϴ�.
			FVector CrossVector = FVector::CrossProduct(LookAtCurrentTargetActorVector, LookAtTargetableActorVector);
			// ����ȭ�� ������ Z������ �¿쿡 �����ϴ��� �Ǻ��մϴ�.
			if (CrossVector.GetSafeNormal().Z < 0.0f)
			{
				// ���� �ٶ󺸴� ������ �������� ���ʿ� �����ϰ� LeftTargetableActors �迭�� �������� ���� ��� �迭�� �߰��մϴ�.
				LeftTargetableActors.AddUnique(TargetableActor);
			}
			else
			{
				// ���� �ٶ󺸴� ������ �������� �����ʿ� �����ϰ� RightTargetableActors �迭�� �������� ���� ��� �迭�� �߰��մϴ�.
				RightTargetableActors.AddUnique(TargetableActor);
			}
		}

		switch (Direction)
		{
		case EDirection::Direction_Left:
			if (LeftTargetableActors.Num() > 0)
			{
				NearestTargetActor = GetNearestTargetActor(LeftTargetableActors);
			}
			else
			{
				NearestTargetActor = GetNearestTargetActor(RightTargetableActors);
			}
			break;
		case EDirection::Direction_Right:
			if (RightTargetableActors.Num() > 0)
			{
				NearestTargetActor = GetNearestTargetActor(RightTargetableActors);
			}
			else
			{
				NearestTargetActor = GetNearestTargetActor(LeftTargetableActors);
			}
			break;
		default:
			break;
		}
	}

	return NearestTargetActor;
}

AActor * UPTLTargetLockComponent::GetTargetActor() const
{
	return TargetActor;
}

void UPTLTargetLockComponent::SetTargetActor(AActor * NewTargetActor)
{
	if (NewTargetActor)
	{
		TargetActor = NewTargetActor;
		bIsLockOnTarget = true;

		APTLCharacterBase* Player = Cast<APTLCharacterBase>(GetOwner());
		if (Player)
		{
			Player->GetCharacterMovement()->bOrientRotationToMovement = false;
			Player->GetCharacterMovement()->bUseControllerDesiredRotation = true;
		}

		if (bDrawDebug)
		{
			APTLEnemy* TargetEnemy = Cast<APTLEnemy>(TargetActor);
			float DebugSize = 30.0f;

			DrawDebugPoint(GetWorld(), TargetEnemy->GetTargetComponent()->GetComponentLocation(), DebugSize, FColor::Red, false, DrawDebugTime);
		}
	}
}

bool UPTLTargetLockComponent::GetIsLockOnTarget() const
{
	return bIsLockOnTarget;
}

