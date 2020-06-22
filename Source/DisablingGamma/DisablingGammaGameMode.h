// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DisablingGammaGameMode.generated.h"

class UHudEditorBase;

UCLASS(minimalapi)
class ADisablingGammaGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADisablingGammaGameMode();

	/**
	* The hud editor is created after begin play of the game mode
	* Therefore let it set itself to the game mode
	*/
	void SetHudEditor(UHudEditorBase* heb);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	UHudEditorBase* HudEditorBase = nullptr;
};



