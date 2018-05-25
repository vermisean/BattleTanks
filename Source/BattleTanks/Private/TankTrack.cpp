// Copyright 2018 Sean Duffy

#include "TankTrack.h"
#include "BattleTanks.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
	
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::ApplySideWaysForce()
{
	// Calculate slip speed 
	auto RightVector = GetRightVector();
	auto SlipSpeed = FVector::DotProduct(RightVector, GetComponentVelocity());
	auto DeltaTime = GetWorld()->GetDeltaSeconds();

	// Work out required acceleration per frame to correct
	auto AccelerationCorrection = -SlipSpeed / DeltaTime * RightVector;

	// Calculate and apply sideways force ( F = ma )
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto ForceCorrection = (TankRoot->GetMass() * AccelerationCorrection) / 2;		// Two tracks, so divide by two
	TankRoot->AddForce(ForceCorrection);
}

// Set throttle between -2 and 2
void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -2, +2);

}

void UTankTrack::DriveTrack()
{
	// Apply appropriate force through throttle
	auto ForceApplied = GetForwardVector() * CurrentThrottle * MaxDrivingForce;
	// Gets location of track
	auto ForceLocation = GetComponentLocation();
	// Get root component (UStaticMeshComponent is a USceneComponent, cast to UPrimitive so that we can apply forces)
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	// Drive tracks
	DriveTrack();
	// Apply sideways force
	ApplySideWaysForce();
	// Reset throttle
	CurrentThrottle = 0.0f;
}
