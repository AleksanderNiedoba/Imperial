// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GridData.h"
#include "GridProfile.generated.h"


UCLASS(EditInlineNew)
class IMPERIAL_API UGridProfile : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TMap<FIntPoint, FGridProfileData> GridMapProfile;

	void OnProfileCreated(); 
};

