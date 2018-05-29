// Copyright 2018 Sean Duffy

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BattleTanksGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API UBattleTanksGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;

	UFUNCTION()
	virtual void BeginLoadingScreen(const FString& MapName);

	UFUNCTION()
	virtual void EndLoadingScreen(UWorld* InLoadedWorld);
	
};
