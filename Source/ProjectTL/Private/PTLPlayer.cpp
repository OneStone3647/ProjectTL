// Fill out your copyright notice in the Description page of Project Settings.

/*=========================================================================*
 * �÷��̾� ĳ���� Ŭ�����Դϴ�.
 *=========================================================================*/

#include "PTLPlayer.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

APTLPlayer::APTLPlayer()
{
	// Tick�� ������� �ʱ� ������ true�� �����մϴ�.
	PrimaryActorTick.bCanEverTick = true;

	BaseTurnRate = 45.0f;
	BaseLookUpRate = 45.0f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// �������� ����
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetRelativeLocation(FVector(0.0f, 0.0f, 60.0f));
	CameraBoom->SocketOffset = FVector(0.0f, 0.0f, 15.0f);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;			// �����ѷ��� �������� ȸ���մϴ�.
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = 5.0f;

	// ī�޶� ����
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;		// ������ �� �������� ȸ������ �ʽ��ϴ�.
}

void APTLPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APTLPlayer::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &APTLPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APTLPlayer::MoveRight);

	// ���콺 �Է�
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	// ������� �Է�
	PlayerInputComponent->BindAxis("TurnRate", this, &APTLPlayer::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &APTLPlayer::LookUpAtRate);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &APTLPlayer::Attack);

	//PlayerInputComponent->BindAction("SetDebug", IE_Pressed, CameraLockArm, &UTLSpringArmComponent::SetDebug);
	//PlayerInputComponent->BindAction("TargetLock", IE_Pressed, CameraLockArm, &UTLSpringArmComponent::LockToTarget);
	//PlayerInputComponent->BindAction<TBaseDelegate<void, EDirection>>("TargetSwitchLeft", IE_Pressed, CameraLockArm, &UTLSpringArmComponent::LockToSwitchTarget, EDirection::Left);
	//PlayerInputComponent->BindAction<TBaseDelegate<void, EDirection>>("TargetSwitchRight", IE_Pressed, CameraLockArm, &UTLSpringArmComponent::LockToSwitchTarget, EDirection::Right);
}

void APTLPlayer::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APTLPlayer::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void APTLPlayer::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APTLPlayer::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void APTLPlayer::Attack()
{
}
