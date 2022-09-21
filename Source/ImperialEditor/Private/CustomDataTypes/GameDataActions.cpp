#include "CustomDataTypes/GameDataActions.h"
#include "Data/GameDataAsset.h"

FText FGameDataAssetActions::GetName() const
{
	return FText::FromString("GameData"); 
}

FColor FGameDataAssetActions::GetTypeColor() const
{
	return FColor(3, 235, 165);
}

UClass* FGameDataAssetActions::GetSupportedClass() const
{
	return UGameDataAsset::StaticClass(); 
}

uint32 FGameDataAssetActions::GetCategories()
{
	return ImperialAssetCategory; 
}

FString FGameDataAssetActions::GetObjectDisplayName(UObject* Object) const
{
	auto Name = Object->GetClass()->GetName();
	Name.RemoveFromStart(TEXT("GD"));
	Name.RemoveFromEnd(TEXT("DataAsset"));
	return Name;
}

FText FGameDataAssetActions::GetDisplayNameFromAssetData(const FAssetData& AssetData) const
{

	auto Name = AssetData.AssetClass.ToString(); 
	Name.RemoveFromStart(TEXT("GD"));
	Name.RemoveFromEnd(TEXT("DataAsset"));
	return FText::FromString(Name);
}


