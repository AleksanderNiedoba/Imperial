// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/ImperialCameraPawn.h"
#include "GameConfig/CameraConfig.h"

void AImperialCameraPawn::CacheDefaults()
{
	const auto* CC = UCameraConfig::GetCameraConfig(); 
	DefaultSpringArmLength = CC->DefaultSpringArmLength;
	CameraSpeedMultiplier = CC->CameraSpeedMultiplier;
	DefaultCameraRotation = CC->DefaultCameraRotation; 
}
