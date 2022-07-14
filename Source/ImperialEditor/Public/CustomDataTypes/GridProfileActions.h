#pragma once
#include "AssetTypeActions_Base.h"

class FGridProfileAssetActions : public FAssetTypeActions_Base
{
public:
	FGridProfileAssetActions(EAssetTypeCategories::Type InAssetCategory);
	
	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual uint32 GetCategories() override;

	private:
	EAssetTypeCategories::Type ImperialAssetCategory;
};