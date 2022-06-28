#pragma once

#include "IImperialModuleInterface.h"
#include "ImperialEditor.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Widgets/Docking/SDockTab.h"

class FTabToolBase : public IImperialModuleListenerInterface, public TSharedFromThis< FTabToolBase >
{
public:
	virtual ~FTabToolBase() {}  
	virtual void OnStartupModule() override
	{
		Initialize();
		FGlobalTabmanager::Get()->RegisterNomadTabSpawner(TabName, FOnSpawnTab::CreateRaw(this, &FTabToolBase::SpawnTab))
			.SetGroup(FImperialEditorModule::Get().GetMenuRoot())
			.SetDisplayName(TabDisplayName)
			.SetTooltipText(ToolTipText);
	};

	virtual void OnShutdownModule() override
	{
		FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(TabName);
	};
	
	virtual void Initialize() {};
	virtual TSharedRef<SDockTab> SpawnTab(const FSpawnTabArgs& TabSpawnArgs) { return SNew(SDockTab); };

	virtual void MakeMenuEntry(FMenuBuilder &MenuBuilder)
	{
		FGlobalTabmanager::Get()->PopulateTabSpawnerMenu(MenuBuilder, TabName);
	};

protected:
	FName TabName;
	FText TabDisplayName;
	FText ToolTipText;
};