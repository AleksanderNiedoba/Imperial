#include "TabTools/GridMapCreatorComponents/MapTileOverlay.h"
#include "Widgets/Images/SImage.h"
#include "ImperialEditor.h"
#include "SlateComponents/CustomBorder.h"

void MapTileOverlay::Construct(const FArguments& InArgs)
{
	TileOverlay::Construct(TileOverlay::FArguments()
		);

	TileId = InArgs._TileId;
	SetOnSelect(InArgs._OnSelected);
	SetOnHover(InArgs._OnHovered); 
}

void MapTileOverlay::SetOnSelect(FOnTileEvent EventHandler)
{
	OnSelect = EventHandler;
}

void MapTileOverlay::SetOnHover(FOnTileEvent EventHandler)
{
	OnHover = EventHandler; 
}

void MapTileOverlay::OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	TileOverlay::OnMouseEnter(MyGeometry, MouseEvent);
	if (OnHover.IsBound())
	{
		OnHover.Execute(TileId);
	}
}

void MapTileOverlay::OnMouseLeave(const FPointerEvent& MouseEvent)
{
	TileOverlay::OnMouseLeave(MouseEvent);
}

void MapTileOverlay::Navigate()
{
	if (OnSelect.IsBound())
	{
		OnSelect.Execute(TileId);
	}
}



