#pragma once

#include "AssetTypeCategories.h"
#include "IAssetTypeActions.h"
#include "IImperialModuleInterface.h"
#include "Framework/Docking/WorkspaceItem.h"
#include "Framework/MultiBox/MultiBoxExtender.h"
#include "Modules/ModuleManager.h"
#include "Toolkits/AssetEditorToolkit.h"


class FImperialEditorModule : public IImperialModuleInterface
{
	typedef FDefaultGameModuleImpl Super;

public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	virtual void AddModuleListeners() override;

	static inline FImperialEditorModule& Get()
	{
		return FModuleManager::LoadModuleChecked< FImperialEditorModule >("ImperialEditor");
	}
	
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("ImperialEditor");
	}
	
	void AddMenuExtension(const FMenuExtensionDelegate &ExtensionDelegate, FName ExtensionHook, const TSharedPtr<FUICommandList> &CommandList = nullptr, EExtensionHook::Position Position = EExtensionHook::Before);
	TSharedRef<FWorkspaceItem> GetMenuRoot() { return MenuRoot; };

protected:
	TSharedPtr<FExtensibilityManager> LevelEditorMenuExtensibilityManager;
	TSharedPtr<FExtender> MenuExtender;

	static TSharedRef<FWorkspaceItem> MenuRoot;

	void MakeListMenu(FMenuBarBuilder &MenuBuilder);
	void FillListMenu(FMenuBuilder &MenuBuilder);

};

