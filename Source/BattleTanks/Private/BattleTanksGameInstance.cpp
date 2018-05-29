// Copyright 2018 Sean Duffy

#include "BattleTanksGameInstance.h"
#include "MoviePlayer.h"
#include "CustomGameViewportClient.h"


void UBattleTanksGameInstance::Init()
{
	Super::Init();

	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UBattleTanksGameInstance::BeginLoadingScreen);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UBattleTanksGameInstance::EndLoadingScreen);
}

void UBattleTanksGameInstance::BeginLoadingScreen(const FString& MapName)
{
	if (!IsRunningDedicatedServer())
	{
		FLoadingScreenAttributes LoadingScreen;
		LoadingScreen.bAutoCompleteWhenLoadingCompletes = false;
		LoadingScreen.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget();

		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	}
}

void UBattleTanksGameInstance::EndLoadingScreen(UWorld* InLoadedWorld)
{
// 	const UWorld* World = GetWorld();
// 	if (World)
// 	{
// 		UCustomGameViewportClient* GameViewportClient = Cast<UCustomGameViewportClient>(World->GetGameViewport());
// 		GameViewportClient->Fade(Duration, bToBlack);
// 	}
}
