#include "TabTools/GridMapCreatorComponents/TerrainSelector.h"
#include "TabTools/GridMapCreatorComponents/SelectorTileOverlay.h"
#include "GameConfig/GridConfig.h"
#include "Grid/TileDefinitions.h"

void TerrainSelector::Construct(const FArguments& InArgs)
{
	auto* TileDefinitions = UTileDefinitions::GetTileDefinitions();

	TSharedPtr<SHorizontalBox> SlotsBox = SNew(SHorizontalBox); 
	for(auto KV : TileDefinitions->GridDefinitions)
	{
		TSharedPtr<SelectorTileOverlay> Tile = SNew(SelectorTileOverlay)
		.TileDefinition(KV.Value)
		.TerrainType(KV.Key)
		.SelectedColor(FLinearColor(255, 255, 0))
		.OnSelected(this, &TerrainSelector::OnTileSelected); 

		Tiles.Add(Tile);
		SlotsBox->AddSlot()
		.Padding(2.f)
		[
			SNew(SBox)
			.WidthOverride(17.f)
			.HeightOverride(17.f)
			[
				Tile.ToSharedRef()
			]
		];
	}

	ChildSlot
	[
		SNew(SVerticalBox)
		+SVerticalBox::Slot()
		[
			SNew(SBox)
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(FText::FromString("Terrain selector"))
			]
		]
		+SVerticalBox::Slot()
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Center)
		.AutoHeight()
		.Padding(0.f,10.f)
		[
			SlotsBox.ToSharedRef() 
		]
		
	];
	
	SetOnSelected(InArgs._OnSelected); 
}

void TerrainSelector::OnTileSelected(ETileTerrainType TerrainType, FTileDefinitionData TileDefinitionData)
{
	for (auto Tile : Tiles)
	{
		Tile->SetSelected(Tile->GetTileDefinition() == TerrainType); 
	}

	if(OnTerrainSelected.IsBound())
	{
		OnTerrainSelected.Execute(TerrainType, TileDefinitionData); 
	}
}

void TerrainSelector::SetOnSelected(FOnItemSelected EventHandler)
{
	OnTerrainSelected = EventHandler; 
}
