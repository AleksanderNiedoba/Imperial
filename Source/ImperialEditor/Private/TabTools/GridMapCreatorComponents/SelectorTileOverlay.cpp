#include "TabTools/GridMapCreatorComponents/SelectorTileOverlay.h"
#include "Widgets/Images/SImage.h"

void SelectorTileOverlay::Construct(const FArguments& InArgs)
{
	TileOverlay::Construct(TileOverlay::FArguments()
		.SelectedColor(InArgs._SelectedColor)
		);
	SetColorAndOpacity(InArgs._TileDefinition.TileMinimapColor);
	SetToolTipText(InArgs._TileDefinition.TileName); 
	TerrainType = InArgs._TerrainType;
	TileDefinitionData = InArgs._TileDefinition; 
	SetOnSelect(InArgs._OnSelected);
	SetOnHover(InArgs._OnHovered); 
}

void SelectorTileOverlay::SetOnSelect(FOnTileEvent EventHandler)
{
	OnSelect = EventHandler;
}

void SelectorTileOverlay::SetOnHover(FOnTileEvent EventHandler)
{
	OnHover = EventHandler; 
}

void SelectorTileOverlay::OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	TileOverlay::OnMouseEnter(MyGeometry, MouseEvent);
	if (OnHover.IsBound())
	{
		OnHover.Execute(TerrainType, TileDefinitionData);
	}
}

void SelectorTileOverlay::OnMouseLeave(const FPointerEvent& MouseEvent)
{
	TileOverlay::OnMouseLeave(MouseEvent);
}

void SelectorTileOverlay::Navigate()
{
	if (OnSelect.IsBound())
	{
		OnSelect.Execute(TerrainType, TileDefinitionData);
	}
}



