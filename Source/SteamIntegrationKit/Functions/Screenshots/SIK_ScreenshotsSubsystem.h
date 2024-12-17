// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SIK_SharedFile.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SIK_ScreenshotsSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnScreenshotReady, FSIK_ScreenshotHandle, ScreenshotHandle, const TEnumAsByte<ESIK_Result>&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnScreenshotRequested);

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_ScreenshotsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	USIK_ScreenshotsSubsystem();
	~USIK_ScreenshotsSubsystem();
	
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || Screenshots")
	FOnScreenshotReady OnScreenshotReady;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || Screenshots")
	FOnScreenshotRequested OnScreenshotRequested;

private:
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	STEAM_CALLBACK_MANUAL(USIK_ScreenshotsSubsystem, OnScreenshotReadyCallback, ScreenshotReady_t, m_CallbackScreenshotReady);
	STEAM_CALLBACK_MANUAL(USIK_ScreenshotsSubsystem, OnScreenshotRequestedCallback, ScreenshotRequested_t, m_CallbackScreenshotRequested);
#endif
};
