// Copyright Epic Games, Inc. All Rights Reserved.


#include "ImperialGameModeBase.h"
#include "Systems/GridSystem.h"

void AImperialGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	UGridSystem::GetGridSystem(this)->CreateGrid(); 
}
