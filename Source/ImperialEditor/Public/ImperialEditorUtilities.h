#pragma once

#include "Styling/SlateBrush.h"
#include "Engine/Blueprint.h"

/**
 * Provides a slate brush that constructs a colored border.
 */
class IMPERIALEDITOR_API FImpSlateColorBorderBrush : public FSlateBrush
{
public:
	// Create a slate colored border brush with the given linear color and margins
	FImpSlateColorBorderBrush(const FLinearColor& InColor, const FMargin& InMargin = FMargin(0.0f));
	// Create a slate colored border brush with the given sRGB color and margins
	//FImpSlateColorBorderBrush(const FColor& InColor, const FMargin& InMargin = FMargin(0.0f));
};




