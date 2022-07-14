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
	Count UMETA(Hidden)
};
ENUM_RANGE_BY_COUNT(ETileTerrainType, ETileTerrainType::Count)

USTRUCT(BlueprintType)
struct FGridProfileData
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	ETileTerrainType TerrainType; 
};

USTRUCT(BlueprintType)
struct IMPERIAL_API FTileDefinitionData
{
	GENERATED_BODY()

	FTileDefinitionData() = default; 
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FColor TileMinimapColor;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSoftObjectPtr<UTexture> TileIcon;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FText TileName;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FText TileDescription;

	FORCEINLINE bool operator == (const FTileDefinitionData& Other) const 
	{
		return TileName.ToString() == Other.TileName.ToString(); 
	}
};