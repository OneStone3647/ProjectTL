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

	// Get�Լ� FORCEINLINE ��ũ�η� inline�Լ��� �ۼ�
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

#pragma region Target

private:
	UPROPERTY(VisibleAnywhere, Category = Target)
	class UPTLTargetLockComponent* TargetLockComponent;

	// Get�Լ� FORCEINLINE ��ũ�η� inline�Լ��� �ۼ�
public:
	UFUNCTION(BlueprintCallable, Category = "Target")			// �ӽ÷� ����ϴ� �������Ʈ �Լ� ����
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

#pragma endregion

private:
	void Attack();
};
