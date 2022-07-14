#include "Grid/GridProfile.h"

#include "GameConfig/GridConfig.h"

void UGridProfile::OnProfileCreated()
{
	GridMapProfile.Empty(); 
	const auto* GC = UGridConfig::GetGridConfig();
	for (int32 RowIndex =0; RowIndex < GC->NumberOfRows; RowIndex++)
	{
		for (int32 ColumnIndex =0; ColumnIndex < GC->NumberOfColumns; ColumnIndex++)
		{
			FIntPoint TileId = FIntPoint(RowIndex, ColumnIndex);
			FGridProfileData GridProfileData = FGridProfileData(); 
			GridMapProfile.Add(TileId, GridProfileData); 
		}
	}
}
