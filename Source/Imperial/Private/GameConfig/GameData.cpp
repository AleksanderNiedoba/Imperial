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

#if WITH_EDITOR
	FSoftObjectPath GameInstanceBlueprintPath = "Blueprint'/Game/Core/BP_ImperialGameInstance.BP_ImperialGameInstance'";
	UObject* GameInstanceBlueprint = GameInstanceBlueprintPath.TryLoad();
	if (!GameInstanceBlueprint)
	{
		return nullptr;
	}
	GameInstanceBlueprint->AddToRoot();
	if (UBlueprint* Blueprint = Cast<UBlueprint>(GameInstanceBlueprint))
	{
		if (Blueprint->ParentClass->IsChildOf(UGameInstance::StaticClass()))
		{
			if (UGameInstance* CDO = Cast<UGameInstance>(Blueprint->GeneratedClass->ClassDefaultObject))
			{
				FObjectProperty* GameDataProperty = CastField<FObjectProperty>(CDO->GetClass()->FindPropertyByName("GameData"));
				if (UGameData* GameData = Cast<UGameData>(GameDataProperty->GetObjectPropertyValue_InContainer(CDO)))
				{
					GameData->LoadGameData(); 
					return GameData;
				}
			}
		}
	}
#endif
	return nullptr; 	
}
