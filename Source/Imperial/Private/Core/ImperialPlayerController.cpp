// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/ImperialPlayerController.h"
#include "GameConfig/GridConfig.h"
#include "Grid/GridTileData.h"
#include "Systems/GridSystem.h"

AImperialPlayerController::AImperialPlayerController(const FObjectInitializer& ObjectInitializer)
{
	SetActorTickEnabled(false); 
}

void AImperialPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	GridSystem->ProcessGridHitData(FindNewMouseWorldData(GridCollisionChannel)); 
}

void AImperialPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	const auto* GC = UGridConfig::GetGridConfig();
	GridCollisionChannel = GC->GridCollisionChannel;
	GridSystem = UGridSystem::GetGridSystem(this);
	SetActorTickEnabled(true); 
}
