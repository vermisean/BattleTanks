// Copyright 2018 Sean Duffy

#include "TankBarrel.h"
#include "BattleTanks.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	// Ensure relative speed is clamped between -1 and 1
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);

	// Move barrel right amount this frame, given max elevation speed and frame time, clamp within reasonable bounds
	float ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;

	float RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	float Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);

	// Set relative location
	SetRelativeRotation(FRotator(Elevation, 0.0f, 0.0f));
}
