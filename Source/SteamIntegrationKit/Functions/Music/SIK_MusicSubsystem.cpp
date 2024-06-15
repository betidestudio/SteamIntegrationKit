// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_MusicSubsystem.h"

#include "Async/Async.h"


USIK_MusicSubsystem::USIK_MusicSubsystem()
{
#ifdef ONLINESUBSYSTEMSTEAM_PACKAGE
	m_CallbackPlaybackStatusHasChanged.Register(this, &USIK_MusicSubsystem::OnPlaybackStatusHasChanged);
	m_CallbackVolumeHasChanged.Register(this, &USIK_MusicSubsystem::OnVolumeHasChanged);

 	if(IsRunningDedicatedServer())
 	{
	m_CallbackPlaybackStatusHasChanged.SetGameserverFlag();
	m_CallbackVolumeHasChanged.SetGameserverFlag();
}
#endif
}

USIK_MusicSubsystem::~USIK_MusicSubsystem()
{
#ifdef ONLINESUBSYSTEMSTEAM_PACKAGE
	m_CallbackPlaybackStatusHasChanged.Unregister();
	m_CallbackVolumeHasChanged.Unregister();
#endif
}

void USIK_MusicSubsystem::OnPlaybackStatusHasChanged(PlaybackStatusHasChanged_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		PlaybackStatusHasChanged.Broadcast();
	});
}

void USIK_MusicSubsystem::OnVolumeHasChanged(VolumeHasChanged_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		VolumeHasChanged.Broadcast(Param.m_flNewVolume);
	});
}