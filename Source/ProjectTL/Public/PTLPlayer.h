// Fill out your copyright notice in the Description page of Project Settings.

/*=========================================================================*
 * �÷��̾� ĳ���� Ŭ�����Դϴ�.
 *=========================================================================*/

#pragma once

#include "PTLCharacterBase.h"
#include "PTLPlayer.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTL_API APTLPlayer : public APTLCharacterBase
{
	GENERATED_BODY()
	
public:
	APTLPlayer();

protected:
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

#pragma region TargetLock

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = TargetLock, meta = (AllowPrivateAccess = "true"))
	class UPTLTargetLockComponent* TargetLockComponent;

private:
	// Ÿ���� ��ȯ�ϱ����� �ʿ��� ���콺 �������� ��
	UPROPERTY(EditDefaultsOnly, Category = TargetLock)
	float TargetSwitchMouseValue;

	// Ÿ���� ��ȯ�ϱ� ���� �ʿ��� �Ƴ��α� ��ƽ �������� ��
	UPROPERTY(EditDefaultsOnly, Category = TargetLock)
	float TargetSwitchAnalogValue;

	// ������ Ÿ�� ��ȯ �� �Ƴ��α� ��ƽ�� �߾����� �ǵ����� true
	UPROPERTY(VisibleInstanceOnly, Category = TargetLock)
	bool bAnalogSettledSinceLastTargetSwitch;

	// �ٸ� Ÿ������ ��ȯ�ϱ� ���� ��Ÿ��
	// �ʹ� ������ ���� Ÿ������ �Ѿ�� ���� �����մϴ�.
	UPROPERTY(EditDefaultsOnly, Category = TargetLock)
	float TargetSwitchMinDelaySeconds;

	// ���������� Ÿ���� �ٲ� �ð�
	UPROPERTY(EditDefaultsOnly, Category = TargetLock)
	float LastTargetSwitchTime;

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
	void Attack();

#pragma endregion
};
