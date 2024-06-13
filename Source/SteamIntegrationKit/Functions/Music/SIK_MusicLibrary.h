// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SIK_SharedFile.h"
THIRD_PARTY_INCLUDES_START
#if WITH_ENGINE_STEAM
#include <steam/isteammusicremote.h>
#else
#include <isteammusicremote.h>
#endif
THIRD_PARTY_INCLUDES_END
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SIK_MusicLibrary.generated.h"

/**
 * 
 */
UCLASS()
class STEAMINTEGRATIONKIT_API USIK_MusicLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Music")
	static bool IsEnabled();

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Music")
	static bool IsPlaying();

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Music")
	static TEnumAsByte<ESIK_AudioPlayback_Status> GetPlaybackStatus();

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Music")
	static float GetVolume();

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Music")
	static void Pause();

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Music")
	static void Play();

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Music")
	static void PlayNext();

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Music")
	static void PlayPrevious();

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Music")
	static void SetVolume(float Volume);


};
