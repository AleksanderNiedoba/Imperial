#include "Grid/GridMapGenerator.h"
#include "Systems/GridSystem.h"
#include "GameConfig/GameData.h"

void FIslandHelperStruct::FindBorderIds(UGridProfile* GridProfile)
{
	BorderIds.Empty(); 
	for (const auto& TileId : TileIds)
	{
		TArray<FIntPoint> Neighbours = UGridSystem::GetNeighbourIds(TileId);
		for (const auto& NeighbourId : Neighbours)
		{
			if(!TileIds.Contains(NeighbourId))
			{
				BorderIds.Add(TileId);
				break; 
			}
			// if(const FGridProfileData* Data = GridProfile->GridMapProfile.Find(NeighbourId))
			// {
			// 	if(Data->TerrainType == ETileTerrainType::Water)
			// 	{
			// 		BorderIds.Add(NeighbourId);
			// 	}
			// }
		}
	}
}

int32 UGridMapGenerator::GenerateMap(UGridProfile* GridProfile, int32 RandomStreamInt)
{
	const FString HasValidDataString = IsValid(GridProfile) ? "Has valid data" : "Data invalid"; 
	UE_LOG(LogTemp, Warning, TEXT("Map Generator - Generate map called (%s)"), *HasValidDataString);

	GridConfig = UGameData::GetGameData()->GetGridConfig();

	
	const int32 MapSizeX = GridConfig->NumberOfColumns;
	const int32 MapSizeY = GridConfig->NumberOfRows;
	int32 MassTemp = GridConfig->NumberOfDistricts / GridConfig->MinDistrictsGroupSize;
	
	RandomStreamInt = RandomStreamInt != - 1 ? RandomStreamInt : FMath::RandRange(0, 20000);
	const FRandomStream RandomStream = FRandomStream(RandomStreamInt); 

	TArray<FIslandHelperStruct> IslandHelpers = RandomIslands(RandomStream);
	
	TMap<FIntPoint, FGridProfileData>& GridMapProfile = GridProfile->GridMapProfile;
	GridProfile->Reset();

	TArray<FIntPoint> AvailablePoints;

	const int32 MinDistanceFromBorder = GridConfig->MinDistanceFromBorder; 
	for (auto& KV : GridMapProfile)
	{
		if (KV.Key.X < MinDistanceFromBorder || KV.Key.Y < MinDistanceFromBorder || KV.Key.X >= MapSizeX - MinDistanceFromBorder || KV.Key.Y >= MapSizeY - MinDistanceFromBorder)
		{
			continue; 
		}

		AvailablePoints.Add(KV.Key); 
		// if(auto* Data = GridMapProfile.Find(KV.Key))
		// {
		// 	Data->TerrainType = ETileTerrainType::Desert;
		// }
		
		
	}

	for (int32 i = 1; i <= IslandHelpers.Num(); i++)
	{
		const int32 IslandIndex = i -1; 
		const FIntPoint CenterPoint = FIntPoint(AvailablePoints[RandomStream.RandRange(0, AvailablePoints.Num() - 1)]);
		if (FGridProfileData* Data = GridMapProfile.Find(CenterPoint))
		{
			if(AssignTerrain(Data, CenterPoint, AvailablePoints, ETileTerrainType::Marshes))
			{
				Data->IslandId = i;
				IslandHelpers[IslandIndex].TileIds.Add(CenterPoint);
				IslandHelpers[IslandIndex].FindBorderIds(GridProfile); 
			}
			 
		}

		int32 IslandTileSize = RandomizeIslandTileSize(RandomStream, IslandHelpers[IslandIndex].Size);
		int32 RandomHeight = RandomStream.RandRange(GridConfig->MinIslandHeight, GridConfig->MaxIslandHeight);
		int32 RandomWidth = RandomStream.RandRange(GridConfig->MinIslandWidth, GridConfig->MaxIslandWidth);


		int32 SafeCounter = 0; 
		while (IslandTileSize > 0)
		{
			TArray<FIntPoint> AvailableNeighbours;
			const FIntPoint RandomTile = IslandHelpers[IslandIndex].BorderIds[RandomStream.RandRange(0, IslandHelpers[IslandIndex].BorderIds.Num() - 1)];
			TArray<FIntPoint> RandomTileNeighbours = GridSystem->GetNeighbourIds(RandomTile).FilterByPredicate([AvailablePoints](FIntPoint Point) { return AvailablePoints.Contains(Point); });
		
			for(auto& RandomTileId : RandomTileNeighbours)
			{
				if (FGridProfileData* Data = GridMapProfile.Find(RandomTileId))
				{
					if (AssignTerrain(Data, RandomTileId, AvailablePoints, ETileTerrainType::Open))
					{
						Data->IslandId = i;
						IslandHelpers[IslandIndex].TileIds.Add(RandomTileId);
						IslandHelpers[IslandIndex].FindBorderIds(GridProfile); 
						IslandTileSize--; 
					}
					for (auto& RandomTileIdNeighbour : GridSystem->GetNeighbourIds(RandomTileId))
					{
						if (FGridProfileData* DataNeighbour = GridMapProfile.Find(RandomTileIdNeighbour))
						{
							if(DataNeighbour->TerrainType == ETileTerrainType::Water)
							{
								DataNeighbour->IslandId = i;
							}
						}
					}
				}
			}
			SafeCounter++;

			if(SafeCounter > 5000)
				break; 
		//	FIntPoint RandomNeighbourId = AvailableNeighbours[RandomStream.RandRange(0, AvailableNeighbours.Num() - 1)]; 
		}

		for (auto& KV : GridMapProfile)
		{
			if(KV.Value.IslandId != 0 && AvailablePoints.Contains(KV.Key))
			{
				const int32 Index = AvailablePoints.IndexOfByPredicate([KV] (FIntPoint Point) { return Point == KV.Key; });
				AvailablePoints.RemoveAt(Index); 
			}
		}

		//return RandomStreamInt; 
		
	}
	return RandomStreamInt; 
}

bool UGridMapGenerator::AssignTerrain(FGridProfileData* Data, FIntPoint AssignmentPoint,  TArray<FIntPoint>& AvailablePoints, ETileTerrainType Type)
{
	const int32 Index = AvailablePoints.IndexOfByPredicate([AssignmentPoint] (FIntPoint Point) { return Point == AssignmentPoint; });
	if(Index != INDEX_NONE)
	{
		Data->TerrainType = Type;
		AvailablePoints.RemoveAt(Index);
		return true; 
	}

	return false; 
}

TArray<FIslandHelperStruct> UGridMapGenerator::RandomIslands(FRandomStream InRandomStream)
{
	int32 MinNumberOfIslands, MaxNumberOfIslands;
	GridConfig->IslandsRange.GetRange(MinNumberOfIslands, MaxNumberOfIslands);

	const int32 MinIslandSizeParts = GridConfig->NumberOfDistricts / GridConfig->MinDistrictsGroupSize;
	const int32 RandomizedIslandsNumber = InRandomStream.RandRange(MinNumberOfIslands, MaxNumberOfIslands);

	TArray<FIslandHelperStruct> IslandHelpers; 
	for (int32 i = 0; i < RandomizedIslandsNumber; i++)
	{
		IslandHelpers.Add(FIslandHelperStruct(i, 1));
	}

	int32 i = 0; 
	while (i < MinIslandSizeParts - RandomizedIslandsNumber)
	{
		const int32 IslandId = InRandomStream.RandRange(0, RandomizedIslandsNumber - 1);
		IslandHelpers[IslandId].Size += 1;

		i++; 
	}

	UE_LOG(LogTemp, Warning, TEXT("Results: "))
	int32 SizeSum = 0; 
	for (auto& Helper : IslandHelpers)
	{
		UE_LOG(LogTemp, Warning, TEXT("Island Id: %i [Size: %i]"), Helper.Index, Helper.Size);
		SizeSum += Helper.Size; 
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Sum size : %i"), SizeSum);

	IslandHelpers.Sort([](const FIslandHelperStruct& A, const FIslandHelperStruct& B ){ return A.Size > B.Size;});
	return IslandHelpers; 
}

int32 UGridMapGenerator::RandomizeIslandTileSize(FRandomStream InRandomStream, int32 InIslandSize)
{
	int32 MinDistrictSize, MaxDistrictSize;
	GridConfig->DistrictSizeRange.GetRange(MinDistrictSize, MaxDistrictSize);
	
	int32 Result = 0; 
	for (int i = 0; i < InIslandSize * 4; i++)
	{
		Result += InRandomStream.RandRange(MinDistrictSize, MaxDistrictSize); 
	}
	
	return Result; 
}
