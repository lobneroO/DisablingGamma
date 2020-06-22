// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HudEditorBase.generated.h"

class UWidgetSwitcher;
class UCanvasPanel;
class UButton;

class ARttCameraActor;

/**
 * 
 */
UCLASS()
class DISABLINGGAMMA_API UHudEditorBase : public UUserWidget
{
	GENERATED_BODY()
	
	virtual void NativeConstruct() override;
	
public:
	void OnToggleButtonClicked();

protected:
	/**
	* Sets up the output of all RttCameras
	*/
	void SetupCompositeView();

	void DestroyComposteView();

	/**
	* Adds a camera's output to the output canvas panel
	*/
	void AddCamera(const ARttCameraActor* camera, const FVector2D position);

public:
	/**
	* The WigetSwitcher has only two children: the EmptyCanvasPanel and the OutputCanvasPanel. It will switch between these two panels
	*/
	UPROPERTY()
	UWidgetSwitcher* WidgetSwitcher = nullptr;

	/**
	* Effictively disables the camera's output in the hud
	*/
	UPROPERTY()
	UCanvasPanel* EmptyCanvasPanel = nullptr;

	/**
	* Effictively enables the camera's output in the hud
	*/
	UPROPERTY()
	UCanvasPanel* OutputCanvasPanel = nullptr;

	/**
	* Toggles between EmptyCanvasPanel and OutputCanvasPanel
	*/
	UPROPERTY()
	UButton* ToggleButton = nullptr;
};
