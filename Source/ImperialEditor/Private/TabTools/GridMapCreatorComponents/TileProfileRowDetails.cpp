#include "TabTools/GridMapCreatorComponents/TileProfileRowDetails.h"
#include "GameConfig/GameData.h"



void TileProfileRowDetails::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(SVerticalBox)
		+SVerticalBox::Slot()
		.VAlign(VAlign_Top)
		.AutoHeight()
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot()
			.VAlign(VAlign_Top)
			.AutoHeight()
			[
				SAssignNew(PathBorder, SBorder)
				.HAlign(HAlign_Left)
				.BorderImage(FEditorStyle::GetBrush("DetailsView.CategoryTop"))
				.Visibility(EVisibility::Collapsed)
				[
					SAssignNew(PathTextBlock, STextBlock)
					.Text(FText::FromString(""))
					.IsEnabled(false) 
				]
				
			]
			+SVerticalBox::Slot()
			.VAlign(VAlign_Top)
			.AutoHeight()
			.Padding(0.f, 10.f)
			[
				SAssignNew(IdsBox, SHorizontalBox)
				.Visibility(EVisibility::Collapsed)
				+SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(STextBlock)
					.Text(FText::FromString("Row: "))
					.IsEnabled(false)
				]
				+SHorizontalBox::Slot()
				.AutoWidth()
				[
					SAssignNew(RowIdTextBlock, STextBlock)
					.Text(FText::FromString(""))
					.IsEnabled(false)
				]
				+SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(20.f, 0.f)
				[
					SNew(STextBlock)
					.Text(FText::FromString("Column: "))
					.IsEnabled(false)
				]
				+SHorizontalBox::Slot()
				.AutoWidth()
				[
					SAssignNew(ColumnIdTextBlock, STextBlock)
					.Text(FText::FromString(""))
					.IsEnabled(false)
				]
			]
		]
	];
	
}

void TileProfileRowDetails::OnAssetLoaded(UGridProfile* InGridProfile)
{
	GridProfile = InGridProfile; 
	if(!IsValid(InGridProfile))
	{
		PathBorder->SetVisibility(EVisibility::Collapsed);
		IdsBox->SetVisibility(EVisibility::Collapsed); 
		return; 
	}
	
	const UPackage* Package = InGridProfile->GetOuter()->GetOutermost();
	PathTextBlock->SetText(FText::FromString(Package->GetPathName()));
	PathBorder->SetVisibility(EVisibility::HitTestInvisible); 
}

void TileProfileRowDetails::OnTileSelected(FIntPoint SelectedId)
{
	RowIdTextBlock->SetText(FText::AsNumber(SelectedId.X));
	ColumnIdTextBlock->SetText(FText::AsNumber(SelectedId.Y));
	IdsBox->SetVisibility(EVisibility::SelfHitTestInvisible); 
}
