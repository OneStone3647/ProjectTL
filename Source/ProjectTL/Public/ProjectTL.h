// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"					// AddOnScreenDebugMessage()�� ����ϱ� ���� ��� �����Դϴ�.
#include "UObject/ConstructorHelpers.h"	// ������ �������� ���ҽ��� �������Ʈ Ŭ������ �ҷ����� ���� ��� �����Դϴ�.

#pragma region LOG

 // �α� ī�װ� ����
DECLARE_LOG_CATEGORY_EXTERN(PTL_LOG, Log, All);

/*-----------------------------------------------------------------------------------------------------------------------------------*
 * FString���� ����� �������� ���ڿ� ������ �������� �ݵ�� * �����ڸ� �տ� ��������� �մϴ�.
 * ������ �̸� ���� FString���� ��ȯ�ϴ� GetName() �Լ��� ���� ���ڿ��� %s�� �����ϴ� ���,
 * �ݵ�� �Լ� �տ� * �����ڸ� �����ؾ��մϴ�.
 * FString::Printf(TEXT("Actor Name : %s, ID : %d, Location X : %.3f"), *GetName(), ID, GetActorLocation().X);
 *-----------------------------------------------------------------------------------------------------------------------------------*/

 // �ڵ尡 ��� �ִ� ���� �̸��� �Լ�, ���� ������ �α׷� ����� ��ũ��
#define LOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))

 // LOG_CALLINFO�� �Բ� �ƹ� ������ ���� �α׸� ����� ��ũ��
/*-----------------------------------------------------------------------------------------------------------------------------------*
 * LOG_S(Error); �Ǵ� LOG(Warning);
 *-----------------------------------------------------------------------------------------------------------------------------------*/
#define LOG_S(Verbosity) UE_LOG(PTL_LOG, Verbosity, TEXT("%s"), *LOG_CALLINFO)

 // LOG_S�� �Բ� ���ڿ��� �߰� ������ �α׷� ����� ��ũ��
/*-----------------------------------------------------------------------------------------------------------------------------------*
 * LOG(Error, "Error"); �Ǵ� LOG(Warning, "Warning");
 *-----------------------------------------------------------------------------------------------------------------------------------*/
#define LOG(Verbosity, Format, ...) UE_LOG(PTL_LOG, Verbosity, TEXT("%s %s"), *LOG_CALLINFO, *FString::Printf(TEXT(Format), ##__VA_ARGS__))

 // Screen�� LOG�� ����ϴ� ��ũ��
 /*-----------------------------------------------------------------------------------------------------------------------------------*
  * LOG_SCREEN("Actor Name : %s, ID : %d, Location X : %.3f"), *GetName(), ID, GetActorLocation().X);
  *-----------------------------------------------------------------------------------------------------------------------------------*/
#define LOG_SCREEN(Format, ...) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT(Format), ##__VA_ARGS__))

  // LOG_SCREEN�� �ð��� ���� ��ũ��, Tick���� DeltaTime�� ���ڷ� �־ ���
#define LOG_SCREEN_T(Time, Format, ...) GEngine->AddOnScreenDebugMessage(-1 Time, FColor::Red, FString::Printf(TEXT(Format), ##__VA_ARGS__))

// LOG�� Verbosity�� ���ڿ��� �� ��ũ��
#define LOG_WARNING(Format, ...) UE_LOG(PTL_LOG, Warning, TEXT("%s %s"), *LOG_CALLINFO *FString::Printf(TEXT(Format), ##__VA_ARGS__))
#define LOG_ERROR(Format, ...) UE_LOG(PTL_LOG, Error, TEXT("%s %s"), *LOG_CALLINFO *FString::Printf(TEXT(Format), ##__VA_ARGS__))

#pragma endregion LOG
