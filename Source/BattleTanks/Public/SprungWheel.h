// Copyright 2018 Sean Duffy

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "SprungWheel.generated.h"

UCLASS()
class BATTLETANKS_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	ASprungWheel();
	virtual void Tick(float DeltaTime) override;
	// Allows for driving forward
	void AddDrivingForce(float ForceMagnitude);

protected:
	virtual void BeginPlay() override;

private:
	void SetUpConstraint();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void ApplyForce();

	// Components
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* Wheel = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* Axle = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPhysicsConstraintComponent* MassWheelConstraint = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPhysicsConstraintComponent* AxleWheelConstraint = nullptr;

	float TotalForceMagnitudeThisFrame = 0;
};
