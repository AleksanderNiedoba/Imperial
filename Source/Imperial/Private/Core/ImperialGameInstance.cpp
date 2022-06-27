// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/ImperialGameInstance.h"
#include "GameConfig/GameData.h"
#include "Systems/GridSystem.h"

void UImperialGameInstance::Init()
{
	Super::Init();
	GameData->LoadGameData();

	GridSystem = UGridSystem::CreateNew(); 
}

UGameData* UImperialGameInstance::GetGameDataSystem() const
{
	return GameData;
}

UGridSystem* UImperialGameInstance::GetGridSystem() const
{
	return GridSystem;
}
