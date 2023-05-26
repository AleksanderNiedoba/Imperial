#include "TabTools/GridMapCreatorComponents/ClickableHyperlinkMap.h"
#include "TabTools/GridMapCreatorComponents/TileOverlay.h"
#include "GameConfig/GameData.h"
#include "Widgets/Input/SButton.h"
#include "GameConfig/GridConfig.h"
#include "TabTools/GridMapCreatorComponents/MapTileOverlay.h"
#include "Grid/TileDefinitions.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Layout/SSpacer.h"

void ClickableHyperlinkMap::Construct(const FArguments& InArgs)
{
	OnTileSelected = InArgs._OnTileSelected;
	OnTileHovered = InArgs._OnTileHovered; 
	const auto* GC = UGridConfig::GetGridConfig();
	TSharedPtr<SVerticalBox> Container = SNew(SVerticalBox);
	
	
	for (int32 RowIndex = 0; RowIndex < GC->NumberOfRows; RowIndex++)
	{
		TSharedPtr<SHorizontalBox> RowContainer = SNew(SHorizontalBox);
		if(RowIndex % 2 != 0 )
		{
			RowContainer->AddSlot().AutoWidth()
			[
			SNew(SSpacer)
			.Size(FVector2D(7.f,14.f))
			];
		}
		for (int32 ColumnIndex = 0; ColumnIndex < GC->NumberOfColumns; ColumnIndex++)
		{
			TSharedPtr<MapTileOverlay> TileButton = SNew(MapTileOverlay)
			.IsEnabled(false)
			.ColorAndOpacity(FLinearColor(FColor(255, 255, 255)))
			.TileId(FIntPoint(ColumnIndex, RowIndex))
			.OnSelected(this, &ClickableHyperlinkMap::OnSelected)
			.OnHovered(this, &ClickableHyperlinkMap::OnHovered);
			RowContainer->AddSlot().AutoWidth()
			[
				SNew(SBox)
				.WidthOverride(14.f)
				.HeightOverride(14.f)
				[
					TileButton.ToSharedRef()
				]
			];

			ButtonsMap.Add(FIntPoint(ColumnIndex, RowIndex), TileButton.ToSharedRef()); 
		}
		Container->AddSlot().AutoHeight()[
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

void ClickableHyperlinkMap::InitWithProfile(UGridProfile* InGridProfile)
{
	if(!IsValid(InGridProfile))
	{
		Clear(); 
		return;
	}

	GridProfile = InGridProfile;
	RefreshButtonsState();
}

void ClickableHyperlinkMap::RefreshButtonsState()
{
	auto* TileDefinitions = UGameData::GetGameData()->GetTileDefinitions(); 
	for (const auto KV : GridProfile->GridMapProfile)
	{
		if (const auto TileButton = ButtonsMap.Find(KV.Key))
		{
			FTileDefinitionData TileDefinition; 
			if(TileDefinitions->GetTileDefinitionForType(KV.Value.TerrainType, TileDefinition))
			{
				const bool ShowIslandId = KV.Value.TerrainType != ETileTerrainType::Water;
				TileButton->Get().SetColorAndOpacity(FLinearColor(TileDefinition.TileMinimapColor));
				TileButton->Get().SetIslandId(KV.Value.IslandId); 
				TileButton->Get().SetShowIslandId(ShowIslandId); 
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
