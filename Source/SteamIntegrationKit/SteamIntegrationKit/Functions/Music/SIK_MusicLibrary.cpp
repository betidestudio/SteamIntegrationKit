// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_MusicLibrary.h"

bool USIK_MusicLibrary::IsEnabled()
{
	if(!SteamMusic())
	{
		return false;
	}
	return SteamMusic()->BIsEnabled();
}

bool USIK_MusicLibrary::IsPlaying()
{
	if(!SteamMusic())
	{
		return false;
	}
	return SteamMusic()->BIsPlaying();
}

TEnumAsByte<ESIK_AudioPlayback_Status> USIK_MusicLibrary::GetPlaybackStatus()
{
	if(!SteamMusic())
	{
		return ESIK_AudioPlayback_Status::Playback_Undefined;
	}
	return static_cast<ESIK_AudioPlayback_Status>(SteamMusic()->GetPlaybackStatus());
}

float USIK_MusicLibrary::GetVolume()
{
	if(!SteamMusic())
	{
		return 0.0f;
	}
	return SteamMusic()->GetVolume();
}

void USIK_MusicLibrary::Pause()
{
	if(!SteamMusic())
	{
		return;
	}
	SteamMusic()->Pause();
}

void USIK_MusicLibrary::Play()
{
	if(!SteamMusic())
	{
		return;
	}
	SteamMusic()->Play();
}

void USIK_MusicLibrary::PlayNext()
{
	if(!SteamMusic())
	{
		return;
	}
	SteamMusic()->PlayNext();
}

void USIK_MusicLibrary::PlayPrevious()
{
	if(!SteamMusic())
	{
		return;
	}
	SteamMusic()->PlayPrevious();
}

void USIK_MusicLibrary::SetVolume(float Volume)
{
	if(!SteamMusic())
	{
		return;
	}
	SteamMusic()->SetVolume(Volume);
}
