// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OverworldCameraPawn.h"
#include "ImperialCameraPawn.generated.h"


UCLASS()
class IMPERIAL_API AImperialCameraPawn : public AOverworldCameraPawn
{
	GENERATED_BODY()

protected:
	void CacheDefaults() override;
};
