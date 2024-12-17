// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SIK_SharedFile.h"
#include "SIK_MusicRemoteSubsystem.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMusicPlayerRemoteToFront);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMusicPlayerRemoteWillActivate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMusicPlayerRemoteWillDeactivate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMusicPlayerSelectsPlaylistEntry, int32, nID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMusicPlayerSelectsQueueEntry, int32, nID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMusicPlayerWantsLooped, bool, bEnable);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMusicPlayerWantsPause);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMusicPlayerWantsPlayingRepeatStatus, int32, nStatus);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMusicPlayerWantsPlayNext);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMusicPlayerWantsPlayPrevious);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMusicPlayerWantsPlay);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMusicPlayerWantsShuffled, bool, bShuffled);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMusicPlayerWantsVolume, float, NewVolume);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMusicPlayerWillQuit);

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_MusicRemoteSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	USIK_MusicRemoteSubsystem();
	~USIK_MusicRemoteSubsystem();

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || Music Remote")
	FOnMusicPlayerRemoteToFront OnMusicPlayerRemoteToFront;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || Music Remote")
	FOnMusicPlayerRemoteWillActivate OnMusicPlayerRemoteWillActivate;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || Music Remote")
	FOnMusicPlayerRemoteWillDeactivate OnMusicPlayerRemoteWillDeactivate;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || Music Remote")
	FOnMusicPlayerSelectsPlaylistEntry OnMusicPlayerSelectsPlaylistEntry;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || Music Remote")
	FOnMusicPlayerSelectsQueueEntry OnMusicPlayerSelectsQueueEntry;
	
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || Music Remote")
	FOnMusicPlayerWantsLooped OnMusicPlayerWantsLooped;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || Music Remote")
	FOnMusicPlayerWantsPause OnMusicPlayerWantsPause;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || Music Remote")
	FOnMusicPlayerWantsPlayingRepeatStatus OnMusicPlayerWantsPlayingRepeatStatus;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || Music Remote")
	FOnMusicPlayerWantsPlayNext OnMusicPlayerWantsPlayNext;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || Music Remote")
	FOnMusicPlayerWantsPlayPrevious OnMusicPlayerWantsPlayPrevious;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || Music Remote")
	FOnMusicPlayerWantsPlay OnMusicPlayerWantsPlay;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || Music Remote")
	FOnMusicPlayerWantsShuffled OnMusicPlayerWantsShuffled;
	
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || Music Remote")
	FOnMusicPlayerWantsVolume OnMusicPlayerWantsVolume;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || Music Remote")
	FOnMusicPlayerWillQuit OnMusicPlayerWillQuit;

private:
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	STEAM_CALLBACK_MANUAL(USIK_MusicRemoteSubsystem, OnMusicPlayerRemoteToFrontCallbck, MusicPlayerRemoteToFront_t, m_CallbackMusicPlayerRemoteToFront);
	STEAM_CALLBACK_MANUAL(USIK_MusicRemoteSubsystem, OnMusicPlayerRemoteWillActivateCallbck, MusicPlayerRemoteWillActivate_t, m_CallbackMusicPlayerRemoteWillActivate);
	STEAM_CALLBACK_MANUAL(USIK_MusicRemoteSubsystem, OnMusicPlayerRemoteWillDeactivateCallbck, MusicPlayerRemoteWillDeactivate_t, m_CallbackMusicPlayerRemoteWillDeactivate);
	STEAM_CALLBACK_MANUAL(USIK_MusicRemoteSubsystem, OnMusicPlayerSelectsPlaylistEntryCallbck, MusicPlayerSelectsPlaylistEntry_t, m_CallbackMusicPlayerSelectsPlaylistEntry);
	STEAM_CALLBACK_MANUAL(USIK_MusicRemoteSubsystem, OnMusicPlayerSelectsQueueEntryCallbck, MusicPlayerSelectsQueueEntry_t, m_CallbackMusicPlayerSelectsQueueEntry);
	STEAM_CALLBACK_MANUAL(USIK_MusicRemoteSubsystem, OnMusicPlayerWantsLoopedCallbck, MusicPlayerWantsLooped_t, m_CallbackMusicPlayerWantsLooped);
	STEAM_CALLBACK_MANUAL(USIK_MusicRemoteSubsystem, OnMusicPlayerWantsPauseCallbck, MusicPlayerWantsPause_t, m_CallbackMusicPlayerWantsPause);
	STEAM_CALLBACK_MANUAL(USIK_MusicRemoteSubsystem, OnMusicPlayerWantsPlayingRepeatStatusCallbck, MusicPlayerWantsPlayingRepeatStatus_t, m_CallbackMusicPlayerWantsPlayingRepeatStatus);
	STEAM_CALLBACK_MANUAL(USIK_MusicRemoteSubsystem, OnMusicPlayerWantsPlayNextCallbck, MusicPlayerWantsPlayNext_t, m_CallbackMusicPlayerWantsPlayNext);
	STEAM_CALLBACK_MANUAL(USIK_MusicRemoteSubsystem, OnMusicPlayerWantsPlayPreviousCallbck, MusicPlayerWantsPlayPrevious_t, m_CallbackMusicPlayerWantsPlayPrevious);
	STEAM_CALLBACK_MANUAL(USIK_MusicRemoteSubsystem, OnMusicPlayerWantsPlayCallbck, MusicPlayerWantsPlay_t, m_CallbackMusicPlayerWantsPlay);
	STEAM_CALLBACK_MANUAL(USIK_MusicRemoteSubsystem, OnMusicPlayerWantsShuffledCallbck, MusicPlayerWantsShuffled_t, m_CallbackMusicPlayerWantsShuffled);
	STEAM_CALLBACK_MANUAL(USIK_MusicRemoteSubsystem, OnMusicPlayerWantsVolumeCallbck, MusicPlayerWantsVolume_t, m_CallbackMusicPlayerWantsVolume);
	STEAM_CALLBACK_MANUAL(USIK_MusicRemoteSubsystem, OnMusicPlayerWillQuitCallbck, MusicPlayerWillQuit_t, m_CallbackMusicPlayerWillQuit);
#endif
};
