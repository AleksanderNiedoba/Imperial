#include "ImperialEditorUtilities.h"

FImpSlateColorBorderBrush::FImpSlateColorBorderBrush(const FLinearColor& InColor, const FMargin& InMargin)
: FSlateBrush(ESlateBrushDrawType::Border, NAME_None, InMargin, ESlateBrushTileType::NoTile, ESlateBrushImageType::NoImage, FVector2D::ZeroVector, InColor)
{
}

// FImpSlateColorBorderBrush::FImpSlateColorBorderBrush(const FColor& InColor, const FMargin& InMargin)
// : FSlateBrush(ESlateBrushDrawType::Border, NAME_None, InMargin, ESlateBrushTileType::NoTile, ESlateBrushImageType::NoImage, FVector2D::ZeroVector, InColor)
// {
// 	
// }
