#include "TabTools/GridMapCreatorComponents/GridMapCreatorPanel.h"
#include "TabTools/GridMapCreatorComponents/TileProfileSelector.h"
#include "TabTools/GridMapCreatorComponents/TileProfileRowDetails.h"
#include "TabTools/GridMapCreatorComponents/ClickableHyperlinkMap.h"
#include "TabTools/GridMapCreatorComponents/TerrainSelector.h"
#include "Widgets/Input/SButton.h"
#include "Grid/GridProfile.h"
#include "Grid/GridData.h"
#include "Systems/GridSystem.h"
#include "TabTools/GridMapCreator.h"
#include "Widgets/Layout/SScrollBox.h"


void GridMapCreatorPanel::Construct(const FArguments& InArgs)
{
	GridMapCreator = InArgs._Tool;
	if(!GridMapCreator.IsValid())
	{
		return; 
	}
	
	SAssignNew(ProfileRowDetails, TileProfileRowDetails);
	
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
							ProfileRowDetails.ToSharedRef()
						]
						+SVerticalBox::Slot().AutoHeight()
						.Padding(10.f, 10.f)
						[
							SNew(TerrainSelector)
							.OnSelected(this, &GridMapCreatorPanel::OnTerrainTypeSelected)
						]
						+SVerticalBox::Slot()
						.AutoHeight()
						.Padding(10.f, 10.f)
						[
							SNew(SHorizontalBox)
							+SHorizontalBox::Slot()
							.FillWidth(.2f)
							[
								SAssignNew(SeedSpinBox, SSpinBox<int32>)
								.MinValue(-1)
								.MaxValue(20000)
								.Value(- 1)
							]
							+SHorizontalBox::Slot()
							.Padding(10.f, 0.f, 0.f, 0.f)
							.FillWidth(1.0f)
							[
								SAssignNew(SeedTextBox, STextBlock)
							]
						]
						+SVerticalBox::Slot().AutoHeight()
						.Padding(10.f, 10.f)
						[
							SNew(SButton)
							.Text(FText::FromString("GenerateRandom"))
							.OnClicked(this, &GridMapCreatorPanel::OnRandomMapButtonClicked)
						]
					]
				]
			]
		]
	];

	SetSeedTextValue(-1); 
}

void GridMapCreatorPanel::OnAssetLoaded(UGridProfile* InGridProfile)
{
	GridProfile = InGridProfile;
	ClickableMap->InitWithProfile(InGridProfile);
	ProfileRowDetails->OnAssetLoaded(InGridProfile);

	if(IsValid(InGridProfile))
	{
		SetSeedTextValue(InGridProfile->GridGenerationSeed); 
	}
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

FReply GridMapCreatorPanel::OnRandomMapButtonClicked()
{
	if(!IsValid(GridProfile))
	{
		return FReply::Handled(); 
	}
	
	UGridSystem* GS = UGridSystem::CreateNew();
	const int32 GeneratedMapSeed = GS->GetGridMapGenerator()->GenerateMap(GridProfile, SeedSpinBox->GetValue());
	SetSeedTextValue(GeneratedMapSeed); 
	ClickableMap->RefreshButtonsState(); 
	return FReply::Handled(); 
}

void GridMapCreatorPanel::SetSeedTextValue(int32 InSeed)
{
	const FString SeedString = "Generation seed: " + FString::FromInt(InSeed); 
	SeedTextBox->SetText(FText::FromString(SeedString)); 
}