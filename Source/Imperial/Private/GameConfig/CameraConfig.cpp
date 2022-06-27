#include "GameConfig/CameraConfig.h"
#include "GameConfig/GameData.h"

UCameraConfig* UCameraConfig::GetCameraConfig()
{
	if(auto* GD = UGameData::GetGameData())
	{
		return GD->GetCameraConfig();
	}
	return nullptr;  
}
