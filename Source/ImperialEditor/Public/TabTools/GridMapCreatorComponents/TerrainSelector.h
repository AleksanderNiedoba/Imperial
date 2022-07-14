#pragma once
#include "ContentBrowserDelegates.h"
#include "ImperialEditorUtilities.h"
#include "Brushes/SlateColorBrush.h"
#include "Grid/GridData.h"

class SCustomBorder;

class TerrainSelector : public SCompoundWidget
{
	DECLARE_DELEGATE_TwoParams(FOnItemSelected, ETileTerrainType, FTileDefinitionData);
	
	SLATE_BEGIN_ARGS(TerrainSelector)
	{}
	SLATE_DEFAULT_SLOT(FArguments, Content)
	SLATE_EVENT(FOnItemSelected, OnSelected)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	void OnTileSelected(ETileTerrainType TerrainType, FTileDefinitionData TileDefinitionData);
	void SetOnSelected(FOnItemSelected EventHandler); 

protected:
	FOnItemSelected OnTerrainSelected;
	
	TArray<TSharedPtr<class SelectorTileOverlay>> Tiles; 
};




