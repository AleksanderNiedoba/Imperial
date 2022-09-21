#include "Data/GDResourceDataAsset.h"
#include "GameConfig/GameData.h"

FText UGDResourceDataAsset::GetGameDataName()
{
	return Name; 
}

FText UGDResourceDataAsset::GetGameDataDescription()
{
	return Description;
}

UTexture2D* UGDResourceDataAsset::GetGameDataIcon()
{
	return !Icon.IsNull() ? Icon.LoadSynchronous() : nullptr;
}

#if WITH_EDITOR
IMPLEMENT_NEWASSETCREATED(Resource)
#endif 