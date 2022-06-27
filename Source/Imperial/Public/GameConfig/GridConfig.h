#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GridConfig.generated.h"


UCLASS()
class IMPERIAL_API UGridConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "ImperialConfig")
	static UGridConfig* GetGridConfig();
	
	UFUNCTION(BlueprintPure, Category = "Grid")
	float GetHalfTileSize() const;
	UFUNCTION(BlueprintPure, Category = "Grid")
	void GetGridSize(float& GridSizeX, float& GridSizeY) const;
	UFUNCTION(BlueprintPure, Category = "Grid")
	FVector GetGridCenterLocation() const; 

	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Grid")
	int32 NumberOfColumns = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Grid")
	int32 NumberOfRows = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Grid")
	float TileSize = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Grid")
	bool CrossGrid = true; 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Grid")
	TEnumAsByte<ECollisionChannel> GridCollisionChannel;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Grid\|Debug")
	FLinearColor GridColor;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Grid\|Debug")
	float GridOpacity = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Grid\|Debug")
	float GridLineThickness = 0; 
};
