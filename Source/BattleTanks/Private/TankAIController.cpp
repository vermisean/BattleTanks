// Copyright 2018 Sean Duffy

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"
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
	if (!(PlayerTank && ControlledTank)) { return; }
	
	// Move towards player
	MoveToActor(PlayerTank, AcceptanceRadius);

	// Aim towards player
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	if(AimingComponent->GetFiringState() == EFiringState::Locked)
	{
		AimingComponent->Fire();
	}

}

void ATankAIController::SetPawn(APawn* InPawn)
{
	// Using this so that we can ensure we have setpawn called
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!PossessedTank) { return; }

		// Subscribe our local method to tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}

void ATankAIController::OnPossessedTankDeath()
{
	if (!GetPawn()) { return; }
	// Destroys AI Controller when tank is dead
	GetPawn()->DetachFromControllerPendingDestroy();

	//UE_LOG(LogTemp, Warning, TEXT("Received!"));
}

