#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameDataTables.generated.h"

UCLASS(BlueprintType)
class IMPERIAL_API UGDResourceTable : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSoftObjectPtr<class UGameDataAsset>> ResourceDefinitions;
};