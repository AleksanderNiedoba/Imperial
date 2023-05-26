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
	void InitWithProfile(UGridProfile* InGridProfile);
	void RefreshButtonsState(); 
	void Clear();
	void OnSelected(FIntPoint SelectedId);
	void OnHovered(FIntPoint SelectedId);
	void SetTileData(FIntPoint TileId, struct FTileDefinitionData TileDefinition);

	TSharedPtr<SPanel> CreatePanel(bool CreateEmpty); 

protected:
	TMap<FIntPoint, TSharedRef<class MapTileOverlay>> ButtonsMap;

private:
	
	UGridProfile* GridProfile = nullptr; 
	FTileEvent OnTileSelected;
	FTileEvent OnTileHovered; 
	
};

inline TSharedPtr<SPanel> ClickableHyperlinkMap::CreatePanel(bool CreateEmpty)
{
	return SNew(SBox); 
}

