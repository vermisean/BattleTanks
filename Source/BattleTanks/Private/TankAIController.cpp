// Copyright 2018 Sean Duffy

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "BattleTanks.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	// Ensure there is a player available
	if (!ensure(PlayerTank && ControlledTank)) { return; }
	
	// Move towards player
	MoveToActor(PlayerTank, AcceptanceRadius);

	// Aim towards player
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	// Fire if ready (TODO Fix firing & Limit each frame)
	//ControlledTank->Fire();

}


