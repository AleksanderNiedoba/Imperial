#pragma once
#include "Grid/GridProfile.h"


class ClickableHyperlinkMap : public SCompoundWidget
{
	DECLARE_DELEGATE_OneParam(FTileEvent, FIntPoint);
	
	SLATE_BEGIN_ARGS(ClickableHyperlinkMap)
	{}
	SLATE_EVENT(FTileEvent, OnTileSelected)
	SLATE_EVENT(FTileEvent, OnTileHovered)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	void InitWithProfile(UGridProfile* GridProfile);
	void Clear();
	void OnSelected(FIntPoint SelectedId);
	void OnHovered(FIntPoint SelectedId);
	void SetTileData(FIntPoint TileId, struct FTileDefinitionData TileDefinition); 

protected:
	TMap<FIntPoint, TSharedRef<class MapTileOverlay>> ButtonsMap;

private:
	FTileEvent OnTileSelected;
	FTileEvent OnTileHovered; 
	
};

