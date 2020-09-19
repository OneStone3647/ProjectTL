// Fill out your copyright notice in the Description page of Project Settings.

/*=========================================================================*
 * Ÿ�ٶ� ����� ���� ���� ������Ʈ�Դϴ�.
 * ���� ���� ���� Ÿ���� �˻��ϰ� �� �� �� Ÿ���� ���������� ���� �ٶ󺸰� �մϴ�.
 *=========================================================================*/

#pragma once

#include "ProjectTL.h"
#include "Components/ActorComponent.h"
#include "PTLTargetLockComponent.generated.h"

 /*-----------------------------------------------------------------------------------------------------------------------------------*
  * �¿츦 ��Ÿ�� enum Ŭ�����Դϴ�.
  * BlueprintType�� ���ڰ����� ������ �������Ʈ������ ����� �� �ֽ��ϴ�. 
  * UENUM(BlueprintType)
  *-----------------------------------------------------------------------------------------------------------------------------------*/
UENUM()
enum class EDirection : uint8
{
	Left	UMETA(DisplayName = "Left"),
	Right	UMETA(DisplayName = "Right")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTTL_API UPTLTargetLockComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPTLTargetLockComponent();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = TargetLock, meta = (AllowPrivateAccess = "true"))
	class AActor* TargetActor;

private:
	UPROPERTY(VisibleAnywhere, Category = TargetLock)
	bool bLockedOnTarget;

	// ����� ���� ����
	UPROPERTY(EditAnywhere, Category = TargetLock)
	bool bDrawDebug;

	// ����� �ð�
	UPROPERTY(EditAnywhere, Category = TargetLock)
	float DebugLifeTime;

	// Traget�� Ž���� �ִ� �Ÿ�
	UPROPERTY(EditAnywhere, Category = TargetLock)
	float MaxTargetDistance;

public:
	void LockOnTarget();

	void LockOnSwitchTarget(EDirection Direction);

	void UnlockTarget();

private:
	// ���� ������ Target�� �迭�� �����մϴ�.
	TArray<AActor*> GetTargetableActors();

	AActor* SetTarget(TArray<AActor*> TargetableActors);

	AActor* SwitchTarget(EDirection Direction);

public:
	// Target�� ���� ȸ���������� ����մϴ�.
	FRotator RInterpToTarget();

public:
	void SetDebug();

public:
	FORCEINLINE AActor* GetTargetActor() const
	{
		return TargetActor;
	}

	FORCEINLINE bool GetLockOnTargetFlag() const
	{
		return bLockedOnTarget;
	}
};
