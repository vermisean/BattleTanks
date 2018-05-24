// Copyright 2018 Sean Duffy

#include "Tank.h"
#include "BattleTanks.h"


ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;
}

float ATank::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(Damage);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;

	if (CurrentHealth <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Dead tank"));
	}

	return DamageToApply;
}

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth;
}

