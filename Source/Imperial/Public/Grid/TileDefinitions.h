// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GridData.h"
#include "TileDefinitions.generated.h"

UCLASS()
class IMPERIAL_API UTileDefinitions : public UDataAsset
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure)
	static UTileDefinitions* GetTileDefinitions(); 
	

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "TileDefinition")
	TMap<ETileTerrainType, FTileDefinitionData> GridDefinitions;

	UFUNCTION(BlueprintPure)
	bool GetTileDefinitionForType(ETileTerrainType TerrainType, FTileDefinitionData& TileDefinition);

#if WITH_EDITOR
	virtual void PostLoad() override;
#endif
};
