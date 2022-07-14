#pragma once

#include "Widgets/Layout/SBorder.h"
#include "Brushes/SlateColorBrush.h"
#include "ImperialEditorUtilities.h"

class IMPERIALEDITOR_API  SCustomBorder : public SBorder
{
public:
	SLATE_BEGIN_ARGS(SCustomBorder)
		: _Content()
		, _HAlign(HAlign_Fill)
		, _VAlign(VAlign_Fill)
		, _Padding(FMargin(2.0f))
		, _BorderSize(FMargin(2.0f))
		, _BorderColor(FColor(73, 73, 73))
		, _BackgroundColor(FLinearColor::Transparent)
		, _ForegroundColor(FSlateColor::UseForeground())
		, _HoverColor(FLinearColor::Transparent)
		{}

		SLATE_DEFAULT_SLOT(FArguments, Content)
		SLATE_ARGUMENT(EHorizontalAlignment, HAlign)
		SLATE_ARGUMENT(EVerticalAlignment, VAlign)
		SLATE_ARGUMENT(FMargin, Padding)
		SLATE_ARGUMENT(FMargin, BorderSize)
		SLATE_ARGUMENT(FLinearColor, BorderColor)
		SLATE_ARGUMENT(FLinearColor, BackgroundColor)
		SLATE_ARGUMENT(FSlateColor, ForegroundColor)
		SLATE_ARGUMENT(FLinearColor, HoverColor)


	SLATE_END_ARGS()
	
	SCustomBorder();
	void Construct(const SCustomBorder::FArguments& InArgs);

	void SetTileColor(FLinearColor Color);
	void SetBorderColor(FLinearColor Color);

	void OnHover();
	void OnReleaseHover();
	
private:
	
	FLinearColor BackgroundColor, HoverColor, BorderColor;
	FSlateColorBrush BackgroundImage;
	FImpSlateColorBorderBrush BorderImage;
	bool Hovered;

};
