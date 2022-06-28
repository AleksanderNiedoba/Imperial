#pragma once

#include "ImperialEditor/TabToolBase.h"

class GridMapCreator : public FTabToolBase
{
public:
	virtual void OnStartupModule() override;
	virtual void OnShutdownModule() override;
	virtual void Initialize() override;
	virtual TSharedRef<SDockTab> SpawnTab(const FSpawnTabArgs& TabSpawnArgs) override;
	
};