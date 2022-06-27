#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CameraConfig.generated.h"


UCLASS()
class IMPERIAL_API UCameraConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "ImperialConfig")
	static UCameraConfig* GetCameraConfig();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera defaults")
	float DefaultSpringArmLength = 500.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera defaults")
	float CameraSpeedMultiplier = 0.5f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera defaults")
	FRotator DefaultCameraRotation;  
	
};
