#pragma once

#include "CoreMinimal.h"
#include "CameraConfig.h"
#include "UObject/NoExportTypes.h"
#include "UObject/SoftObjectPtr.h"
#include "GridConfig.h"
#include "Data/GDResourceDataAsset.h"
#include "Grid/TileDefinitions.h"
#include "GameData.generated.h"



UCLASS(BlueprintType, EditInlineNew, DefaultToInstanced)
class IMPERIAL_API UGameData : public UObject
{
	GENERATED_BODY()

public:
	void LoadGameData();
	static UGameData* GetGameData(); 


	//Configs 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
	TSoftObjectPtr<UGridConfig>  GridConfig = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
	TSoftObjectPtr<UCameraConfig>  CameraConfig = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
	TSoftObjectPtr<UTileDefinitions>  TileDefinitions = nullptr;

	
	UGridConfig* GetGridConfig() const { return CachedGridConfig; } 
	UCameraConfig* GetCameraConfig() const {return CachedCameraConfig; }
	UTileDefinitions* GetTileDefinitions() const {return CachedTileDefinitions; }
	
private:
	UPROPERTY(Transient, DuplicateTransient)
	UGridConfig* CachedGridConfig = nullptr;
	UPROPERTY(Transient, DuplicateTransient)
	UCameraConfig* CachedCameraConfig = nullptr;
	UPROPERTY(Transient, DuplicateTransient)
	UTileDefinitions* CachedTileDefinitions = nullptr;


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UGDResourceTable* ResourceTable;
	UPROPERTY(Transient, BlueprintReadOnly)
	TArray<UGDResourceDataAsset*> ResourceCache;
	
};
