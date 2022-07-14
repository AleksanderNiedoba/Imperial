#include "TabTools/GridMapCreatorComponents/TileOverlay.h"
#include "Widgets/SLeafWidget.h"
#include "Widgets/Images/SImage.h"
#include "ImperialEditor.h"
#include "SlateComponents/CustomBorder.h"

class STileOverlayHelper : public SLeafWidget
{
public:
	SLATE_BEGIN_ARGS(STileOverlayHelper)
	{}
	SLATE_EVENT(FPointerEventHandler, OnMouseButtonDown)
SLATE_END_ARGS()
void Construct(const FArguments& InArgs)
	{
		OnMouseButtonDownHandler = InArgs._OnMouseButtonDown;
	}
	
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override
	{
		return ++LayerId;
	}
	virtual FVector2D ComputeDesiredSize(float) const override
	{
		return FVector2D(1.0f);
	}
	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override
	{
		if (OnMouseButtonDownHandler.IsBound())
		{
			return OnMouseButtonDownHandler.Execute(MyGeometry, MouseEvent);
		}
		return FReply::Unhandled();
	}
protected:
	virtual FCursorReply OnCursorQuery(const FGeometry&, const FPointerEvent&) const override
	{
		return FCursorReply::Cursor(EMouseCursor::Hand);
	}
private:
	FPointerEventHandler OnMouseButtonDownHandler;
};

void TileOverlay::Construct(const FArguments& InArgs)
{
	SelectedColor = InArgs._SelectedColor; 
	SOverlay::Construct(SOverlay::FArguments()
	+SOverlay::Slot()
		[
			SAssignNew(TileColorBorder, SCustomBorder)
			.BorderSize(FMargin(0.6f))
			.BackgroundColor(InArgs._ColorAndOpacity)
			.BorderColor(FLinearColor::Black)
			.HoverColor(FLinearColor(255, 255, 255))
		]
		+SOverlay::Slot()
		[
			SNew(STileOverlayHelper)
			.OnMouseButtonDown_Lambda([=](const FGeometry&, const FPointerEvent& MouseEvent) -> FReply
				{
				if (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton || MouseEvent.IsTouchEvent())
				{
					Navigate();
					return FReply::Handled();
				}
				return FReply::Unhandled();
				})
		]);
}

void TileOverlay::Navigate()
{
}

void TileOverlay::SetColorAndOpacity(FLinearColor Color)
{
	TileColorBorder->SetTileColor(Color);
	
}

void TileOverlay::SetSelected(bool NewSelected)
{
	bIsSelected = NewSelected;
	const FLinearColor Color = NewSelected ? SelectedColor : FLinearColor(0, 0, 0); 
	TileColorBorder->SetBorderColor(Color); 
}

void TileOverlay::OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	SOverlay::OnMouseEnter(MyGeometry, MouseEvent);
	if(!IsSelected())
	{
		TileColorBorder->OnHover();
	}
}

void TileOverlay::OnMouseLeave(const FPointerEvent& MouseEvent)
{
	SOverlay::OnMouseLeave(MouseEvent);

	if(!IsSelected())
	{
		TileColorBorder->OnReleaseHover();
	}
}
