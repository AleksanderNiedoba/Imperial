#include "CustomDataTypes/GridProfileActions.h"

#include "Grid/GridProfile.h"

FGridProfileAssetActions::FGridProfileAssetActions(EAssetTypeCategories::Type InAssetCategory) : ImperialAssetCategory(InAssetCategory)
{
}

FText FGridProfileAssetActions::GetName() const
{
	return FText::FromString("GridProfile"); 
}

FColor FGridProfileAssetActions::GetTypeColor() const
{
	return FColor(222, 189, 27);
}

UClass* FGridProfileAssetActions::GetSupportedClass() const
{
	return UGridProfile::StaticClass(); 
}

uint32 FGridProfileAssetActions::GetCategories()
{
	return ImperialAssetCategory; 
}


