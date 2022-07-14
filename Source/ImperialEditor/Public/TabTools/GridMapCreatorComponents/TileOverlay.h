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
	bool IsSelected() const { return bIsSelected; } 

	virtual void Navigate();
	virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;


		
protected:
	FLinearColor SelectedColor; 
	TSharedPtr<SCustomBorder> TileColorBorder;
	bool bIsSelected = false; 
	
};



