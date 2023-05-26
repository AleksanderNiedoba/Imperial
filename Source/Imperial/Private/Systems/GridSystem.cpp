// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/GridSystem.h"
#include "Core/IGameSystems.h"
#include "GameConfig/GridConfig.h"
#include "Grid/GridTileData.h"


UGridSystem* UGridSystem::GetGridSystem(const UObject* InWorldContextObject)
{
	if (!InWorldContextObject || !InWorldContextObject->GetWorld())
	{
		return nullptr;
	}
	
	if (const auto* Systems = Cast<IGameSystems>(InWorldContextObject->GetWorld()->GetGameInstance()))
	{
		return Systems->GetGridSystem();
	}
	return nullptr;
}

UGridSystem* UGridSystem::CreateNew()
{
	auto* Instance = NewObject<UGridSystem>();
	Instance->GridConfig = UGridConfig::GetGridConfig();
	return Instance; 
}

UGridMapGenerator* UGridSystem::GetGridMapGenerator()
{
	if(!IsValid(MapGenerator))
	{
		MapGenerator = NewObject<UGridMapGenerator>();
		MapGenerator->SetGridSystem(this); 
	}
	
	return MapGenerator; 
}

bool UGridSystem::CreateGrid()
{
		
	for (int RowIndex = 0; RowIndex < GridConfig->NumberOfRows; RowIndex++)
	{
		
		FGridRowData NewRowData;
		NewRowData.RowId = RowIndex;
		
		for (int ColumnIndex = 0; ColumnIndex < GridConfig->NumberOfColumns; ColumnIndex++)
		{
			auto* GridData = NewObject<UGridTileData>();
			GridData->GridId = FIntPoint(RowIndex, ColumnIndex);
			GridData->GridCenterPoint = CalculateTileCenterPoint(RowIndex, ColumnIndex);

			NewRowData.RowGridData.Add(GridData); 
		}
		Grid.Add(NewRowData); 
	}

	return true; 
}

FVector UGridSystem::CalculateTileCenterPoint(int32 RowId, int32 ColumnId) const 
{
	const float TileSize = GridConfig->TileSize; 
	const float HalfTileSize = GridConfig->GetHalfTileSize(); 
	const float CenterPointX = RowId * TileSize + HalfTileSize;
	float CenterPointY;
	
	if(!GridConfig->CrossGrid)
	{
		CenterPointY = ColumnId * TileSize + HalfTileSize;
	}
	else
	{
		const float CrossGridShift = RowId % 2 == 0 ? HalfTileSize : 0.f;
		CenterPointY = ColumnId * TileSize + CrossGridShift;
	}

	return FVector(CenterPointX, CenterPointY, 0.f); 
}

UGridTileData* UGridSystem::GetGridDataById(int32 RowId, int32 ColumnId)
{
	auto* RowGridDataPtr = Grid.FindByPredicate([=] (const FGridRowData GridRowData) { return GridRowData.RowId == RowId; });
	if(!RowGridDataPtr)
	{
		return nullptr; 
	}

	return RowGridDataPtr->RowGridData.IsValidIndex(ColumnId) ? RowGridDataPtr->RowGridData[ColumnId] : nullptr;
}

void UGridSystem::ProcessGridHitData(FHitResult HitResult)
{
	int32 RowId, ColumnId;
	if(HitResult.bBlockingHit && GetGridIdFromLocation(HitResult.Location, RowId, ColumnId))
	{
		if(IsValid(HitGridData) && HitGridData->IsSame(RowId, ColumnId))
		{
			return; 
		}

		HitGridData = GetGridDataById(RowId, ColumnId);
		OnNewGridTileHit.Broadcast(HitGridData);
		return; 
	}
	
	if(!IsValid(HitGridData))
	{
		return;
	}
	HitGridData = nullptr;
	OnNewGridTileHit.Broadcast(nullptr); 
	
}

TArray<UGridTileData*> UGridSystem::GetNeighbours(const UGridTileData* GridTileData)
{
	TArray<UGridTileData*> Result; 
	for(const auto TileId : GetNeighbourIds(GridTileData->GridId))
	{
		Result.Add(GetGridDataById(TileId.X, TileId.Y)); 
	}

	return Result; 
}

TArray<FIntPoint> UGridSystem::GetNeighbourIds(FIntPoint GridId)
{
	TArray<FIntPoint> Result;
	const UGridConfig* GC = UGridConfig::GetGridConfig(); 
	
	TArray<FIntPoint> HNeighbours; 
	if(GridId.Y == 0)
	{
		HNeighbours.Add(FIntPoint(GridId.X, GC->NumberOfRows -1));
		HNeighbours.Add(FIntPoint(GridId.X, GridId.Y + 1));
	}
	else if(GridId.Y == GC->NumberOfRows -1)
	{
		HNeighbours.Add(FIntPoint(GridId.X, GridId.Y - 1));
		HNeighbours.Add(FIntPoint(GridId.X, 0));
	}
	else
	{
		HNeighbours.Add(FIntPoint(GridId.X, GridId.Y - 1));
		HNeighbours.Add(FIntPoint(GridId.X, GridId.Y + 1));
	}

	Result.Append(HNeighbours);

	if(GridId.X < GC->NumberOfColumns - 1)
	{
		Result.Append(GetVNeighbourIds(GridId, EVNeighbourRelation::Top));
	}

	if(GridId.X > 0)
	{
		Result.Append(GetVNeighbourIds(GridId, EVNeighbourRelation::Bottom));
	}

	return Result; 
}

TArray<FIntPoint> UGridSystem::GetVNeighbourIds(FIntPoint GridId, EVNeighbourRelation Relation)
{
	const UGridConfig* GC = UGridConfig::GetGridConfig(); 
	const int32 RowDifference = Relation == EVNeighbourRelation::Top ? 1 : - 1;
	TArray<FIntPoint> Result; 

	if(GridId.X % 2 == 0)
	{
		const int32 RightTopNeighbourId = GridId.Y != GC->NumberOfRows - 1 ?
			GridId.Y + 1 : 0;
			
		Result.Add(FIntPoint(GridId.X + RowDifference, GridId.Y));
		Result.Add(FIntPoint(GridId.X + RowDifference,RightTopNeighbourId));			
	}
	else
	{
		const int32 LeftTopNeighbourId = GridId.Y == 0 ? GC->NumberOfRows - 1 : GridId.Y - 1;  
			
		Result.Add(FIntPoint(GridId.X + RowDifference, LeftTopNeighbourId));
		Result.Add(FIntPoint(GridId.X + RowDifference, GridId.Y ));
	}

	return Result; 
}

bool UGridSystem::IsLocationValid(FVector Location) const
{
	float GridSizeX, GridSizeY;
	GridConfig->GetGridSize(GridSizeX, GridSizeY); 
	return Location.X >= 0 && Location.Y >= 0 && Location.X <= GridSizeX && Location.Y <= GridSizeY; 
}

UGridTileData* UGridSystem::GetCurrentHitGridData() const 
{
	return IsValid(HitGridData) ? HitGridData : nullptr; 
}

bool UGridSystem::GetGridIdFromLocation(FVector Location, int32& RowId, int32& ColumnId)
{
	if (!IsLocationValid(Location))
	{
		return false; 
	}

	const float TileSize = GridConfig->TileSize; 
	RowId = FMath::Floor(Location.X / TileSize);
	if(!GridConfig->CrossGrid || RowId % 2 == 0)
	{
		ColumnId = FMath::Floor(Location.Y / TileSize);
		return true; 
	}
	
	float GridSizeX, GridSizeY;
	const float HalfTileSize = GridConfig->GetHalfTileSize();
	
	GridConfig->GetGridSize(GridSizeX, GridSizeY);
	if(Location.Y <= HalfTileSize || Location.Y > GridSizeY - HalfTileSize)
	{
		ColumnId = 0; 
	}
	else
	{
		ColumnId = FMath::Floor((Location.Y + HalfTileSize)  / TileSize);
	}
	
	return true; 
}
