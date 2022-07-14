#include "CustomDataTypes/GridProfileFactory.h"
#include "Grid/GridProfile.h"

UGridProfileFactory::UGridProfileFactory(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	SupportedClass = UGridProfile::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UGridProfileFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	UGridProfile* NewGridProfileAsset = NewObject<UGridProfile>(InParent, InClass, InName, Flags | RF_Transactional);
	NewGridProfileAsset->OnProfileCreated(); 
	return NewGridProfileAsset; 
}
