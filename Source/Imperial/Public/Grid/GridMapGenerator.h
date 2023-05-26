// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Grid/GridProfile.h"
#include "GridMapGenerator.generated.h"

USTRUCT()
struct IMPERIAL_API FIslandHelperStruct
{
	GENERATED_BODY()

	FIslandHelperStruct()
	{
		Index = -1;
		Size = 0;
	}

	FIslandHelperStruct(int32 InIndex, int32 InSize)
	{
		Index = InIndex;
		Size = InSize;
	}
		
	int32 Index;
	int32 Size;

	TArray<FIntPoint> TileIds;
	TArray<FIntPoint> BorderIds; 
	int32 TileSize = 0;

	void FindBorderIds(UGridProfile* GridProfile); 
};

class UGridConfig; 
UCLASS()
class IMPERIAL_API UGridMapGenerator : public UObject
{
	GENERATED_BODY()

public:
	int32 GenerateMap(UGridProfile* GridProfile, int32 RandomStreamInt = - 1);

	TArray<FIslandHelperStruct> RandomIslands(FRandomStream InRandomStream);
	int32 RandomizeIslandTileSize(FRandomStream InRandomStream, int32 InIslandSize);

	bool AssignTerrain(FGridProfileData* Data, FIntPoint AssignmentPoint, TArray<FIntPoint>& AvailablePoints, ETileTerrainType Type); 


	void SetGridSystem(class UGridSystem* InGridSystem) { GridSystem = InGridSystem; } 

private:
	UPROPERTY()
	UGridConfig* GridConfig = nullptr;
	UPROPERTY()
	class UGridSystem* GridSystem = nullptr;
};



