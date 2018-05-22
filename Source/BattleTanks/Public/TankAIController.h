// Copyright 2018 Sean Duffy

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"
// Depends on movement via pathfinding

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaTime ) override;

	// How close the AI tank can get to the player
	UPROPERTY(EditAnywhere, Category = "Setup")
	float AcceptanceRadius = 3000.0f;
};
