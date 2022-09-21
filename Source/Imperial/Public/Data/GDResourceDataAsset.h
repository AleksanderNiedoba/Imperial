#pragma once

#include "CoreMinimal.h"
#include "GameDataAsset.h"
#include "GDResourceDataAsset.generated.h"

UCLASS(BlueprintType)
class IMPERIAL_API UGDResourceDataAsset : public UGameDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Resource")
	FText Name;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Resource")
	FText Description;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Resource")
	TSoftObjectPtr<UTexture2D> Icon;

	virtual FText GetGameDataName() override;
	virtual FText GetGameDataDescription() override;
	virtual UTexture2D* GetGameDataIcon() override;

#if WITH_EDITOR
	virtual void OnNewAssetCreated() override;
#endif
};




