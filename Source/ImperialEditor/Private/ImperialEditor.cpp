#include "ImperialEditor.h"
#include "Modules/ModuleManager.h"
#include "LevelEditor.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "TabTools/GridMapCreator.h"

IMPLEMENT_GAME_MODULE(FImperialEditorModule, ImperialEditor);

TSharedRef<FWorkspaceItem> FImperialEditorModule::MenuRoot = FWorkspaceItem::NewGroup(FText::FromString("Menu Root"));

void FImperialEditorModule::AddModuleListeners()
{
	ModuleListeners.Add(MakeShareable(new GridMapCreator)); 
}

void FImperialEditorModule::StartupModule()
{
	if (!IsRunningCommandlet())
	{
		FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
		LevelEditorMenuExtensibilityManager = LevelEditorModule.GetMenuExtensibilityManager(); 
		MenuExtender = MakeShareable(new FExtender);
		MenuExtender->AddMenuBarExtension("Window", EExtensionHook::After, nullptr, FMenuBarExtensionDelegate::CreateRaw(this, &FImperialEditorModule::MakeListMenu));
		LevelEditorMenuExtensibilityManager->AddExtender(MenuExtender); 
	}
	
	IImperialModuleInterface::StartupModule();
}

void FImperialEditorModule::ShutdownModule()
{
	IImperialModuleInterface::ShutdownModule();
}



void FImperialEditorModule::AddMenuExtension(const FMenuExtensionDelegate& ExtensionDelegate, FName ExtensionHook, const TSharedPtr<FUICommandList>& CommandList, EExtensionHook::Position Position)
{
	MenuExtender->AddMenuExtension(ExtensionHook, Position, CommandList, ExtensionDelegate);
}

void FImperialEditorModule::MakeListMenu(FMenuBarBuilder& MenuBuilder)
{
	MenuBuilder.AddPullDownMenu(
		FText::FromString("Imperial"),
		FText::FromString("Open custom imperial tools tab"),
		FNewMenuDelegate::CreateRaw(this, &FImperialEditorModule::FillListMenu),
		"Imperial",
		FName(TEXT("Imperial Tools")));
}

void FImperialEditorModule::FillListMenu(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.BeginSection("ImperialSection", FText::FromString("Grid Tools"));
	MenuBuilder.AddMenuSeparator(FName("Grid_Tools"));
	MenuBuilder.EndSection();
}


