// Fill out your copyright notice in the Description page of Project Settings.

/*=========================================================================*
 * NPC Ŭ�����Դϴ�.
 *=========================================================================*/

#include "PTLNPC.h"
#include "Components/CapsuleComponent.h"
#include "Components/TextRenderComponent.h"

APTLNPC::APTLNPC()
{
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));

	ActorNameText->SetText(TEXT("NPC"));
}
