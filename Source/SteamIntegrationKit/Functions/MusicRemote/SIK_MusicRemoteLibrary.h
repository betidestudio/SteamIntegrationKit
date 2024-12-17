// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SIK_SharedFile.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SIK_MusicRemoteLibrary.generated.h"

/**
 * 
 */
UCLASS()
class STEAMINTEGRATIONKIT_API USIK_MusicRemoteLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Music Remote")
	static bool ActivationSuccess(bool bValue);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Music Remote")
	static bool IsCurrentMusicRemote();

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Music Remote")
	static bool CurrentEntryDidChange();

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Music Remote")
	static bool CurrentEntryIsAvailable(bool bAvailable);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Music Remote")
	static bool CurrentEntryWillChange();

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Music Remote")
	static bool DeregisterSteamMusicRemote();

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Music Remote")
	static bool EnableLooped(bool bEnable);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Music Remote")
	static bool EnablePlaylists(bool bEnable);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Music Remote")
	static bool EnablePlayNext(bool bEnable);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Music Remote")
	static bool EnablePlayPrevious(bool bEnable);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Music Remote")
	static bool EnableQueue(bool bEnable);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Music Remote")
	static bool EnableShuffled(bool bEnable);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Music Remote")
	static bool PlaylistDidChange();

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Music Remote")
	static bool PlaylistWillChange();

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Music Remote")
	static bool QueueDidChange();
	
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Music Remote")
	static bool QueueWillChange();

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Music Remote")
	static bool RegisterSteamMusicRemote(const FString& Name);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Music Remote")
	static bool ResetPlaylistEntries();

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Music Remote")
	static bool ResetQueueEntries();

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Music Remote")
	static bool SetCurrentPlaylistEntry(int32 nID);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Music Remote")
	static bool SetCurrentQueueEntry(int32 nID);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Music Remote")
	static bool SetDisplayName(const FString& DisplayName);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Music Remote")
	static bool SetPlaylistEntry(int32 nID, int32 nPosition, const FString& EntryText);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Music Remote")
	static bool SetPNGIcon_64x64(TArray<uint8> PNGData);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Music Remote")
	static bool SetQueueEntry(int32 nID, int32 nPosition, const FString& EntryText);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Music Remote")
	static bool UpdateCurrentEntryCoverArt(TArray<uint8> PNGData);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Music Remote")
	static bool UpdateCurrentEntryElapsedSeconds(int32 nValue);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Music Remote")
	static bool UpdateCurrentEntryText(const FString& Text);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Music Remote")
	static bool UpdateLooped(bool bLooped);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Music Remote")
	static bool UpdatePlaybackStatus(TEnumAsByte<ESIK_AudioPlayback_Status> Status);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Music Remote")
	static bool UpdateShuffled(bool bShuffled);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Music Remote")
	static bool UpdateVolume(float flValue);
};
