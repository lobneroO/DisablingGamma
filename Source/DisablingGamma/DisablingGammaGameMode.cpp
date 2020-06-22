// Copyright Epic Games, Inc. All Rights Reserved.

#include "DisablingGammaGameMode.h"
#include "DisablingGammaHUD.h"
#include "DisablingGammaCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "DisablingGammaHUD.h"
#include "HudEditorBase.h"

ADisablingGammaGameMode::ADisablingGammaGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	//we use the blueprint in order to create a blueprint inheriting from HudEditorBase
	static ConstructorHelpers::FClassFinder<AHUD> HudClassFinder(TEXT("Blueprint'/Game/HUD/HUD.HUD_C'"));
	HUDClass = HudClassFinder.Class;
	
	//HUDClass = ADisablingGammaHUD::StaticClass();

	
}

void ADisablingGammaGameMode::SetHudEditor(UHudEditorBase* heb)
{
	HudEditorBase = heb;
	//bind "Alt" + "K" to toggle, since this is a first person game and we wouldn't reach the button in moste cases
	APlayerController* pc = GetWorld()->GetFirstPlayerController();
	if (HudEditorBase && pc)
	{
		pc->InputComponent->BindAction("ToggleOutputPanel", IE_Released, HudEditorBase, &UHudEditorBase::OnToggleButtonClicked);
	}
}

void ADisablingGammaGameMode::BeginPlay()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, "Starting custom game mode.");
}