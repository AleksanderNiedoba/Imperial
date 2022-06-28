// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GridData.h"
#include "TileDefinitions.generated.h"

USTRUCT(BlueprintType)
struct FTileDefinitionData
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
};

UCLASS()
class IMPERIAL_API UTileDefinitions : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "TileDefinition")
	TMap<ETileTerrainType, FTileDefinitionData> GridDefinitions;

	UFUNCTION(BlueprintPure)
	bool GetTileDefinitionForType(ETileTerrainType TerrainType, FTileDefinitionData& TileDefinition);

#if WITH_EDITOR
	virtual void PostLoad() override;
#endif
};
