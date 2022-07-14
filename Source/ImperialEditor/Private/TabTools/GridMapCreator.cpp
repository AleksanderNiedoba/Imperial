#include "TabTools/GridMapCreator.h"

#include "GameConfig/GridConfig.h"
#include "TabTools/GridMapCreatorComponents/GridMapCreatorPanel.h"

void GridMapCreator::OnStartupModule()
{
	FTabToolBase::OnStartupModule();
    FImperialEditorModule::Get().AddMenuExtension(FMenuExtensionDelegate::CreateRaw(this, &GridMapCreator::MakeMenuEntry), FName("Grid_Tools"));
}

void GridMapCreator::OnShutdownModule()
{
	FTabToolBase::OnShutdownModule();
}

void GridMapCreator::Initialize()
{
	TabName = "GridTools";
	TabDisplayName = FText::FromString("Grid map creator");
	ToolTipText = FText::FromString("Grid map creator window"); 
}

TSharedRef<SDockTab> GridMapCreator::SpawnTab(const FSpawnTabArgs& TabSpawnArgs)
{
	TSharedRef<SDockTab> SpawnedTab = SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(GridMapCreatorPanel)
			.Tool(SharedThis(this))
		];

	return SpawnedTab;
}
