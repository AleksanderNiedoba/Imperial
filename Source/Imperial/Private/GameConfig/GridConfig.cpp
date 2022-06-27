#include "GameConfig/GridConfig.h"
#include "GameConfig/GameData.h"

UGridConfig* UGridConfig::GetGridConfig()
{
	if(auto* GD = UGameData::GetGameData())
	{
		return GD->GetGridConfig();
	}
	return nullptr;  
}

float UGridConfig::GetHalfTileSize() const
{
	return TileSize / 2.f; 
}

void UGridConfig::GetGridSize(float& GridSizeX, float& GridSizeY) const
{
	GridSizeX = NumberOfRows * TileSize;
	GridSizeY = NumberOfColumns * TileSize; 
}

FVector UGridConfig::GetGridCenterLocation() const
{
	float GridSizeX, GridSizeY;
	GetGridSize(GridSizeX, GridSizeY);
	return FVector(GridSizeX / 2, GridSizeY / 2, 0.f);
}
