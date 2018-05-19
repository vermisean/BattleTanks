// Copyright 2018 Sean Duffy

#include "TankAIController.h"
#include "Tank.h"
#include "BattleTanks.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());

	// Ensure there is a player available
	if (PlayerTank)
	{
		// Move towards player
		MoveToActor(PlayerTank, AcceptanceRadius);

		// Aim towards player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		// Fire if ready (TODO Limit each frame)
		ControlledTank->Fire();

	}
}


