// Copyright 2018 Sean Duffy

#include "TankTrack.h"
#include "SprungWheel.h"
#include "SpawnPoint.h"
#include "BattleTanks.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}

// Set throttle between -2 and 2
void UTankTrack::SetThrottle(float Throttle)
{
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -2, +2);
	DriveTrack(CurrentThrottle);
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	// Apply appropriate force through throttle
	auto ForceApplied = CurrentThrottle * MaxDrivingForce;
	// Get wheels and get force per wheel
	auto Wheels = GetWheels();
	auto ForcePerWheel = ForceApplied / Wheels.Num();
	// Run through each wheel, apply correct force
	for (ASprungWheel* Wheel : Wheels)
	{
		Wheel->AddDrivingForce(ForcePerWheel);
	}
}

TArray<class ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<ASprungWheel*> ResultArray;
	TArray<USceneComponent*> Children;

	// Need to iterate over child components
	GetChildrenComponents(true, Children);

	for (USceneComponent* Child : Children)
	{
		auto SpawnPointChild = Cast<USpawnPoint>(Child);
		if (!SpawnPointChild) { continue; }

		AActor* SpawnedChild = SpawnPointChild->GetSpawnedActor();
		auto SprungWheel = Cast<ASprungWheel>(SpawnedChild);
		if (!SprungWheel) { continue; }

		ResultArray.Add(SprungWheel);
	}

	return ResultArray;
}
