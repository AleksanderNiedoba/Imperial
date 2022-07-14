#include "TabTools/GridMapCreatorComponents/TileProfileSelector.h"
#include "AssetThumbnail.h"
#include "FileHelpers.h"
#include "PropertyCustomizationHelpers.h"
#include "SAssetDropTarget.h"
#include "GameConfig/GameData.h"
#include "Widgets/Input/SButton.h"


void TileProfileSelector::Construct(const FArguments& InArgs)
{
	NumOfPools = InArgs._NumOfPools;
	ThumbnailsAllowed = InArgs._InAreRealTimeThumbnailsAllowed;
	CenterThumbnail = InArgs._ShouldCenterThumbnail;
	OnLoadClicked = InArgs._OnLoadClicked; 
	
	TSharedPtr<SVerticalBox> Container = SNew(SVerticalBox);
	ThumbnailPool = MakeShareable(new FAssetThumbnailPool(NumOfPools, ThumbnailsAllowed));
	AssetThumbnail = MakeShareable( new FAssetThumbnail( GridProfile, 50, 50, ThumbnailPool ) );

	TSharedRef<SWidget> AssetWidget =
			SNew( SAssetDropTarget )
			//.ToolTipText( this, &SDialogueVoicePropertyEditor::OnGetToolTip )
			//.OnIsAssetAcceptableForDrop( this, &SDialogueVoicePropertyEditor::OnIsAssetAcceptableForDrop )
			//.OnAssetDropped( this, &SDialogueVoicePropertyEditor::OnAssetDropped )
			[
				SNew( SBox )
				.WidthOverride(50) 
				.HeightOverride(50)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.Padding(0.0f)
				[
					AssetThumbnail->MakeThumbnailWidget()
				]
			];
	
	ChildSlot
	[
		
		
		SNew(SBorder)
				.Padding(FMargin(10.f, 0.f))
				.BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder"))
				.VAlign(VAlign_Top)
				[
					SNew(SHorizontalBox)
					+SHorizontalBox::Slot()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					.AutoWidth()
					.Padding(10.f, 0.f)
					[
						SNew(STextBlock)
						.Text(FText::FromString("Select asset:"))
					]
					+SHorizontalBox::Slot()
					.AutoWidth()
					.Padding(10.f)
					.VAlign(VAlign_Top)
					[
						SNew( SBox )
						.HAlign(HAlign_Center)
						.VAlign(VAlign_Center)
						[
							SAssignNew(ComboButton, SComboButton)
							.ButtonStyle( FEditorStyle::Get(), "PropertyEditor.AssetComboStyle" )
							.ForegroundColor(FEditorStyle::GetColor("PropertyEditor.AssetName.ColorAndOpacity"))
							.OnGetMenuContent( this, &TileProfileSelector::OnGetMenuContent )
							.ButtonContent()
							[
								AssetWidget
							]
						]
					]
					+SHorizontalBox::Slot()
					.FillWidth(1.f)
					[
						SNew( SBox )
						.HAlign(HAlign_Center)
						.VAlign(VAlign_Center)
						[
						SNew(SHorizontalBox)
						+SHorizontalBox::Slot()
						.AutoWidth()
						.Padding(5.f, 0.f)
						[
							SNew(SButton)
							.Text(FText::FromString("Save"))
							.OnClicked_Lambda([=]
							{
								FEditorFileUtils::SaveDirtyPackages(true, false, true, false, false, false);
								return FReply::Handled();
							})
						]
						+SHorizontalBox::Slot()
						.AutoWidth()
						.Padding(5.f, 0.f)
						[
							SNew(SButton)
							.Text(FText::FromString("Load"))
							.OnClicked_Lambda([=] { OnLoadClicked.Execute(GridProfile); return FReply::Handled();})
						]
						+SHorizontalBox::Slot()
						.AutoWidth()
						.Padding(5.f, 0.f)
						[
							SNew(SButton)
							.Text(FText::FromString("Clear"))
							.OnClicked_Lambda([=]
							{
								AssetThumbnail->SetAsset(nullptr); 
								OnLoadClicked.Execute(nullptr);
								return FReply::Handled();
							})
						]
					
					]
					]
				]
		
		
		
	];
}

TSharedRef<SWidget> TileProfileSelector::OnGetMenuContent()
{
	TArray<const UClass*> AllowedClasses;
	AllowedClasses.Add(UGridProfile::StaticClass());

	UGridProfile* DialogueVoice = NULL;
	{
		UObject* Object = NULL;
		//DialogueVoicePropertyHandle->GetValue(Object);
		//DialogueVoice = Cast<UDialogueVoice>(Object);
	}

	return PropertyCustomizationHelpers::MakeAssetPickerWithMenu(
		DialogueVoice,
		false,
		AllowedClasses,
		PropertyCustomizationHelpers::GetNewAssetFactoriesForClasses(AllowedClasses),
		OnShouldFilterAsset,
		FOnAssetSelected::CreateSP(this, &TileProfileSelector::OnAssetSelectedFromPicker),
		FSimpleDelegate::CreateSP(this, &TileProfileSelector::CloseMenu));
}

void TileProfileSelector::OnAssetSelectedFromPicker(const FAssetData& InAssetData)
{
	AssetThumbnail->SetAsset(InAssetData);
	GridProfile = Cast<UGridProfile>(InAssetData.GetAsset()); 
}

void TileProfileSelector::CloseMenu()
{
	ComboButton->SetIsOpen(false);
}

