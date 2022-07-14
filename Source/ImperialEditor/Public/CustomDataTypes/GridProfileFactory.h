#pragma once
#include "UnrealEd.h"
#include "GridProfileFactory.generated.h"

UCLASS()
class UGridProfileFactory : public UFactory
{
	GENERATED_UCLASS_BODY()
public:
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};