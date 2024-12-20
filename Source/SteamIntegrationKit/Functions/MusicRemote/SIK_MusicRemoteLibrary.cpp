// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_MusicRemoteLibrary.h"



bool USIK_MusicRemoteLibrary::ActivationSuccess(bool bValue)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->BActivationSuccess(bValue);
#else
	return false;
#endif
}

bool USIK_MusicRemoteLibrary::IsCurrentMusicRemote()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->BIsCurrentMusicRemote();
#else
	return false;
#endif
}

bool USIK_MusicRemoteLibrary::CurrentEntryDidChange()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->CurrentEntryDidChange();
#else
	return false;
#endif
}

bool USIK_MusicRemoteLibrary::CurrentEntryIsAvailable(bool bAvailable)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->CurrentEntryIsAvailable(bAvailable);
#else
	return false;
#endif
}

bool USIK_MusicRemoteLibrary::CurrentEntryWillChange()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->CurrentEntryWillChange();
#else
	return false;
#endif
}

bool USIK_MusicRemoteLibrary::DeregisterSteamMusicRemote()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->DeregisterSteamMusicRemote();
#else
	return false;
#endif
}

bool USIK_MusicRemoteLibrary::EnableLooped(bool bEnable)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->EnableLooped(bEnable);
#else
	return false;
#endif
}

bool USIK_MusicRemoteLibrary::EnablePlaylists(bool bEnable)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->EnablePlaylists(bEnable);
#else
	return false;
#endif
}

bool USIK_MusicRemoteLibrary::EnablePlayNext(bool bEnable)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->EnablePlayNext(bEnable);
#else
	return false;
#endif
}

bool USIK_MusicRemoteLibrary::EnablePlayPrevious(bool bEnable)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->EnablePlayPrevious(bEnable);
#else
	return false;
#endif
}

bool USIK_MusicRemoteLibrary::EnableQueue(bool bEnable)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->EnableQueue(bEnable);
#else
	return false;
#endif
}

bool USIK_MusicRemoteLibrary::EnableShuffled(bool bEnable)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->EnableShuffled(bEnable);
#else
	return false;
#endif
}

bool USIK_MusicRemoteLibrary::PlaylistDidChange()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->PlaylistDidChange();
#else
	return false;
#endif
}

bool USIK_MusicRemoteLibrary::PlaylistWillChange()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->PlaylistWillChange();
#else
	return false;
#endif
}

bool USIK_MusicRemoteLibrary::QueueDidChange()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->QueueDidChange();
#else
	return false;
#endif
}

bool USIK_MusicRemoteLibrary::QueueWillChange()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->QueueWillChange();
#else
	return false;
#endif
}

bool USIK_MusicRemoteLibrary::RegisterSteamMusicRemote(const FString& Name)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->RegisterSteamMusicRemote(TCHAR_TO_ANSI(*Name));
#else
	return false;
#endif
}

bool USIK_MusicRemoteLibrary::ResetPlaylistEntries()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->ResetPlaylistEntries();
#else
	return false;
#endif
}

bool USIK_MusicRemoteLibrary::ResetQueueEntries()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->ResetQueueEntries();
#else
	return false;
#endif
}

bool USIK_MusicRemoteLibrary::SetCurrentPlaylistEntry(int32 nID)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->SetCurrentPlaylistEntry(nID);
#else
	return false;
#endif
}

bool USIK_MusicRemoteLibrary::SetCurrentQueueEntry(int32 nID)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->SetCurrentQueueEntry(nID);
#else
	return false;
#endif
}

bool USIK_MusicRemoteLibrary::SetDisplayName(const FString& DisplayName)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->SetDisplayName(TCHAR_TO_ANSI(*DisplayName));
#else
	return false;
#endif
}

bool USIK_MusicRemoteLibrary::SetPlaylistEntry(int32 nID, int32 nPosition, const FString& EntryText)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->SetPlaylistEntry(nID, nPosition, TCHAR_TO_ANSI(*EntryText));
#else
	return false;
#endif
}

bool USIK_MusicRemoteLibrary::SetPNGIcon_64x64(TArray<uint8> PNGData)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->SetPNGIcon_64x64(PNGData.GetData(), PNGData.Num());
#else
	return false;
#endif
}

bool USIK_MusicRemoteLibrary::SetQueueEntry(int32 nID, int32 nPosition, const FString& EntryText)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->SetQueueEntry(nID, nPosition, TCHAR_TO_ANSI(*EntryText));
#else
	return false;
#endif
}

bool USIK_MusicRemoteLibrary::UpdateCurrentEntryCoverArt(TArray<uint8> PNGData)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->UpdateCurrentEntryCoverArt(PNGData.GetData(), PNGData.Num());
#else
	return false;
#endif
}

bool USIK_MusicRemoteLibrary::UpdateCurrentEntryElapsedSeconds(int32 nValue)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->UpdateCurrentEntryElapsedSeconds(nValue);
#else
	return false;
#endif
}

bool USIK_MusicRemoteLibrary::UpdateCurrentEntryText(const FString& Text)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->UpdateCurrentEntryText(TCHAR_TO_ANSI(*Text));
#else
	return false;
#endif
}

bool USIK_MusicRemoteLibrary::UpdateLooped(bool bLooped)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->UpdateLooped(bLooped);
#else
	return false;
#endif
}

bool USIK_MusicRemoteLibrary::UpdatePlaybackStatus(TEnumAsByte<ESIK_AudioPlayback_Status> Status)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->UpdatePlaybackStatus(static_cast<AudioPlayback_Status>(Status.GetValue()));
#else
	return false;
#endif
}

bool USIK_MusicRemoteLibrary::UpdateShuffled(bool bShuffled)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->UpdateShuffled(bShuffled);
#else
	return false;
#endif
}

bool USIK_MusicRemoteLibrary::UpdateVolume(float flValue)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->UpdateVolume(flValue);
#else
	return false;
#endif
}






