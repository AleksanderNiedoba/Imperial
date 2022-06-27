// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OverworldPlayerController.h"
#include "GameFramework/PlayerController.h"
#include "ImperialPlayerController.generated.h"

UCLASS()
class IMPERIAL_API AImperialPlayerController : public AOverworldPlayerController
{
	GENERATED_BODY()

public:
	AImperialPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void Tick(float DeltaSeconds) override;
protected:

	virtual void BeginPlay() override; 
	
private:
	UPROPERTY()
	TEnumAsByte<ECollisionChannel> GridCollisionChannel;
	UPROPERTY()
	class UGridSystem* GridSystem = nullptr; 
};
