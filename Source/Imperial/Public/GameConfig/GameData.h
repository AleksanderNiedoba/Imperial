#pragma once

#include "CoreMinimal.h"
#include "CameraConfig.h"
#include "UObject/NoExportTypes.h"
#include "UObject/SoftObjectPtr.h"
#include "GridConfig.h"
#include "Grid/TileDefinitions.h"
#include "GameData.generated.h"



UCLASS(BlueprintType, EditInlineNew)
class IMPERIAL_API UGameData : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
	TSoftObjectPtr<UGridConfig>  GridConfig = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
	TSoftObjectPtr<UCameraConfig>  CameraConfig = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
	TSoftObjectPtr<UTileDefinitions>  TileDefinitions = nullptr;

	void LoadGameData();
	static UGameData* GetGameData(); 
	
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
};
