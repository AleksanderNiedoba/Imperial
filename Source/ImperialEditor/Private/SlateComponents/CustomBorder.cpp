#include "SlateComponents/CustomBorder.h"


SCustomBorder::SCustomBorder()
	: BackgroundImage(FLinearColor::Transparent)
	, BorderImage(FColor(73, 73, 73))
{
}

void SCustomBorder::Construct(const SCustomBorder::FArguments& InArgs)
{
	BackgroundColor = InArgs._BackgroundColor;
	HoverColor = InArgs._HoverColor;
	BorderColor = InArgs._BorderColor;
	
	BackgroundImage = FSlateColorBrush(InArgs._BackgroundColor);
	BorderImage = FImpSlateColorBorderBrush(InArgs._BorderColor, InArgs._BorderSize);
	Hovered = false;
	SBorder::Construct(SBorder::FArguments()
		.BorderImage(&BorderImage)
		.Padding(InArgs._BorderSize)
		[
			SNew(SBorder)
			.BorderImage(&BackgroundImage)
			.HAlign(InArgs._HAlign)
			.VAlign(InArgs._VAlign)
			.Padding(InArgs._Padding)
			.ForegroundColor(InArgs._ForegroundColor)
			[
				InArgs._Content.Widget
			]
		]);
}

void SCustomBorder::SetTileColor(FLinearColor Color)
{
	BackgroundColor = Color; 
	BackgroundImage.TintColor= FSlateColor(Color); 
}

void SCustomBorder::SetBorderColor(FLinearColor Color)
{
	BorderImage.TintColor = FSlateColor(Color); 
}

void SCustomBorder::OnHover()
{
	BorderImage.TintColor = FSlateColor(HoverColor); 
}

void SCustomBorder::OnReleaseHover()
{
	BorderImage.TintColor = FSlateColor(BorderColor); 
}

