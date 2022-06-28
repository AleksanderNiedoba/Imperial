// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid/TileDefinitions.h"


bool UTileDefinitions::GetTileDefinitionForType(ETileTerrainType TerrainType, FTileDefinitionData& TileDefinition)
{
	if(!GridDefinitions.Contains(TerrainType))
	{
		return false; 
	}

	TileDefinition = *GridDefinitions.Find(TerrainType);
	return true; 
}

#if WITH_EDITOR

void UTileDefinitions::PostLoad()
{
	Super::PostLoad();
	auto CachedDefinitions = GridDefinitions; 
	if (GridDefinitions.Num() <= 0 || GridDefinitions.Num() != (int32)ETileTerrainType::Count)
	{
		GridDefinitions.Empty(); 
		for (ETileTerrainType Terrain : TEnumRange<ETileTerrainType>())
		{
			if(CachedDefinitions.Num() != 0 && CachedDefinitions.Contains(Terrain))
			{
				GridDefinitions.Add(Terrain, *CachedDefinitions.Find(Terrain));
				continue;
			}
			GridDefinitions.Add(Terrain, FTileDefinitionData());
				 
		}
	}
}

#endif