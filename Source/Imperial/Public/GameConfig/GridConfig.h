#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GridConfig.generated.h"

USTRUCT(BlueprintType)
struct IMPERIAL_API FIntRange
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MinValue = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MaxValue = 1;

	void GetRange(int32& Min, int32& Max) const 
	{
		Min = MinValue;
		Max = MaxValue; 
	}
	
};

UCLASS()
class IMPERIAL_API UGridConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "ImperialConfig")
	static UGridConfig* GetGridConfig();
	
	UFUNCTION(BlueprintPure, Category = "Grid")
	float GetHalfTileSize() const;
	UFUNCTION(BlueprintPure, Category = "Grid")
	void GetGridSize(float& GridSizeX, float& GridSizeY) const;
	UFUNCTION(BlueprintPure, Category = "Grid")
	FVector GetGridCenterLocation() const;
	

	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Grid")
	int32 NumberOfColumns = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Grid")
	int32 NumberOfRows = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Grid")
	float TileSize = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Grid")
	bool CrossGrid = true; 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Grid")
	TEnumAsByte<ECollisionChannel> GridCollisionChannel;

	// UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Grid|MapGeneration")
	// int32 NumberOfPlayers = 7;
	// UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Grid|MapGeneration")
	// int32 StartingDistricts = 8;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Grid|MapGeneration")
	int32 MinDistrictsGroupSize = 4;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Grid|MapGeneration")
	int32 NumberOfDistricts = 120;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Grid|MapGeneration")
	int32 MinIslandHeight = 3;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Grid|MapGeneration")
	int32 MinIslandWidth= 3;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Grid|MapGeneration")
	int32 MaxIslandHeight = 15;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Grid|MapGeneration")
	int32 MaxIslandWidth= 40;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Grid|MapGeneration")
	int32 MinDistanceFromBorder = 3;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Grid|MapGeneration")
	FIntRange IslandsRange;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Grid|MapGeneration")
	FIntRange DistrictSizeRange;

	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Grid|Minimap")
	FLinearColor WaterColor;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Grid|Minimap")
	FLinearColor OpenTerrainColor;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Grid|Minimap")
	TSoftObjectPtr<UTexture2D> TerrainTexture;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Grid|Debug")
	FLinearColor GridColor;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Grid|Debug")
	float GridOpacity = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Grid|Debug")
	float GridLineThickness = 0; 
};
