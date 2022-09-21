#pragma once
#include "AssetTypeActions_Base.h"

class FGameDataAssetActions : public FAssetTypeActions_Base
{
public:
	FGameDataAssetActions(EAssetTypeCategories::Type InAssetCategory) : ImperialAssetCategory(InAssetCategory) {}
	
	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual uint32 GetCategories() override;

	virtual bool HasActions(const TArray<UObject*>& InObjects) const override { return false; }
	virtual bool CanFilter() override { return true; }

	private:
	EAssetTypeCategories::Type ImperialAssetCategory;


	
	virtual FString GetObjectDisplayName(UObject* Object) const override;
	virtual FText GetDisplayNameFromAssetData(const FAssetData& AssetData) const override;
};
