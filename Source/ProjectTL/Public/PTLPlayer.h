// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PTLCharacterBase.h"
#include "PTLPlayer.generated.h"

/*=========================================================================*
 * �÷��̾� ĳ���� Ŭ�����Դϴ�.
 *=========================================================================*/
UCLASS()
class PROJECTTL_API APTLPlayer : public APTLCharacterBase
{
	GENERATED_BODY()
	
public:
	APTLPlayer();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#pragma region Camera
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const
	{
		return CameraBoom;
	}

	FORCEINLINE class UCameraComponent* GetFollowCamera() const
	{
		return FollowCamera;
	}
#pragma endregion

#pragma region TargetLockSystem
private:
	UFUNCTION(BlueprintCallable, Category = "TargetLockSystem")
	void LockOnTarget();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TargetLockSystem", meta = (AllowPrivateAccess = "true"))
	class UPTLTargetLockComponent* TargetLockComponent;

private:
	// Target�� ��ȯ�ϱ� ���� �ʿ��� ���콺 �������� ���Դϴ�.
	UPROPERTY(EditAnywhere, Category = "TargetLockSystem")
	float MouseValueToSwitchTarget;

	// Target�� ��ȯ�ϱ� ���� �ʿ��� �Ƴ��α� ��ƽ �������� ���Դϴ�.
	UPROPERTY(EditAnywhere, Category = "TargetLockSystem")
	float AnalogValueToSwitchTarget;

	// �ٸ� Target���� ��ȯ�ϱ� ���� ��Ÿ���Դϴ�.
	// �ʹ� ������ ���� Target�� �Ѿ�� ���� �����մϴ�.
	UPROPERTY(EditAnywhere, Category = "TargetLockSystem")
	float MinDelaySecondsToSwitchTarget;

	// ������ Target ��ȯ �� �Ƴ��α� ��ƽ�� �߾����� �ǵ����� true�� �����˴ϴ�.
	UPROPERTY(VisibleInstanceOnly, Category = "TargetLockSystem")
	bool bAnalogSettledSinceLastSwitchTarget;

	// ���������� Target�� �ٲ� �ð��Դϴ�.
	UPROPERTY(VisibleInstanceOnly, Category = "TargetLockSystem")
	float LastTimeSwitchTarget;

public:
	FORCEINLINE UPTLTargetLockComponent* GetTargetLockComponent() const
	{
		return TargetLockComponent;
	}
#pragma endregion

#pragma region Movement
protected:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

private:
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	class APTLPlayerController* PlayerController;
#pragma endregion

private:
	void Attack();
};
