// Copyright 2018 Sean Duffy

#include "SprungWheel.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

ASprungWheel::ASprungWheel()
{
	PrimaryActorTick.bCanEverTick = true;

	Mass = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mass"));
	SetRootComponent(Mass);

	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	Wheel->SetupAttachment(Mass);

	MassWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("MassWheelConstraint"));
	MassWheelConstraint->SetupAttachment(Mass);
}

void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	
}

void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

