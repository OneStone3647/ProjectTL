// Fill out your copyright notice in the Description page of Project Settings.

#include "PTLStateComponent.h"

UPTLStateComponent::UPTLStateComponent()
{
	// Tick �Լ��� ������� �ʽ��ϴ�.
	PrimaryComponentTick.bCanEverTick = false;

	bIsDead = false;
}

 bool UPTLStateComponent::GetIsDead() const
 {
	 return bIsDead;
 }

 void UPTLStateComponent::SetIsDead(bool bFlag)
 {
	 bIsDead = bFlag;
 }

