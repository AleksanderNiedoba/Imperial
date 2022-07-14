#pragma once
#include "ContentBrowserDelegates.h"
#include "TileOverlay.h"
#include "Grid/GridData.h"


class SCustomBorder;

class SelectorTileOverlay : public TileOverlay
{
	DECLARE_DELEGATE_TwoParams(FOnTileEvent, ETileTerrainType, FTileDefinitionData);
	
	SLATE_BEGIN_ARGS(SelectorTileOverlay)
		: _Content()
		, _ColorAndOpacity()
		, _SelectedColor()
		, _HandlePressEvents(true)
		{}
		SLATE_DEFAULT_SLOT(FArguments, Content)
		SLATE_ARGUMENT(FLinearColor, ColorAndOpacity)
		SLATE_ARGUMENT(ETileTerrainType, TerrainType)
		SLATE_ARGUMENT(FTileDefinitionData, TileDefinition)
		SLATE_ARGUMENT(FLinearColor, SelectedColor)
		SLATE_ARGUMENT(bool, HandlePressEvents)
		SLATE_EVENT(FOnTileEvent, OnSelected)
		SLATE_EVENT(FOnTileEvent, OnHovered)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	void SetOnSelect(FOnTileEvent EventHandler);
	void SetOnHover(FOnTileEvent EventHandler);
	ETileTerrainType GetTileDefinition() const { return TerrainType; }

	virtual void Navigate() override; 
	virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;

		
protected:
	TSharedPtr<SCustomBorder> TileColorBorder;

	FTileDefinitionData TileDefinitionData; 
	ETileTerrainType TerrainType = ETileTerrainType::Water; 
	FOnTileEvent OnSelect;
	FOnTileEvent OnHover; 

};



