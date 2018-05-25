// Copyright 2018 Sean Duffy

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SpawnPoint.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API USpawnPoint : public USceneComponent
{
	GENERATED_BODY()

public:	
	USpawnPoint();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	AActor* GetSpawnedActor() const { return SpawnedActor; }	// inline method

protected:
	virtual void BeginPlay() override;

private:
	// Config
	UPROPERTY(EditDefaultsOnly, Category = "Config")
	TSubclassOf<AActor> SpawnClass;
	
	UPROPERTY()
	AActor* SpawnedActor;
};
