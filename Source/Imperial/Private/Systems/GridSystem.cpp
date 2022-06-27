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

bool UGridSystem::CreateGrid()
{
	const float TileSize = GridConfig->TileSize;
	
	for (int RowIndex = 0; RowIndex < GridConfig->NumberOfRows; RowIndex++)
	{
		
		FGridRowData NewRowData;
		NewRowData.RowId = RowIndex;

		const bool IsEven = GridConfig->CrossGrid && RowIndex % 2 == 0;		
		for (int ColumnIndex = 0; ColumnIndex < GridConfig->NumberOfColumns; ColumnIndex++)
		{
			auto* GridData = NewObject<UGridTileData>();
			GridData->GridId = FVector2D(RowIndex, ColumnIndex);

			
			const float HalfTileSize = TileSize / 2.f; 
			const float CrossGridShift = IsEven ? HalfTileSize : 0.f;
			
			const float CenterPointY = ColumnIndex * TileSize + CrossGridShift;
			const float CenterPointX = RowIndex * TileSize + HalfTileSize;
			
			GridData->GridCenterPoint = FVector(CenterPointX, CenterPointY, 0.f);

			NewRowData.RowGridData.Add(GridData); 
		}
		Grid.Add(NewRowData); 
	}

	return true; 
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
