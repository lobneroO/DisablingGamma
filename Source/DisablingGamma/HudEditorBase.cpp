// Fill out your copyright notice in the Description page of Project Settings.


#include "HudEditorBase.h"

#include "Components/WidgetSwitcher.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "SlateMaterialBrush.h"

#include "RttCameraActor.h"
#include "Styling/SlateBrush.h"

#include "DisablingGammaGameMode.h"

#include "Kismet/GameplayStatics.h"

void UHudEditorBase::NativeConstruct()
{
	WidgetSwitcher = (UWidgetSwitcher*)GetWidgetFromName(TEXT("OutputWidgetSwitcher"));

	EmptyCanvasPanel = (UCanvasPanel*)GetWidgetFromName(TEXT("EmptyCanvasPanel"));
	OutputCanvasPanel = (UCanvasPanel*)GetWidgetFromName(TEXT("OutputCanvasPanel"));

	WidgetSwitcher->SetActiveWidget(EmptyCanvasPanel);

	ToggleButton = (UButton*)GetWidgetFromName(TEXT("PanelToggleButton"));
	if (ToggleButton)
	{
		ToggleButton->OnClicked.AddDynamic(this, &UHudEditorBase::OnToggleButtonClicked);
	}

	ADisablingGammaGameMode*  gm = Cast<ADisablingGammaGameMode>(GetWorld()->GetAuthGameMode());
	gm->SetHudEditor(this);
}

void UHudEditorBase::OnToggleButtonClicked()
{
	if (WidgetSwitcher->GetActiveWidget() == EmptyCanvasPanel)
	{
		WidgetSwitcher->SetActiveWidget(OutputCanvasPanel);
		SetupCompositeView();
	}
	else
	{
		WidgetSwitcher->SetActiveWidget(EmptyCanvasPanel);
		DestroyComposteView();
	}
}

void UHudEditorBase::SetupCompositeView()
{
	//for every camera actor, add a uimage to the hud
	//this uimage is the one we want to display with gamma disabled

	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARttCameraActor::StaticClass(), actors);

	//keep track of the position we can use next. initially this is the upper left, then we simply add
	//the size of the last camera's width until the screen is filled in width
	//then we can add a new line and start at 0

	//for ease of use, we keep all sizes at 512, with a width of 1920 total.
	//might not work in all cases, but is sufficient for a minimal working example
	FVector2D position(0, 0);

	for (AActor* actor : actors)
	{
		ARttCameraActor* camera = Cast<ARttCameraActor>(actor);
		if (camera)
		{
			AddCamera(camera, position);
			position.X += 512;
		}

		//if we reach the end of the "line", 
		//start a new one
		if (position.X >= 1920 - 512)
		{
			position.X = 0;
			position.Y += 512;
		}
	}
}

void UHudEditorBase::DestroyComposteView()
{
	OutputCanvasPanel->ClearChildren();
}

void UHudEditorBase::AddCamera(const ARttCameraActor* camera, const FVector2D position)
{
	UImage* img = NewObject<UImage>(UImage::StaticClass());
	img->SetVisibility(ESlateVisibility::Visible);
	OutputCanvasPanel->AddChild(img);

	//correctly set the position and size of the slot to have image properly displayed in the viewport
	TArray<UPanelSlot*> slots = OutputCanvasPanel->GetSlots();

	//the image now is at the  last slot
	UCanvasPanelSlot* imageSlot = Cast<UCanvasPanelSlot>(slots[slots.Num() - 1]);
	//size is hardcoded to 512, 512
	imageSlot->SetSize(FVector2D(512, 512));
	imageSlot->SetPosition(position);

	UMaterialInstanceDynamic* sensorMaterialDynamic = camera->CameraMaterial;

	img->Brush = FSlateMaterialBrush(*sensorMaterialDynamic, imageSlot->GetSize());

	img->Brush.Tiling = ESlateBrushTileType::NoTile;
	img->Brush.Mirroring = ESlateBrushMirrorType::NoMirror;
	img->Brush.DrawAs = ESlateBrushDrawType::Image;
	if (camera->bIsLinearColor)
	{
		img->Brush.ImageType = ESlateBrushImageType::Linear;
	}
	else
	{
		img->Brush.ImageType = ESlateBrushImageType::FullColor;
	}
	
}