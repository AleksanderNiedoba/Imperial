#include "TabTools/GridMapCreatorComponents/GridMapCreatorPanel.h"
#include "TabTools/GridMapCreatorComponents/TileProfileSelector.h"
#include "TabTools/GridMapCreatorComponents/TileProfileRowDetails.h"
#include "TabTools/GridMapCreatorComponents/ClickableHyperlinkMap.h"
#include "TabTools/GridMapCreatorComponents/TerrainSelector.h"
#include "Grid/GridProfile.h"
#include "Grid/GridData.h"
#include "TabTools/GridMapCreator.h"
#include "Widgets/Layout/SScrollBox.h"


void GridMapCreatorPanel::Construct(const FArguments& InArgs)
{
	GridMapCreator = InArgs._Tool;
	if(!GridMapCreator.IsValid())
	{
		return; 
	}
	
	ChildSlot
	[
		SNew(SScrollBox)
		+ SScrollBox::Slot()
		.VAlign(VAlign_Top)
		.Padding(5)
		[
			SNew(SBorder)
			.BorderBackgroundColor(FColor(192, 192, 192, 255))
			.Padding(0.f)
			[
				SNew(SVerticalBox)
				+SVerticalBox::Slot().AutoHeight()
				[
					SNew(SHorizontalBox)
					+SHorizontalBox::Slot().AutoWidth()
					[
						SAssignNew(ClickableMap, ClickableHyperlinkMap)
						.OnTileSelected(this, &GridMapCreatorPanel::OnTileSelected)
						.OnTileHovered(ProfileRowDetails.ToSharedRef(), &TileProfileRowDetails::OnTileSelected)
						
					]
					+SHorizontalBox::Slot().FillWidth(1.f)
					[
						SNew(SVerticalBox)
						+SVerticalBox::Slot().AutoHeight()
						.Padding(10.f, 10.f)
						[
							SNew(TileProfileSelector)
							.NumOfPools(12)
							.ShouldCenterThumbnail(true)
							.InAreRealTimeThumbnailsAllowed(true)
							.OnLoadClicked(this, &GridMapCreatorPanel::OnAssetLoaded)
						]
						+SVerticalBox::Slot().AutoHeight()
						.Padding(10.f, 10.f)
						[
							SAssignNew(ProfileRowDetails, TileProfileRowDetails)
						]
						+SVerticalBox::Slot().AutoHeight()
						.Padding(10.f, 10.f)
						[
							SNew(TerrainSelector)
							.OnSelected(this, &GridMapCreatorPanel::OnTerrainTypeSelected)
						]
					]
				]
			]
		]
	];
}

void GridMapCreatorPanel::OnAssetLoaded(UGridProfile* InGridProfile)
{
	GridProfile = InGridProfile;
	ClickableMap->InitWithProfile(InGridProfile);
	ProfileRowDetails->OnAssetLoaded(InGridProfile); 
}

void GridMapCreatorPanel::OnTileSelected(FIntPoint TileId)
{
	switch (CurrentTool)
	{
	case EGridMapCreatorTool::None:
		{
			break; 
		}
	case EGridMapCreatorTool::Terrain:
		{
			if(auto* ProfileTileData = GridProfile->GridMapProfile.Find(TileId))
			{
				ProfileTileData->TerrainType = CurrentTileData;
				ClickableMap->SetTileData(TileId, TileDefinitionData); 
				UPackage* Package = GridProfile->GetOuter()->GetOutermost();
				Package->SetDirtyFlag(true); 
			}
		}
		default: break; 
	}
}

void GridMapCreatorPanel::OnTerrainTypeSelected(ETileTerrainType NewTerrainData, FTileDefinitionData NewTileDefinition)
{
	CurrentTool = Terrain;
	CurrentTileData = NewTerrainData;
	TileDefinitionData = NewTileDefinition; 
}