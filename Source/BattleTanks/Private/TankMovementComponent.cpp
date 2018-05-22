// Copyright 2018 Sean Duffy

#include "TankMovementComponent.h"
#include "TankTrack.h"
#include "BattleTanks.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(LeftTrack) || !ensure(RightTrack)) { return; }

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!ensure(LeftTrack) || !ensure(RightTrack)) { return; }

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// No Super as we are replacing the base functionality - We are intercepting this method for the velocity only
	
	// Gets the AI's forward move velocity normal
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	// Get AI's forward vector normal
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	// Get dot product
	auto ForwardThrow = FVector::DotProduct(AIForwardIntention, TankForward);
	// Move forward or backward based on dot product
	this->IntendMoveForward(ForwardThrow);
	// Get cross product
	auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	// Move right or left based on cross product
	this->IntendTurnRight(RightThrow);
}
