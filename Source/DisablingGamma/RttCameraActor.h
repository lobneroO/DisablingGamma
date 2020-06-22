// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

//#include "Engine/TextureRenderTarget2D.h"
//#include <Components/SceneCaptureComponent2D.h>

#include "RttCameraActor.generated.h"

class UTextureRenderTarget2D;
class USceneCaptureComponent2D;

UCLASS()
class DISABLINGGAMMA_API ARttCameraActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARttCameraActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	virtual void PostInitializeComponents() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	/**
	* Render target to be displayed on screen with gamma disabled
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient)
	UTextureRenderTarget2D* TextureTarget = nullptr;

	/** 
	* The camera component for rendering to the render target
	*/
	UPROPERTY(EditAnywhere)
	USceneCaptureComponent2D* Camera = nullptr;

	/**
	* The Material we will create a MaterialInstanceDynamic from
	*/
	UPROPERTY(EditAnywhere)
	UMaterial* CameraBaseMaterial = nullptr;

	/**
	* The Material we will set parameters for and which will be used to render the 
	* Camera's output into the UImage
	*/
	UPROPERTY(VisibleAnywhere)
	UMaterialInstanceDynamic* CameraMaterial = nullptr;

private:
	/**
	* Simple time tracker for movement with sin
	*/
	float TimePassed = 0.0f;

	/**
	* Speeding up simply for ease of use
	*/
	UPROPERTY(EditAnywhere)
	float SpeedMultiplier = 50.0f;

	/**
	* The (half)distance the actor travels along the x axis
	*/
	UPROPERTY(EditAnywhere)
	float Distance = 500;

	/**
	* For movement from the original position
	*/
	FVector OriginalPosition;
};
