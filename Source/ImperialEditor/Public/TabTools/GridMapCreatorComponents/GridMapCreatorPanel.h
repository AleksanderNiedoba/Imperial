#pragma once
#include "ContentBrowserDelegates.h"
#include "Grid/GridProfile.h"


enum EGridMapCreatorTool
{
	None,
	Terrain
};

class GridMapCreatorPanel : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(GridMapCreatorPanel)
	{}
	SLATE_ARGUMENT(TWeakPtr<class GridMapCreator>, Tool)
	SLATE_ARGUMENT( bool, ShouldCenterThumbnail )
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	FOnShouldFilterAsset OnShouldFilterAsset;

	void OnAssetLoaded(UGridProfile* InGridProfile);
	void OnTileSelected(FIntPoint TileId);

	void OnTerrainTypeSelected(ETileTerrainType NewTerrainData, FTileDefinitionData NewTileDefinition); 

	
protected:
	
	TSharedPtr<class TileProfileRowDetails> ProfileRowDetails;
	TSharedPtr<class ClickableHyperlinkMap> ClickableMap;
	TWeakPtr<GridMapCreator> GridMapCreator;
	class UGridConfig* GridConfig = nullptr;
	UGridProfile* GridProfile = nullptr;
	

private:
	FTileDefinitionData TileDefinitionData; 
	ETileTerrainType CurrentTileData = ETileTerrainType::Water;
	EGridMapCreatorTool CurrentTool = EGridMapCreatorTool::None; 
};





