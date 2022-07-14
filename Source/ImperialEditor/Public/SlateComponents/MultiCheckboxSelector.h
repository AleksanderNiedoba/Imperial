#pragma once
#include "ContentBrowserDelegates.h"
#include "ImperialEditorUtilities.h"
#include "SCheckBoxList.h"
#include "Brushes/SlateColorBrush.h"
#include "Grid/GridProfile.h"

class SCustomBorder;

class MultiCheckboxSelector : public SCompoundWidget
{
	DECLARE_DELEGATE_OneParam(FOnTileEvent, FIntPoint);
	
	SLATE_BEGIN_ARGS(MultiCheckboxSelector)
	{}
	SLATE_DEFAULT_SLOT(FArguments, Content)
	SLATE_ARGUMENT(TArray<TSharedPtr<SCheckBoxList>>)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);


};



