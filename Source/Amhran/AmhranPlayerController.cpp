// Fill out your copyright notice in the Description page of Project Settings.

#include "Amhran.h"
#include "AmhranPlayerController.h"

void AAmhranPlayerController::CenterMouse() {
	const ULocalPlayer* LocalPlayer = GetLocalPlayer();
	if (LocalPlayer && LocalPlayer->ViewportClient)
	{
		FViewport* Viewport = LocalPlayer->ViewportClient->Viewport;
		if (Viewport)
		{
			FVector2D ViewportSize;
			LocalPlayer->ViewportClient->GetViewportSize(ViewportSize);
			const int32 X = static_cast<int32>(ViewportSize.X * 0.5f);
			const int32 Y = static_cast<int32>(ViewportSize.Y * 0.5f);

			Viewport->SetMouse(X, Y);
		}
	}
}

void AAmhranPlayerController::OnKill() {
	IgnoreMoveInput = true;
	IgnoreLookInput = true;
}