#pragma once
#include "UnrealEd.h"
#include "GameDataFactory.generated.h"

UCLASS()
class UGameDataFactory : public UFactory
{
	GENERATED_UCLASS_BODY()
	
private:
	UPROPERTY()
	UClass* SelectedClass = nullptr;

public:
	virtual bool ConfigureProperties() override;
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};

