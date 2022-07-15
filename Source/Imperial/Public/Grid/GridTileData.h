// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GridData.h"
#include "GridTileData.generated.h"

UCLASS()
class IMPERIAL_API UGridTileData : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	FIntPoint GridId; 
	UPROPERTY(BlueprintReadOnly)
	FVector GridCenterPoint;
	UPROPERTY(BlueprintReadOnly)
	ETileTerrainType TerrainType = ETileTerrainType::Water;

	UFUNCTION()
	bool IsSame(const UGridTileData* GridTileData) const;
	bool IsSame(const int32 RowId, const int32 ColumnId) const;
	bool IsSame(const FIntPoint InGridId) const; 
};
