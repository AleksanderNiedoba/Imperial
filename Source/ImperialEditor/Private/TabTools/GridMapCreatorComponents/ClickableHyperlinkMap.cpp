#include "TabTools/GridMapCreatorComponents/ClickableHyperlinkMap.h"
#include "TabTools/GridMapCreatorComponents/TileOverlay.h"
#include "GameConfig/GameData.h"
#include "Widgets/Input/SButton.h"
#include "GameConfig/GridConfig.h"
#include "TabTools/GridMapCreatorComponents/MapTileOverlay.h"
#include "Grid/TileDefinitions.h"
#include "Widgets/Layout/SScrollBox.h"

void ClickableHyperlinkMap::Construct(const FArguments& InArgs)
{
	OnTileSelected = InArgs._OnTileSelected;
	OnTileHovered = InArgs._OnTileHovered; 
	const auto* GC = UGridConfig::GetGridConfig();
	TSharedPtr<SVerticalBox> Container = SNew(SVerticalBox);
	
	for (int32 RowIndex = 0; RowIndex < GC->NumberOfRows; RowIndex++)
	{
		TSharedPtr<SHorizontalBox> RowContainer = SNew(SHorizontalBox);
		for (int32 ColumnIndex = 0; ColumnIndex < GC->NumberOfColumns; ColumnIndex++)
		{
			TSharedPtr<MapTileOverlay> TileButton = SNew(MapTileOverlay)
			.IsEnabled(false)
			.ColorAndOpacity(FLinearColor(FColor(255, 255, 255)))
			.TileId(FIntPoint(RowIndex, ColumnIndex))
			.OnSelected(this, &ClickableHyperlinkMap::OnSelected)
			.OnHovered(this, &ClickableHyperlinkMap::OnHovered);
			RowContainer->AddSlot()
			[
				SNew(SBox)
				.WidthOverride(15.f)
				.HeightOverride(15.f)
				[
					TileButton.ToSharedRef()
				]
			];

			ButtonsMap.Add(FIntPoint(RowIndex, ColumnIndex), TileButton.ToSharedRef()); 
		}
		Container->AddSlot()[
		RowContainer.ToSharedRef()]; 
	}

	ChildSlot
[
	SNew(SScrollBox)
	.Orientation(EOrientation::Orient_Vertical)
	+SScrollBox::Slot()[
		SNew(SScrollBox)
		.Orientation(EOrientation::Orient_Vertical)]
		+SScrollBox::Slot()
		[
			SNew(SBorder)
			.BorderBackgroundColor(FColor(192, 192, 192, 255))
	
			[
			Container.ToSharedRef()
			]
			
		]
];
}

void ClickableHyperlinkMap::InitWithProfile(UGridProfile* GridProfile)
{
	if(!IsValid(GridProfile))
	{
		Clear(); 
		return;
	}
	
	auto* TileDefinitions = UGameData::GetGameData()->GetTileDefinitions(); 
	for (const auto KV : GridProfile->GridMapProfile)
	{
		if (auto TileButton = ButtonsMap.Find(KV.Key))
		{
			FTileDefinitionData TileDefinition; 
			if(TileDefinitions->GetTileDefinitionForType(KV.Value.TerrainType, TileDefinition))
			{
				TileButton->Get().SetColorAndOpacity(FLinearColor(TileDefinition.TileMinimapColor));
				TileButton->Get().SetEnabled(true); 
			}
		}
	}
}

void ClickableHyperlinkMap::Clear()
{
	for (auto KV : ButtonsMap)
	{
		KV.Value->SetColorAndOpacity(FLinearColor(255, 255, 255));
		KV.Value->SetEnabled(false); 
	}
}

void ClickableHyperlinkMap::OnSelected(FIntPoint SelectedId)
{
	if(OnTileSelected.IsBound())
	{
		OnTileSelected.Execute(SelectedId);		
	}
}

void ClickableHyperlinkMap::OnHovered(FIntPoint SelectedId)
{
	if(OnTileHovered.IsBound())
	{
		OnTileHovered.Execute(SelectedId); 
	}
}

void ClickableHyperlinkMap::SetTileData(FIntPoint TileId, FTileDefinitionData TileDefinition)
{
	if(const auto Tile = ButtonsMap.Find(TileId))
	{
		Tile->Get().SetColorAndOpacity(TileDefinition.TileMinimapColor); 
	}
}
