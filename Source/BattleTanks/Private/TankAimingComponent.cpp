// Copyright 2018 Sean Duffy

#include "TankAimingComponent.h"
#include "BattleTanks.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UTankAimingComponent::BeginPlay()
{
	// Ensures first fire is after initial reload
	LastFireTime = GetWorld()->GetTimeSeconds();
}


void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	this->Barrel = BarrelToSet;
	this->Turret = TurretToSet;
}


void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel) && !ensure(ProjectileBlueprint)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));	// If fails, returns location of Barrel
	
	// Calculate velocity using SuggestProjectileVelocity
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.0f,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	// Calculate the out launch velocity
	if (bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}

}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if (RoundsLeft <= 0)
	{
		FiringState = EFiringState::OutOfAmmo;
	}
	else if ((GetWorld()->GetTimeSeconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel) || !ensure(Turret)) { return; }

	// Figure out difference between current barrel rotation and aim direction
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);

	// Always yaw shortest way
	if (FMath::Abs(DeltaRotator.Yaw) < 180)
	{
		Turret->Rotate(DeltaRotator.Yaw);
	}
	else
	{
		Turret->Rotate(-DeltaRotator.Yaw);
	}

}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	
	auto BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, 0.01f);
	
}

void UTankAimingComponent::Fire()
{
	// Locked for AI, whenever for us
	if (FiringState == EFiringState::Locked || FiringState == EFiringState::Aiming)
	{ 	
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }

		// Spawn projectile at socket location on barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);
		Projectile->LaunchProjectile(LaunchSpeed);

		LastFireTime = GetWorld()->GetTimeSeconds();
		RoundsLeft--;
	}
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

int32 UTankAimingComponent::GetRoundsLeft() const
{
	return RoundsLeft;
}
