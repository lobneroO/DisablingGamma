// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HudEditorBase.h"
#include "DisablingGammaHUD.generated.h"

UCLASS()
class ADisablingGammaHUD : public AHUD
{
	GENERATED_BODY()

public:
	ADisablingGammaHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	UHudEditorBase* HudEditorWidget = nullptr;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

