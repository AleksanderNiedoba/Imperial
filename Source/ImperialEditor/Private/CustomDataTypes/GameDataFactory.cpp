#include "CustomDataTypes/GameDataFactory.h"
#include "Data/GameDataAsset.h"
#include "ClassViewerFilter.h"
#include "Kismet2/SClassPickerDialog.h"

class FChildrenOfClassFilterViewer : public IClassViewerFilter
{
public:
	TSet<const UClass*> AllowedChildrenOfClasses;

	virtual bool IsClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const UClass* InClass, TSharedRef<FClassViewerFilterFuncs> InFilterFuncs) override
	{
		return InFilterFuncs->IfInChildOfClassesSet(AllowedChildrenOfClasses, InClass) != EFilterReturn::Failed;
	}

	virtual bool IsUnloadedClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const TSharedRef<const IUnloadedBlueprintData > InUnloadedClassData, TSharedRef< FClassViewerFilterFuncs > InFilterFuncs) override
	{
		return  InFilterFuncs->IfInChildOfClassesSet(AllowedChildrenOfClasses, InUnloadedClassData) != EFilterReturn::Failed;
	}
};

UGameDataFactory::UGameDataFactory(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	SupportedClass = UGameDataAsset::StaticClass(); 
	bCreateNew = true;
	bEditAfterNew = true;
}

bool UGameDataFactory::ConfigureProperties()
{
	static const FText TitleText = FText::FromString(TEXT("Select game data class:"));
	auto* ParentClass = UGameDataAsset::StaticClass();

	// Fill in options
	FClassViewerInitializationOptions Options;
	Options.Mode = EClassViewerMode::ClassPicker;
	Options.DisplayMode = EClassViewerDisplayMode::DefaultView;
	Options.bShowUnloadedBlueprints = true;
	Options.bExpandRootNodes = true;
	Options.NameTypeToDisplay = EClassViewerNameTypeToDisplay::Dynamic;
	const TSharedPtr<FChildrenOfClassFilterViewer> Filter = MakeShareable(new FChildrenOfClassFilterViewer);
	Filter->AllowedChildrenOfClasses.Add(ParentClass);
	Options.ClassFilters.Add(Filter.ToSharedRef());
	
	const bool bPressedOk = SClassPickerDialog::PickClass(TitleText, Options, SelectedClass, ParentClass);

	return bPressedOk;
}

UObject* UGameDataFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	if(!IsValid(SelectedClass))
	{
		return nullptr; 
	}
	
	UGameDataAsset* NewGridProfileAsset = NewObject<UGameDataAsset>(InParent, SelectedClass, InName, Flags | RF_Transactional);
	NewGridProfileAsset->OnNewAssetCreated(); 
	return NewGridProfileAsset; 
}
