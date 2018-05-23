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

protected:
	// How close the AI tank can get to the player
	UPROPERTY(EditDefaultsOnly, Category = "AI Setup")
	float AcceptanceRadius = 80000.0f;

private:
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaTime ) override;
};
