#pragma once

#include "CoreMinimal.h"
#include "GameConfig/GameDataTables.h"
#include "GameDataAsset.generated.h"

#define IMPLEMENT_NEWASSETCREATED(_Type) \
	IMPLEMENT_NEWASSETCREATED_WITHID_WITHOP(_Type, Id, [](decltype(Id) A) { return A+1;})


#define IMPLEMENT_NEWASSETCREATED_WITHID_WITHOP(_Type, _Id, _OP) \
void UGD##_Type##DataAsset::OnNewAssetCreated() \
{ \
	auto* GameData = UGameData::GetGameData(); \
	if (GameData->_Type##Table->_Type##Definitions.Contains(this)) \
	{ \
		return; \
	} \
	decltype(_Id) MaxId = -1; \
	for (TSoftObjectPtr<UGameDataAsset>& _Type##Def : GameData->_Type##Table->_Type##Definitions) \
	{ \
		if (!_Type##Def.IsNull() && _Type##Def.LoadSynchronous()) \
		{ \
			MaxId = FMath::Max(Cast<UGD##_Type##DataAsset>(_Type##Def.LoadSynchronous())->_Id, MaxId); \
		} \
	} \
	_Id = _OP(MaxId); \
	GameData->_Type##Table->_Type##Definitions.Add(this); \
	GameData->_Type##Cache.Add(this); \
	GameData->_Type##Table->MarkPackageDirty(); \
	MarkPackageDirty(); \
}

UCLASS()
class IMPERIAL_API UGameDataAsset : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
	int32 Id = -1; 


	UFUNCTION(BlueprintPure)
	virtual FText GetGameDataName() { return FText::FromString(""); }
	UFUNCTION(BlueprintPure)
	virtual FText GetGameDataDescription() { return FText::FromString(""); }
	UFUNCTION(BlueprintPure)
	virtual UTexture2D* GetGameDataIcon() { return nullptr; }

#if WITH_EDITOR
	virtual void OnNewAssetCreated() {}
#endif
};

