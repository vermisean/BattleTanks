// Copyright 2018 Sean Duffy

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

protected:


private:
	ATank();

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth;

public:
	//Called by engine when damage dealt
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	// Returns current health as a percentage of starting health
	UFUNCTION(BlueprintPure, Category = "Health")		// BP Pure allows for readonly pure function that does not chang anything
	float GetHealthPercent() const;

	// Delegate
	FTankDelegate OnDeath;
};
