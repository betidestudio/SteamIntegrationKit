// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
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
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	STEAM_CALLBACK_MANUAL(USIK_MusicSubsystem, OnPlaybackStatusHasChanged, PlaybackStatusHasChanged_t, m_CallbackPlaybackStatusHasChanged);
	STEAM_CALLBACK_MANUAL(USIK_MusicSubsystem, OnVolumeHasChanged, VolumeHasChanged_t, m_CallbackVolumeHasChanged);
#endif
};
