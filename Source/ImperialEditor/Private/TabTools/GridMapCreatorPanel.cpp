#include "TabTools/GridMapCreatorPanel.h"

#include "GameConfig/GridConfig.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Layout/SScrollBox.h"


void GridMapCreatorPanel::Construct(const FArguments& InArgs)
{
	GridMapCreator = InArgs._Tool;
	if(GridMapCreator.IsValid())
	{
		
		// Do stuff 
	}

	TSharedPtr<SVerticalBox> Container = SNew(SVerticalBox);
	const auto* GC = UGridConfig::GetGridConfig();
	const FLinearColor WaterColor = GC->WaterColor; 
		
	for (int RowIndex = 0; RowIndex < GC->NumberOfRows; RowIndex++)
	{
		TSharedPtr<SHorizontalBox> RowContainer = SNew(SHorizontalBox);
		for (int i = 0; i < GC->NumberOfColumns; i++)
		{
			RowContainer->AddSlot()[
			SNew(SBox)
			.WidthOverride(10.f)
			.HeightOverride(10.f)
			
			[
			SNew(SButton)
	.ButtonColorAndOpacity(FSlateColor(WaterColor))
	.ContentPadding(FVector2D(.5f, .5f))
	]
			];
		}
		Container->AddSlot()[
		RowContainer.ToSharedRef()]; 
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
			.Padding(15.0f)
			[
				SNew(SVerticalBox)
				+SVerticalBox::Slot().AutoHeight()
				[
					SNew(SHorizontalBox)
					+SHorizontalBox::Slot().FillWidth(.5f)
					[
						Container.ToSharedRef()
					]
					+SHorizontalBox::Slot().FillWidth(.5f)
					[
						SNew(STextBlock)
						.Text(FText::FromString("Here there will be data asset displayer"))
						]
				]
				
			]
		]					
	];
}
