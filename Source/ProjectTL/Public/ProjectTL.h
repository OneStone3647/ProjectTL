// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"					
#include "UObject/ConstructorHelpers.h"	

// �α� ī�װ� ����
DECLARE_LOG_CATEGORY_EXTERN(ProjectTL_Log, Log, All);

/*-----------------------------------------------------------------------------------------------------------------------------------*
 * FString���� ����� �������� ���ڿ� ������ �������� �ݵ�� * �����ڸ� �տ� ��������� �մϴ�.
 * ������ �̸� ���� FString���� ��ȯ�ϴ� GetName() �Լ��� ���� ���ڿ��� %s�� �����ϴ� ���,
 * �ݵ�� �Լ� �տ� * �����ڸ� �����ؾ��մϴ�.
 * FString::Printf(TEXT("Actor Name : %s, ID : %d, Location X : %.3f"),
 *							*GetName(), ID, GetActorLocation().X);
 *-----------------------------------------------------------------------------------------------------------------------------------*/

// �ڵ尡 ��� �ִ� ���� �̸��� �Լ�, ���� ������ �α׷� ����� ��ũ��
#define PTL_LOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))

// PTL_LOG_CALLINFO�� �Բ� �ƹ� ������ ���� �α׸� ����� ��ũ��
/*-----------------------------------------------------------------------------------------------------------------------------------*
 * PTL_LOG_S(Error);
 * PTL_LOG(Warning);
 *-----------------------------------------------------------------------------------------------------------------------------------*/
#define PTL_LOG_S(Verbosity) UE_LOG(ProjectTL_Log, Verbosity, TEXT("%s"), *PTL_LOG_CALLINFO)

// PTL_LOG_S�� �Բ� ���ڿ��� �߰� ������ �α׷� ����� ��ũ��
/*-----------------------------------------------------------------------------------------------------------------------------------*
 * PTL_LOG(Error, "Error"); 
 * PTL_LOG(Warning, "Warning");
 *-----------------------------------------------------------------------------------------------------------------------------------*/
#define PTL_LOG(Verbosity, Format, ...) UE_LOG(ProjectTL_Log, Verbosity, TEXT("%s %s"), *PTL_LOG_CALLINFO, *FString::Printf(TEXT(Format), ##__VA_ARGS__))

// Screen�� LOG�� �и鼭 ����ϴ� ��ũ��
/*-----------------------------------------------------------------------------------------------------------------------------------*
 * PTL_LOCE_SCREEN("Actor Name : %s, ID : %d, Location X : %.3f"),
 *							GetName(), ID, GetActorLocation().X);
 *-----------------------------------------------------------------------------------------------------------------------------------*/
#define PTL_LOG_SCREEN(Format, ...) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT(Format), ##__VA_ARGS__))

// Screen�� LOG�� Index ������� �����Ͽ� �����ϴ� ��ũ��
#define PTL_LOG_SCREEN_INFO(Index, Format, ...) GEngine->AddOnScreenDebugMessage(Index, 0.0f, FColor::Cyan, FString::Printf(TEXT(Format), ##__VA_ARGS__))

// PTL_LOG_SCREEN�� �ð��� ���� ��ũ��, Tick���� DeltaTime�� ���ڷ� �־ ����մϴ�.
#define PTL_LOG_SCREEN_T(Time, Format, ...) GEngine->AddOnScreenDebugMessage(-1 Time, FColor::Red, FString::Printf(TEXT(Format), ##__VA_ARGS__))

// PTL_LOG�� Verbosity�� ���ڿ��� �� ��ũ��
#define PTL_LOG_WARNING(Format, ...) UE_LOG(ProjectTL_Log, Warning, TEXT("%s %s"), *PTL_LOG_CALLINFO *FString::Printf(TEXT(Format), ##__VA_ARGS__))
#define PTL_LOG_ERROR(Format, ...) UE_LOG(ProjectTL_Log, Error, TEXT("%s %s"), *PTL_LOG_CALLINFO *FString::Printf(TEXT(Format), ##__VA_ARGS__))

// ��Ÿ�ӿ��� ������ �߻��� �� ���������� ���� �α׸� �Ѹ��� �ٷ� �Լ��� ��ȯ�մϴ�.
#define PTL_CHECK(Expr, ...) {if(!(Expr)) {PTL_LOG(Error, TEXT("ASSERTION: %s")), TEXT("'"#Expr"'")); return __VA_ARGS__;}}

