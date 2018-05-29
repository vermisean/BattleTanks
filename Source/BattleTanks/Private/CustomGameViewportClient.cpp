// Copyright 2018 Sean Duffy

#include "CustomGameViewportClient.h"
#include "BattleTanks.h"

// 
// void CustomGameViewportClient::PostRender(UCanvas* Canvas)
// {
// 	// Fade if requested
// 	if (bFading)
// 	{
// 		DrawScreenFade(Canvas);
// 	}
// }
// 
// void CustomGameViewportClient::ClearFade()
// {
// 	bFading = false;
// }
// 
// void CustomGameViewportClient::Fade(const float Duration, const bool bToBlack)
// {
// 	const UWorld* World = GetWorld();
// 	if (World)
// 	{
// 		bFading = true;
// 		this->bToBlack = bToBlack;
// 		FadeDuration = Duration;
// 		FadeStartTime = World->GetTimeSeconds();
// 	}
// }
// 
// void CustomGameViewportClient::DrawScreenFade(UCanvas* Canvas)
// {
// 	if (bFading)
// 	{
// 		const UWorld* World = GetWorld();
// 		if (World)
// 		{
// 			const float Time = World->GetTimeSeconds();
// 			const float Alpha = FMath::Clamp((Time - FadeStartTime) / FadeDuration, 0.f, 1.f);
// 
// 			// Be sure to stay black in fade to black
// 			if (Alpha == 1.f && !bToBlack)
// 			{
// 				bFading = false;
// 			}
// 			else
// 			{
// 				FColor OldColor = Canvas->DrawColor;
// 				FLinearColor FadeColor = FLinearColor::Black;
// 				FadeColor.A = bToBlack ? Alpha : 1 - Alpha;
// 				Canvas->DrawColor = FadeColor.ToFColor(true);
// 				Canvas->DrawTile(Canvas->DefaultTexture, 0, 0, Canvas->ClipX, Canvas->ClipY, 0, 0, Canvas->DefaultTexture->GetSizeX(), Canvas->DefaultTexture->GetSizeY());
// 				Canvas->DrawColor = OldColor;
// 			}
// 		}
// 	}
// }
