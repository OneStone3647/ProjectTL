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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Target, meta = (AllowPrivateAccess = "true"))
	class AActor* TargetActor;

private:
	UPROPERTY(VisibleAnywhere, Category = Target)
	bool bLockedOnTarget;

	// ����� ���� ����
	UPROPERTY(VisibleAnywhere, Category = Target)
	bool bDrawDebug;

	// ����� �ð�
	UPROPERTY(VisibleAnywhere, Category = Target)
	float DebugLifeTime;

	// Traget�� Ž���� �ִ� �Ÿ�
	UPROPERTY(VisibleAnywhere, Category = Target)
	float MaxTargetDistance;

public:
	// Target�� �����մϴ�.
	void LockOnTarget();

	// ����� Target�� �����մϴ�.
	void LockOnSwitchTarget(EDirection Direction);

	// Target�� �����մϴ�.
	void UnlockTarget();

private:
	// ���� ������ Target�� �迭 �����մϴ�.
	TArray<AActor*> GetTargetableActors();

	// Target�� �����մϴ�.
	AActor* SetTarget(TArray<AActor*> TargetableActors);

	// Target�� �����մϴ�.
	AActor* SwitchTarget(EDirection Direction);

public:
	// Target�� ���� ȸ���������� ����մϴ�.
	FRotator RInterpToTarget();

public:
	// ����׸� �����մϴ�.
	void SetDebug();

	// Get�Լ� FORCEINLINE ��ũ�η� inline�Լ��� �ۼ�
public:
	UFUNCTION(BlueprintCallable, Category = "Target")			// �ӽ÷� ����ϴ� �������Ʈ �Լ� ����
	FORCEINLINE AActor* GetTargetActor() const
	{
		return TargetActor;
	}

	FORCEINLINE bool GetLockOnTargetFlag() const
	{
		return bLockedOnTarget;
	}
};
