#pragma once
#include "ContentBrowserDelegates.h"
#include "ImperialEditorUtilities.h"
#include "Brushes/SlateColorBrush.h"
#include "Grid/GridProfile.h"

class SCustomBorder;

class TileOverlay : public SOverlay
{
	
	SLATE_BEGIN_ARGS(TileOverlay)
	{}
	SLATE_DEFAULT_SLOT(FArguments, Content)
	SLATE_ARGUMENT(FLinearColor, ColorAndOpacity)
	SLATE_ARGUMENT(FLinearColor, SelectedColor)
	SLATE_ARGUMENT(bool, HandlePressEvents)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	void SetColorAndOpacity(FLinearColor Color);
	void SetSelected(bool NewSelected);
	void SetIslandId(int32 InIslandId);
	void SetShowIslandId(bool InShowIslandId);
	void RefreshVisibility();
	bool IsSelected() const { return bIsSelected; }
	

	virtual void Navigate();
	virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;


		
protected:
	int32 IslandId = -1;
	bool ShowIslandId = false; 
	
	FLinearColor SelectedColor; 
	TSharedPtr<SCustomBorder> TileColorBorder;
	TSharedPtr<STextBlock> IslandIdText;
	bool bIsSelected = false; 
	
};





