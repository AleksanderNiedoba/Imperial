// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid/GridTileData.h"

bool UGridTileData::IsSame(const UGridTileData* GridTileData) const 
{
	return GridId == GridTileData->GridId; 
}

bool UGridTileData::IsSame(const int32 RowId, const int32 ColumnId) const
{
	const FIntPoint InGridId = FIntPoint(RowId, ColumnId);
	return GridId == InGridId; 
}

bool UGridTileData::IsSame(const FIntPoint InGridId) const
{
	return GridId == InGridId; 
}
