#pragma once

#include "CoreMinimal.h"
#include "IGameSystems.h"
#include "Engine/GameInstance.h"
#include "ImperialGameInstance.generated.h"


UCLASS()
class IMPERIAL_API UImperialGameInstance : public UGameInstance, public IGameSystems 
{
	GENERATED_BODY()

public:
	
	virtual void Init() override;
	virtual UGameData* GetGameDataSystem() const override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	UGameData* GameData;

	//Game systems
	UPROPERTY(Transient)
	UGridSystem* GridSystem = nullptr;
	virtual UGridSystem* GetGridSystem() const override; 
};
