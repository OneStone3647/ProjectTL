// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectTL.h"
#include "GameFramework/HUD.h"
#include "PTLHUD.generated.h"

/*=========================================================================*
 * LockOn�� Target�� Texture�� ǥ������ HUD Ŭ�����Դϴ�.
 *=========================================================================*/
UCLASS()
class PROJECTTL_API APTLHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	APTLHUD();

public:
	virtual void DrawHUD() override;

private:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Indicator", meta = (AllowPrivateAccess = "true"))
	UTexture* IndicatorTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Indicator", meta = (AllowPrivateAccess = "true"))
	float IndicatorSize;
};
