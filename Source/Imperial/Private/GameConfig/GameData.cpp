#include "GameConfig/GameData.h"
#include "Core/IGameSystems.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

void UGameData::LoadGameData()
{
	CachedGridConfig = GridConfig.LoadSynchronous();
	CachedCameraConfig = CameraConfig.LoadSynchronous(); 
}

UGameData* UGameData::GetGameData()
{
	if(!GEngine)
	{
		return nullptr;
	}
	
	auto WorldContexts = GEngine->GetWorldContexts();
	for(auto& WorldContext : WorldContexts)
	{
		if(auto* GameSystem = Cast<IGameSystems>(WorldContext.OwningGameInstance))
		{
			return GameSystem->GetGameDataSystem();
		}
	}
	return nullptr; 
}
