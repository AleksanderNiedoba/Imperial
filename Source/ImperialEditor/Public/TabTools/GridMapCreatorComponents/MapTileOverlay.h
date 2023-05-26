#pragma once
#include "ContentBrowserDelegates.h"
#include "ImperialEditorUtilities.h"
#include "TileOverlay.h"
#include "Brushes/SlateColorBrush.h"
#include "Grid/GridProfile.h"

class SCustomBorder;

class MapTileOverlay : public TileOverlay
{
	DECLARE_DELEGATE_OneParam(FOnTileEvent, FIntPoint);
	
	SLATE_BEGIN_ARGS(MapTileOverlay)
		: _Content()
		, _ColorAndOpacity()
	
		{}
		SLATE_DEFAULT_SLOT(FArguments, Content)
		SLATE_ARGUMENT(FLinearColor, ColorAndOpacity)
		SLATE_ARGUMENT(FIntPoint, TileId)
		SLATE_ARGUMENT(uint8, IslandId)
		SLATE_EVENT(FOnTileEvent, OnSelected)
		SLATE_EVENT(FOnTileEvent, OnHovered)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	void SetOnSelect(FOnTileEvent EventHandler);
	void SetOnHover(FOnTileEvent EventHandler); 

	virtual void Navigate() override; 
	virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;
		
protected:
	TSharedPtr<SCustomBorder> TileColorBorder;
	
	FIntPoint TileId = FIntPoint(-1, -1); 
	FOnTileEvent OnSelect;
	FOnTileEvent OnHover; 

};



