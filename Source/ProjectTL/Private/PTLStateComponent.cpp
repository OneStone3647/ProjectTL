// Fill out your copyright notice in the Description page of Project Settings.

/*=========================================================================*
 * ĳ������ ���¸� ��Ÿ���� Ŭ�����Դϴ�.
 *=========================================================================*/

#include "PTLStateComponent.h"

UPTLStateComponent::UPTLStateComponent()
{
	// TickComponent�Լ��� ������� �ʱ� ������ false�� �����մϴ�.
	PrimaryComponentTick.bCanEverTick = false;

	bIsDead = false;
}
