// Fill out your copyright notice in the Description page of Project Settings.

#include "RttCameraActor.h"

#include "Engine/TextureRenderTarget2D.h"
#include <Components/SceneCaptureComponent2D.h>
#include <Materials/Material.h>
#include <Materials/MaterialInstanceDynamic.h>

#include <UObject/ConstructorHelpers.h>

// Sets default values
ARttCameraActor::ARttCameraActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//setup the camera and render target for rendering
	Camera = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Sensor Camera"));
	if (Camera)
	{
		Camera->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		Camera->CaptureSource = ESceneCaptureSource::SCS_FinalToneCurveHDR;

		TextureTarget = NewObject<UTextureRenderTarget2D>();

		TextureTarget->ClearColor = FLinearColor::Black;
		TextureTarget->InitAutoFormat(512, 512);

		Camera->TextureTarget = TextureTarget;
	}

	ConstructorHelpers::FObjectFinder<UMaterial> material(TEXT("Material'/Game/Materials/M_RttCamera.M_RttCamera'"));
	CameraBaseMaterial = material.Object;

}

// Called when the game starts or when spawned
void ARttCameraActor::BeginPlay()
{
	Super::BeginPlay();
	
	OriginalPosition = GetActorLocation();
}

void ARttCameraActor::PostInitializeComponents()
{
	//method that is called after the constructor but before begin play
	//(all default values have been set by this time, is only called during gameplay)
	Super::PostInitializeComponents();

	CameraMaterial = UMaterialInstanceDynamic::Create(CameraBaseMaterial, this);
	if (TextureTarget)
	{
		TextureTarget->TargetGamma = 1.0;
		TextureTarget->bForceLinearGamma = true;

	}
	if (!Camera->TextureTarget && TextureTarget)
	{
		Camera->TextureTarget = TextureTarget;
	}

	CameraMaterial->SetTextureParameterValue(TEXT("CameraOutput"), TextureTarget);
}

// Called every frame
void ARttCameraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//for a simple animation, just move on the x-axis 
	TimePassed += DeltaTime;
	SetActorLocation(OriginalPosition + FVector(FMath::Sin(TimePassed) * Distance, 0, 0));
}

