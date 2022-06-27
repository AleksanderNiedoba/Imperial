// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OverworldBaseSettings.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Pawn.h"
#include "OverworldCameraPawn.generated.h"

UCLASS()
class OVERWORLDBASE_API AOverworldCameraPawn : public APawn
{
	GENERATED_BODY()

public:
	AOverworldCameraPawn();
	
	//Camera Components 
	UPROPERTY()
	USceneComponent* CameraRootComponent;
	UPROPERTY()
	USceneComponent* HorizontalSpanRoot;
	UPROPERTY()
	USceneComponent* VerticalSpanRoot;
	UPROPERTY(BlueprintReadWrite)
	UCameraComponent* CameraComponent;
	UPROPERTY()
	USpringArmComponent* CameraSpringArm;

protected:
	virtual void BeginPlay() override;
	virtual void CacheDefaults();

	void SetupCameraDefaults();
	void UpdateZoomDistance();

public:	
	virtual void Tick(float DeltaTime) override;
	void MoveCamera(const EScreenMovement Direction);
	void AdjustCameraSpan(const float MouseX, const float MouseY) const;
	void RequestZoomChange(const EZoomState ZoomState);

	UFUNCTION(BlueprintImplementableEvent)
	void Draw(FVector Location); 

protected:
	float DefaultSpringArmLength = 0.f;
	float MaxZoomDistance = 0.f;
	float MinZoomDistance = 0.f;
	float CameraSpeedMultiplier = 0.f;
	float CameraZoomSpeedMultiplier = 0.f;
	float MaxVerticalSpan = 0.f;
	float MinVerticalSpan = 0.f;
	FRotator DefaultCameraRotation;
	
private:
	float DestZoomDistance;
	bool NeedZoomUpdate;
	

};
