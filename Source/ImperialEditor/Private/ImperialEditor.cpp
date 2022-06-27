// Copyright 2016, Flying Wild Hog sp. z o.o.
#include "ImperialEditor.h"
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "Editor.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Modules/ModuleManager.h"
#include "Editor/UnrealEdEngine.h"
#include "Animation\AnimSequence.h"
#include "IAssetTools.h"


	
class FImperialEditorModuleImpl : public IImperialEditorModule
{
	typedef FDefaultGameModuleImpl Super;

public:
	/**
	* Called right after the module DLL has been loaded and the module object has been created
	*/
	virtual void StartupModule() override;

	/**
	* Called before the module is unloaded, right before the module object is destroyed.
	*/
	virtual void ShutdownModule() override;
	virtual uint32 GetGameDataAssetCategory() const override;
	virtual bool IsGameModule() const override;

private:
	
	EAssetTypeCategories::Type GameDataAssetCategoryBit;
	// All registered asset type actions. Cached here so that we can unregister them during shutdown.
	TArray<TSharedPtr<IAssetTypeActions>> RegisteredAssetTypeActions;
};

IMPLEMENT_GAME_MODULE(FImperialEditorModuleImpl, ImperialEditor);
#define LOCTEXT_NAMESPACE "ImperialEditor"


void FImperialEditorModuleImpl::StartupModule()
{
	IImperialEditorModule::StartupModule();
	UE_LOG(LogTemp, Warning, TEXT("It Works!!!"));
}

void FImperialEditorModuleImpl::ShutdownModule()
{
	IImperialEditorModule::ShutdownModule();
}

uint32 FImperialEditorModuleImpl::GetGameDataAssetCategory() const
{
	return GameDataAssetCategoryBit;
}

bool FImperialEditorModuleImpl::IsGameModule() const
{
	return true;
}

