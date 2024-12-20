// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_MusicLibrary.h"

bool USIK_MusicLibrary::IsEnabled()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMusic())
	{
		return false;
	}
	return SteamMusic()->BIsEnabled();
#else
	return false;
#endif
}

bool USIK_MusicLibrary::IsPlaying()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMusic())
	{
		return false;
	}
	return SteamMusic()->BIsPlaying();
#else
	return false;
#endif
}

TEnumAsByte<ESIK_AudioPlayback_Status> USIK_MusicLibrary::GetPlaybackStatus()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMusic())
	{
		return ESIK_AudioPlayback_Status::Playback_Undefined;
	}
	return static_cast<ESIK_AudioPlayback_Status>(SteamMusic()->GetPlaybackStatus());
#else
	return ESIK_AudioPlayback_Status::Playback_Undefined;
#endif
}

float USIK_MusicLibrary::GetVolume()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMusic())
	{
		return 0.0f;
	}
	return SteamMusic()->GetVolume();
#else
	return 0.0f;
#endif
}

void USIK_MusicLibrary::Pause()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMusic())
	{
		return;
	}
	SteamMusic()->Pause();
#endif
}

void USIK_MusicLibrary::Play()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMusic())
	{
		return;
	}
	SteamMusic()->Play();
#endif
}

void USIK_MusicLibrary::PlayNext()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMusic())
	{
		return;
	}
	SteamMusic()->PlayNext();
#endif
}

void USIK_MusicLibrary::PlayPrevious()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMusic())
	{
		return;
	}
	SteamMusic()->PlayPrevious();
#endif
}

void USIK_MusicLibrary::SetVolume(float Volume)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMusic())
	{
		return;
	}
	SteamMusic()->SetVolume(Volume);
#endif
}
