#pragma once
#include "ContentBrowserDelegates.h"
#include "Grid/GridProfile.h"

class TileProfileSelector : public SCompoundWidget
{
	DECLARE_DELEGATE_OneParam(FOnButtonClicked, UGridProfile*);
	
	SLATE_BEGIN_ARGS(TileProfileSelector)
	{}
	SLATE_ARGUMENT( int32, NumOfPools )
	SLATE_ARGUMENT( bool, ShouldCenterThumbnail )
	SLATE_ARGUMENT( bool, InAreRealTimeThumbnailsAllowed )
	SLATE_EVENT(FOnButtonClicked, OnLoadClicked)
	SLATE_EVENT(FOnButtonClicked, OnSaveClicked)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	
	TSharedRef<SWidget> OnGetMenuContent();
	FOnShouldFilterAsset OnShouldFilterAsset;

	void OnAssetSelectedFromPicker( const FAssetData& InAssetData );
	void CloseMenu();

	FOnButtonClicked OnLoadClicked;
	FOnButtonClicked OnSaveClicked; 
	
protected:
	
	TSharedPtr<FAssetThumbnailPool> ThumbnailPool;
	TSharedPtr<FAssetThumbnail> AssetThumbnail;
	TSharedPtr<SComboButton> ComboButton;
	class UGridConfig* GridConfig = nullptr;
	UGridProfile* GridProfile = nullptr;

private:
	int32 NumOfPools = 0; 
	bool ThumbnailsAllowed = true;
	bool CenterThumbnail = true; 
};

