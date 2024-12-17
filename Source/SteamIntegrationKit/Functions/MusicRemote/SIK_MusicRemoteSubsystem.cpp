// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_MusicRemoteSubsystem.h"

#include "Async/Async.h"


USIK_MusicRemoteSubsystem::USIK_MusicRemoteSubsystem()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	m_CallbackMusicPlayerRemoteToFront.Register(this, &USIK_MusicRemoteSubsystem::OnMusicPlayerRemoteToFrontCallbck);
	m_CallbackMusicPlayerRemoteWillActivate.Register(this, &USIK_MusicRemoteSubsystem::OnMusicPlayerRemoteWillActivateCallbck);
	m_CallbackMusicPlayerRemoteWillDeactivate.Register(this, &USIK_MusicRemoteSubsystem::OnMusicPlayerRemoteWillDeactivateCallbck);
	m_CallbackMusicPlayerSelectsPlaylistEntry.Register(this, &USIK_MusicRemoteSubsystem::OnMusicPlayerSelectsPlaylistEntryCallbck);
	m_CallbackMusicPlayerSelectsQueueEntry.Register(this, &USIK_MusicRemoteSubsystem::OnMusicPlayerSelectsQueueEntryCallbck);
	m_CallbackMusicPlayerWantsLooped.Register(this, &USIK_MusicRemoteSubsystem::OnMusicPlayerWantsLoopedCallbck);
	m_CallbackMusicPlayerWantsPause.Register(this, &USIK_MusicRemoteSubsystem::OnMusicPlayerWantsPauseCallbck);
	m_CallbackMusicPlayerWantsPlayingRepeatStatus.Register(this, &USIK_MusicRemoteSubsystem::OnMusicPlayerWantsPlayingRepeatStatusCallbck);
	m_CallbackMusicPlayerWantsPlayNext.Register(this, &USIK_MusicRemoteSubsystem::OnMusicPlayerWantsPlayNextCallbck);
	m_CallbackMusicPlayerWantsPlayPrevious.Register(this, &USIK_MusicRemoteSubsystem::OnMusicPlayerWantsPlayPreviousCallbck);
	m_CallbackMusicPlayerWantsPlay.Register(this, &USIK_MusicRemoteSubsystem::OnMusicPlayerWantsPlayCallbck);
	m_CallbackMusicPlayerWantsShuffled.Register(this, &USIK_MusicRemoteSubsystem::OnMusicPlayerWantsShuffledCallbck);
	m_CallbackMusicPlayerWantsVolume.Register(this, &USIK_MusicRemoteSubsystem::OnMusicPlayerWantsVolumeCallbck);
	m_CallbackMusicPlayerWillQuit.Register(this, &USIK_MusicRemoteSubsystem::OnMusicPlayerWillQuitCallbck);

 	if(IsRunningDedicatedServer())
 	{
	m_CallbackMusicPlayerRemoteToFront.SetGameserverFlag();
	m_CallbackMusicPlayerRemoteWillActivate.SetGameserverFlag();
	m_CallbackMusicPlayerRemoteWillDeactivate.SetGameserverFlag();
	m_CallbackMusicPlayerSelectsPlaylistEntry.SetGameserverFlag();
	m_CallbackMusicPlayerSelectsQueueEntry.SetGameserverFlag();
	m_CallbackMusicPlayerWantsLooped.SetGameserverFlag();
	m_CallbackMusicPlayerWantsPause.SetGameserverFlag();
	m_CallbackMusicPlayerWantsPlayingRepeatStatus.SetGameserverFlag();
	m_CallbackMusicPlayerWantsPlayNext.SetGameserverFlag();
	m_CallbackMusicPlayerWantsPlayPrevious.SetGameserverFlag();
	m_CallbackMusicPlayerWantsPlay.SetGameserverFlag();
	m_CallbackMusicPlayerWantsShuffled.SetGameserverFlag();
	m_CallbackMusicPlayerWantsVolume.SetGameserverFlag();
	m_CallbackMusicPlayerWillQuit.SetGameserverFlag();
}
#endif
}


USIK_MusicRemoteSubsystem::~USIK_MusicRemoteSubsystem()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	m_CallbackMusicPlayerRemoteToFront.Unregister();
	m_CallbackMusicPlayerRemoteWillActivate.Unregister();
	m_CallbackMusicPlayerRemoteWillDeactivate.Unregister();
	m_CallbackMusicPlayerSelectsPlaylistEntry.Unregister();
	m_CallbackMusicPlayerSelectsQueueEntry.Unregister();
	m_CallbackMusicPlayerWantsLooped.Unregister();
	m_CallbackMusicPlayerWantsPause.Unregister();
	m_CallbackMusicPlayerWantsPlayingRepeatStatus.Unregister();
	m_CallbackMusicPlayerWantsPlayNext.Unregister();
	m_CallbackMusicPlayerWantsPlayPrevious.Unregister();
	m_CallbackMusicPlayerWantsPlay.Unregister();
	m_CallbackMusicPlayerWantsShuffled.Unregister();
	m_CallbackMusicPlayerWantsVolume.Unregister();
	m_CallbackMusicPlayerWillQuit.Unregister();
#endif
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
void USIK_MusicRemoteSubsystem::OnMusicPlayerRemoteToFrontCallbck(MusicPlayerRemoteToFront_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnMusicPlayerRemoteToFront.Broadcast();
	});
}

void USIK_MusicRemoteSubsystem::OnMusicPlayerRemoteWillActivateCallbck(MusicPlayerRemoteWillActivate_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnMusicPlayerRemoteWillActivate.Broadcast();
	});
}

void USIK_MusicRemoteSubsystem::OnMusicPlayerRemoteWillDeactivateCallbck(MusicPlayerRemoteWillDeactivate_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnMusicPlayerRemoteWillDeactivate.Broadcast();
	});
}

void USIK_MusicRemoteSubsystem::OnMusicPlayerSelectsPlaylistEntryCallbck(MusicPlayerSelectsPlaylistEntry_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnMusicPlayerSelectsPlaylistEntry.Broadcast(Param.nID);
	});
}

void USIK_MusicRemoteSubsystem::OnMusicPlayerSelectsQueueEntryCallbck(MusicPlayerSelectsQueueEntry_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnMusicPlayerSelectsQueueEntry.Broadcast(Param.nID);
	});
}

void USIK_MusicRemoteSubsystem::OnMusicPlayerWantsLoopedCallbck(MusicPlayerWantsLooped_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnMusicPlayerWantsLooped.Broadcast(Param.m_bLooped);
	});
}

void USIK_MusicRemoteSubsystem::OnMusicPlayerWantsPauseCallbck(MusicPlayerWantsPause_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnMusicPlayerWantsPause.Broadcast();
	});
}

void USIK_MusicRemoteSubsystem::OnMusicPlayerWantsPlayingRepeatStatusCallbck(MusicPlayerWantsPlayingRepeatStatus_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnMusicPlayerWantsPlayingRepeatStatus.Broadcast(Param.m_nPlayingRepeatStatus);
	});
}

void USIK_MusicRemoteSubsystem::OnMusicPlayerWantsPlayNextCallbck(MusicPlayerWantsPlayNext_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnMusicPlayerWantsPlayNext.Broadcast();
	});
}

void USIK_MusicRemoteSubsystem::OnMusicPlayerWantsPlayPreviousCallbck(MusicPlayerWantsPlayPrevious_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnMusicPlayerWantsPlayPrevious.Broadcast();
	});
}

void USIK_MusicRemoteSubsystem::OnMusicPlayerWantsPlayCallbck(MusicPlayerWantsPlay_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnMusicPlayerWantsPlay.Broadcast();
	});
}

void USIK_MusicRemoteSubsystem::OnMusicPlayerWantsShuffledCallbck(MusicPlayerWantsShuffled_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnMusicPlayerWantsShuffled.Broadcast(Param.m_bShuffled);
	});
}

void USIK_MusicRemoteSubsystem::OnMusicPlayerWantsVolumeCallbck(MusicPlayerWantsVolume_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnMusicPlayerWantsVolume.Broadcast(Param.m_flNewVolume);
	});
}

void USIK_MusicRemoteSubsystem::OnMusicPlayerWillQuitCallbck(MusicPlayerWillQuit_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnMusicPlayerWillQuit.Broadcast();
	});
}
#endif