// Copyright 2018 Sean Duffy

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 *	Sets maximum driving force and used to apply forces to the tank
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// Called to drive tank
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void SetThrottle(float Throttle);

	// Max force per track in Newtons
	UPROPERTY(EditDefaultsOnly)
	float MaxDrivingForce = 40000000.0f;		// Assume 40 tonne tank with 1g acceleration
	
private:	
	UTankTrack();

	TArray<class ASprungWheel*> GetWheels() const;

	void DriveTrack(float CurrentThrottle);
};
