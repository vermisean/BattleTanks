// Copyright 2018 Sean Duffy

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameViewportClient.h"
//#include "CustomGameViewportClient.generated.h"

// /**
//  * Simple GameViewportClient used to handle a global fadein/fadeout
//  */
// class BATTLETANKS_API CustomGameViewportClient : public UGameViewportClient
// {
// public:
// 	// Last rendering call in render loop
// 	virtual void PostRender(UCanvas* Canvas) override;
// 
// 	// Used for Fade to and from black
// 	virtual void ClearFade();
// 	
// 	// Clear fading state
// 	virtual void Fade(const float Duration, const bool bToBlack);
// 
// 	// Does the actual fading
// 	void DrawScreenFade(UCanvas* Canvas);
// 
// private:
// 	// Values for fading
// 	uint32 bFading : 1;
// 	uint32 bToBlack : 1;
// 	float FadeAlpha;
// 	float FadeStartTime;
// 	float FadeDuration;
// 
// };
