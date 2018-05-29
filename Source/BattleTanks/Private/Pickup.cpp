// Copyright 2018 Sean Duffy

#include "Pickup.h"


// Sets default values
APickup::APickup()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(true);

	//TODO implement overlap with player for pickup

	ParticleEffect = CreateDefaultSubobject<UParticleSystemComponent>(FName("Particle Effect"));
	ParticleEffect->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

}

void APickup::BeginPlay()
{
	Super::BeginPlay();
	
}

void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Rotate(RotSpeed);
}

void APickup::Rotate(float RelativeSpeed)
{
	if (CollisionMesh)
	{
		// Ensure relative speed is clamped between -1 and 1
		RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);

		// Move turret right amount this frame, given max Rotation speed and frame time, clamp within reasonable bounds
		float RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;

		float NewRotation = CollisionMesh->RelativeRotation.Yaw + RotationChange;

		// Set relative location
		CollisionMesh->SetRelativeRotation(FRotator(0.0f, NewRotation, 0.0f));
	}
}

