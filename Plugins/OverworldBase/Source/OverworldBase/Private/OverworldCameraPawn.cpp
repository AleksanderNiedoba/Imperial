// Fill out your copyright notice in the Description page of Project Settings.


#include "OverworldCameraPawn.h"

AOverworldCameraPawn::AOverworldCameraPawn()
{
	CameraRootComponent = CreateDefaultSubobject<USceneComponent>("CameraRootComponent");
	CameraRootComponent->SetupAttachment(RootComponent);
	RootComponent = CameraRootComponent;

	HorizontalSpanRoot = CreateDefaultSubobject<USceneComponent>("HorizontalSpanRoot");
	HorizontalSpanRoot->SetupAttachment(CameraRootComponent);

	VerticalSpanRoot = CreateDefaultSubobject<USceneComponent>("VerticalSpanRoot");
	VerticalSpanRoot->SetupAttachment(HorizontalSpanRoot);

	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>("CameraSpringArm");
	CameraSpringArm->SetupAttachment(VerticalSpanRoot);
	CameraSpringArm->bDoCollisionTest = false; 

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(CameraSpringArm);
	
}

void AOverworldCameraPawn::BeginPlay()
{
	Super::BeginPlay();

	CacheDefaults(); 
	SetupCameraDefaults();
}

void AOverworldCameraPawn::CacheDefaults()
{
	DefaultSpringArmLength = 1000.0;
	MaxZoomDistance = 30000.0;
	MinZoomDistance = 4000.0;
	CameraSpeedMultiplier = 50.0;
	CameraZoomSpeedMultiplier = 0.1;
	MaxVerticalSpan = -20;
	MinVerticalSpan = -75.0;
	DefaultCameraRotation = FRotator(-30.0, 0.0, 0.0);
}

void AOverworldCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (NeedZoomUpdate) {
		UpdateZoomDistance();
	}

}

void AOverworldCameraPawn::SetupCameraDefaults()
{
	DestZoomDistance = DefaultSpringArmLength;
	CameraSpringArm->TargetArmLength = DefaultSpringArmLength;
	VerticalSpanRoot->SetRelativeRotation(DefaultCameraRotation);
}

void AOverworldCameraPawn::UpdateZoomDistance()
{
	float CurrentZoomDistance = CameraSpringArm->TargetArmLength;

	if (CurrentZoomDistance != DestZoomDistance)
	{
		if (abs(DestZoomDistance - CurrentZoomDistance) <= CameraZoomSpeedMultiplier)
		{
			CameraSpringArm->TargetArmLength = DestZoomDistance;
			NeedZoomUpdate = false;
			return;
		}
		CurrentZoomDistance = FMath::Lerp(CurrentZoomDistance, DestZoomDistance, CameraZoomSpeedMultiplier);
		CameraSpringArm->TargetArmLength = CurrentZoomDistance;
	}
}



void AOverworldCameraPawn::MoveCamera(const EScreenMovement Direction)
{
	const FVector CurrentLocation = GetActorLocation();
	const FVector ForwardMoveVector = HorizontalSpanRoot->GetForwardVector();
	const FVector RightMoveVector = HorizontalSpanRoot->GetRightVector();
	FVector NewLocation;


	switch (Direction)
	{
	case EScreenMovement::Bottom:
		NewLocation = CurrentLocation - ForwardMoveVector * CameraSpeedMultiplier;
		break;
	case EScreenMovement::Top:
		NewLocation = CurrentLocation + ForwardMoveVector * CameraSpeedMultiplier;
		break;
	case EScreenMovement::Right:
		NewLocation = CurrentLocation + RightMoveVector * CameraSpeedMultiplier;
		break;
	case EScreenMovement::Left:
		NewLocation = CurrentLocation - RightMoveVector * CameraSpeedMultiplier;
		break;
	}

	SetActorLocation(NewLocation);
}

void AOverworldCameraPawn::AdjustCameraSpan(const float MouseX, const float MouseY) const 
{
	if (abs(MouseX) > 0)
	{
		HorizontalSpanRoot->AddRelativeRotation(FRotator(0.0, MouseX, 0.0));
	}
	if (abs(MouseY) > 0)
	{
		const float CurrentVerticalRotation = VerticalSpanRoot->GetRelativeRotation().Pitch;
		const float NewVerticalRotation = FMath::Clamp(CurrentVerticalRotation + MouseY, MinVerticalSpan, MaxVerticalSpan);
		VerticalSpanRoot->SetRelativeRotation(FRotator(NewVerticalRotation, 0.0, 0.0));
	}
}

void AOverworldCameraPawn::RequestZoomChange(const EZoomState ZoomState)
{
	const float PrevoiusZoomDistance = DestZoomDistance;

	switch (ZoomState)
	{
	case EZoomState::ZommingIn:
		DestZoomDistance = FMath::Clamp(DestZoomDistance += 1000, MinZoomDistance, MaxZoomDistance);
		break;
	case EZoomState::ZommingOut:
		DestZoomDistance = FMath::Clamp(DestZoomDistance -= 1000, MinZoomDistance, MaxZoomDistance);
		break;
	}
	if (PrevoiusZoomDistance != DestZoomDistance)
		NeedZoomUpdate = true;
}



