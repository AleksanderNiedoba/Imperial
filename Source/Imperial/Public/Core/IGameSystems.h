#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IGameSystems.generated.h"

UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UGameSystems : public UInterface
{
	GENERATED_BODY()
};

class IMPERIAL_API IGameSystems
{
	GENERATED_BODY()

public:
	virtual class UGameData* GetGameDataSystem() const { return nullptr; }
	virtual class UGridSystem* GetGridSystem() const { return nullptr; }
};
