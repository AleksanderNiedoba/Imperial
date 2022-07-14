#pragma once
#include "ContentBrowserDelegates.h"
#include "Grid/GridProfile.h"

class TileProfileRowDetails : public SCompoundWidget
{
	//DECLARE_DELEGATE_OneParam(FOnLoadClicked, UGridProfile*);
	
	SLATE_BEGIN_ARGS(TileProfileRowDetails)
	{}
	//SLATE_EVENT(FOnLoadClicked, OnLoadClicked)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	
	//FOnLoadClicked OnLoadClicked; 

	void OnAssetLoaded(UGridProfile* InGridProfile);
	void OnTileSelected(FIntPoint SelectedId);
	
protected:
	TSharedPtr<SBorder> PathBorder; 
	TSharedPtr<STextBlock> PathTextBlock;
	TSharedPtr<SHorizontalBox> IdsBox; 
	TSharedPtr<STextBlock> RowIdTextBlock;
	TSharedPtr<STextBlock> ColumnIdTextBlock; 

private:
	UGridProfile* GridProfile = nullptr; 
};

