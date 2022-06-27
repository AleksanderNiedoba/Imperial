// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GridSystem.generated.h"

class UGridConfig; 

USTRUCT(BlueprintType)
struct FGridRowData
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly)
	int32 RowId = 0;
	UPROPERTY(BlueprintReadOnly)
	TArray<class UGridTileData*> RowGridData;

	bool IsEmpty() const { return RowGridData.Num() == 0; }
};


UCLASS()
class IMPERIAL_API UGridSystem : public UObject
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNewGridTileHit, UGridTileData*, TileData); 
	
public:

	UFUNCTION(BlueprintPure, meta = (WorldContext = "InWorldContextObject"))
	static UGridSystem* GetGridSystem(const UObject* InWorldContextObject);
	static UGridSystem* CreateNew();

	bool CreateGrid();
	FVector CalculateTileCenterPoint(int32 RowId, int32 ColumnId) const; 
	void ProcessGridHitData(FHitResult HitLocation);
	
	UFUNCTION(BlueprintPure)
	bool IsLocationValid(FVector Location)const ; 
	UFUNCTION(BlueprintPure)
	UGridTileData* GetGridDataById(int32 RowId, int32 ColumnId);
	UFUNCTION(BlueprintPure)
	UGridTileData* GetCurrentHitGridData() const;
	UFUNCTION(BlueprintPure)
	bool GetGridIdFromLocation(FVector Location, int32& RowId, int32& ColumnId);

	UPROPERTY(BlueprintAssignable)
	FNewGridTileHit OnNewGridTileHit;

private:
	UPROPERTY()
	TArray<FGridRowData> Grid; 
	UPROPERTY()
	UGridConfig* GridConfig = nullptr;
	UPROPERTY()
	UGridTileData* HitGridData = nullptr;
	

};
