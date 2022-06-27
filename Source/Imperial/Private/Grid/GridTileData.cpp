// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid/GridTileData.h"

bool UGridTileData::IsSame(const UGridTileData* GridTileData) const 
{
	return GridId == GridTileData->GridId; 
}

bool UGridTileData::IsSame(const int32 RowId, const int32 ColumnId) const
{
	const FVector2D InGridId = FVector2D(RowId, ColumnId);
	return GridId == InGridId; 
}
