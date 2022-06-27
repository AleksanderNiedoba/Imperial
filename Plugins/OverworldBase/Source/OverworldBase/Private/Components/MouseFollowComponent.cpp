// Copyright Quan Project 2021. All Rights Reserved.


#include "Components/MouseFollowComponent.h"
#include "OverworldStatics.h"


UMouseFollowComponent::UMouseFollowComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UMouseFollowComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UMouseFollowComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(EnableMouseFollow)
	{
		const FVector HitLocation = UOverworldStatics::GetMouseWorldHitLocation(this, ECC_GameTraceChannel1);
		GetOwner()->SetActorLocation(HitLocation);
	}	
}

void UMouseFollowComponent::EnableActorFollowing(bool NewEnable)
{
	EnableMouseFollow = NewEnable;
}

