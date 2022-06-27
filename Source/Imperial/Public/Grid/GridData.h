// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GridData.generated.h"


UENUM(BlueprintType)
enum class ETileTerrainType : uint8 
{
	Water = 0,
	Hills,
	Mountains,
	Desert,
	Forest,
	Marshes,
	Open,
	River
};