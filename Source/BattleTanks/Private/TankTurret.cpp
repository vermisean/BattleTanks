// Copyright 2018 Sean Duffy

#include "TankTurret.h"
#include "BattleTanks.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	// Ensure relative speed is clamped between -1 and 1
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);

	// Move turret right amount this frame, given max Rotation speed and frame time, clamp within reasonable bounds
	float RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;

	float NewRotation = RelativeRotation.Yaw + RotationChange;

	// Set relative location
	SetRelativeRotation(FRotator(0.0f, NewRotation, 0.0f));
}
