// Copyright 2018 Sean Duffy

#include "TankTrack.h"
#include "BattleTanks.h"

// Set throttle between -1 and 1
void UTankTrack::SetThrottle(float Throttle)
{
	// Apply appropriate force through throttle
	auto ForceApplied = GetForwardVector() * Throttle * MaxDrivingForce;
	// Gets location of track
	auto ForceLocation = GetComponentLocation();	
	// Get root component (UStaticMeshComponent is a USceneComponent, cast to UPrimitive so that we can apply forces)
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
