// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
THIRD_PARTY_INCLUDES_START
#if WITH_ENGINE_STEAM
#include <steam/steam_api.h>
#include <steam/steamtypes.h>
#include <steam/isteammusic.h>
#include <steam/steam_api_common.h>
#else
#include <steam_api_common.h>
#include "isteammusic.h"
#endif
THIRD_PARTY_INCLUDES_END
#include "SIK_SharedFile.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SIK_MusicSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlaybackStatusHasChanged);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FVolumeHasChanged, float, Volume);
UCLASS()
class STEAMINTEGRATIONKIT_API USIK_MusicSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	USIK_MusicSubsystem();
	~USIK_MusicSubsystem();

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || Music")
	FPlaybackStatusHasChanged PlaybackStatusHasChanged;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || Music")
	FVolumeHasChanged VolumeHasChanged;

private:
	STEAM_CALLBACK_MANUAL(USIK_MusicSubsystem, OnPlaybackStatusHasChanged, PlaybackStatusHasChanged_t, m_CallbackPlaybackStatusHasChanged);
	STEAM_CALLBACK_MANUAL(USIK_MusicSubsystem, OnVolumeHasChanged, VolumeHasChanged_t, m_CallbackVolumeHasChanged);
};
