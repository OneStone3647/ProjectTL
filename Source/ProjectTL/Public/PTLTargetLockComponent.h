// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectTL.h"
#include "Components/ActorComponent.h"
#include "PTLTargetLockComponent.generated.h"

 /*=========================================================================*
  * �¿츦 ��Ÿ�� enum Ŭ�����Դϴ�.
  * BlueprintType�� ���ڰ����� ������ �������Ʈ������ ����� �� �ֽ��ϴ�. 
  * UENUM(BlueprintType)
 *=========================================================================*/
UENUM()
enum class EDirection : uint8
{
	Direction_Left	UMETA(DisplayName = "Left"),
	Direction_Right	UMETA(DisplayName = "Right")
};

/*=========================================================================*
 * Ÿ�ٶ� ����� ���� ���� ������Ʈ�Դϴ�.
 * ���� ���� ���� Ÿ���� �˻��ϰ� �� �� �� Ÿ���� ���������� ���� �ٶ󺸰� �մϴ�.
 *=========================================================================*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTTL_API UPTLTargetLockComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPTLTargetLockComponent();

#pragma region Debug
public:
	void SetDebug();

private:
	// ����� ���� ����
	UPROPERTY(EditAnywhere, Category = "Debug")
	bool bDrawDebug;

	// ����� �ð�
	UPROPERTY(EditAnywhere, Category = "Debug")
	float DrawDebugTime;
#pragma endregion

#pragma region TargetLockSystem
public:
	UFUNCTION(BlueprintCallable, Category = "TargetLockSystem")
	void LockOnTarget();

	UFUNCTION(BlueprintCallable, Category = "TargetLockSystem")
	void SwitchLockOnTarget(EDirection NewDirection);

	UFUNCTION(BlueprintCallable, Category = "TargetLockSystem")
	void UnLockOnTarget();

	// Target�� ���� ȸ���������� ����մϴ�.
	UFUNCTION(BlueprintCallable, Category = "TargetLockSystem")
	FRotator RInterpToTarget();

private:
	TArray<AActor*> GetTargetableActors();

	AActor* GetNearestTargetActor(TArray<AActor*> TargetableActors);

	AActor* GetNearestTargetActorToDirection(EDirection Direction);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "TargetLockSystem", meta = (AllowPrivateAccess = "true"))
	bool bIsLockOnTarget;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "TargetLockSystem", meta = (AllowPrivateAccess = "true"))
	class AActor* TargetActor;

	// Traget�� Ž���� �ִ� �Ÿ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TargetLockSystem", meta = (AllowPrivateAccess = "true"))
	float MaxTargetDistance;

public:
	AActor* GetTargetActor() const;

	UFUNCTION(BlueprintCallable, Category = "TargetLockSystem")
	void SetTargetActor(AActor* NewTargetActor);

	bool GetIsLockOnTarget() const;
#pragma endregion
};
