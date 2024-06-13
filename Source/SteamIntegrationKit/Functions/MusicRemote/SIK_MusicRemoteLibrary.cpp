// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_MusicRemoteLibrary.h"



bool USIK_MusicRemoteLibrary::ActivationSuccess(bool bValue)
{
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->BActivationSuccess(bValue);
}

bool USIK_MusicRemoteLibrary::IsCurrentMusicRemote()
{
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->BIsCurrentMusicRemote();
}

bool USIK_MusicRemoteLibrary::CurrentEntryDidChange()
{
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->CurrentEntryDidChange();
}

bool USIK_MusicRemoteLibrary::CurrentEntryIsAvailable(bool bAvailable)
{
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->CurrentEntryIsAvailable(bAvailable);
}

bool USIK_MusicRemoteLibrary::CurrentEntryWillChange()
{
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->CurrentEntryWillChange();
}

bool USIK_MusicRemoteLibrary::DeregisterSteamMusicRemote()
{
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->DeregisterSteamMusicRemote();
}

bool USIK_MusicRemoteLibrary::EnableLooped(bool bEnable)
{
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->EnableLooped(bEnable);
}

bool USIK_MusicRemoteLibrary::EnablePlaylists(bool bEnable)
{
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->EnablePlaylists(bEnable);
}

bool USIK_MusicRemoteLibrary::EnablePlayNext(bool bEnable)
{
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->EnablePlayNext(bEnable);
}

bool USIK_MusicRemoteLibrary::EnablePlayPrevious(bool bEnable)
{
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->EnablePlayPrevious(bEnable);
}

bool USIK_MusicRemoteLibrary::EnableQueue(bool bEnable)
{
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->EnableQueue(bEnable);
}

bool USIK_MusicRemoteLibrary::EnableShuffled(bool bEnable)
{
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->EnableShuffled(bEnable);
}

bool USIK_MusicRemoteLibrary::PlaylistDidChange()
{
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->PlaylistDidChange();
}

bool USIK_MusicRemoteLibrary::PlaylistWillChange()
{
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->PlaylistWillChange();
}

bool USIK_MusicRemoteLibrary::QueueDidChange()
{
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->QueueDidChange();
}

bool USIK_MusicRemoteLibrary::QueueWillChange()
{
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->QueueWillChange();
}

bool USIK_MusicRemoteLibrary::RegisterSteamMusicRemote(const FString& Name)
{
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->RegisterSteamMusicRemote(TCHAR_TO_ANSI(*Name));
}

bool USIK_MusicRemoteLibrary::ResetPlaylistEntries()
{
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->ResetPlaylistEntries();
}

bool USIK_MusicRemoteLibrary::ResetQueueEntries()
{
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->ResetQueueEntries();
}

bool USIK_MusicRemoteLibrary::SetCurrentPlaylistEntry(int32 nID)
{
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->SetCurrentPlaylistEntry(nID);
}

bool USIK_MusicRemoteLibrary::SetCurrentQueueEntry(int32 nID)
{
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->SetCurrentQueueEntry(nID);
}

bool USIK_MusicRemoteLibrary::SetDisplayName(const FString& DisplayName)
{
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->SetDisplayName(TCHAR_TO_ANSI(*DisplayName));
}

bool USIK_MusicRemoteLibrary::SetPlaylistEntry(int32 nID, int32 nPosition, const FString& EntryText)
{
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->SetPlaylistEntry(nID, nPosition, TCHAR_TO_ANSI(*EntryText));
}

bool USIK_MusicRemoteLibrary::SetPNGIcon_64x64(TArray<uint8> PNGData)
{
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->SetPNGIcon_64x64(PNGData.GetData(), PNGData.Num());
}

bool USIK_MusicRemoteLibrary::SetQueueEntry(int32 nID, int32 nPosition, const FString& EntryText)
{
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->SetQueueEntry(nID, nPosition, TCHAR_TO_ANSI(*EntryText));
}

bool USIK_MusicRemoteLibrary::UpdateCurrentEntryCoverArt(TArray<uint8> PNGData)
{
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->UpdateCurrentEntryCoverArt(PNGData.GetData(), PNGData.Num());
}

bool USIK_MusicRemoteLibrary::UpdateCurrentEntryElapsedSeconds(int32 nValue)
{
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->UpdateCurrentEntryElapsedSeconds(nValue);
}

bool USIK_MusicRemoteLibrary::UpdateCurrentEntryText(const FString& Text)
{
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->UpdateCurrentEntryText(TCHAR_TO_ANSI(*Text));
}

bool USIK_MusicRemoteLibrary::UpdateLooped(bool bLooped)
{
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->UpdateLooped(bLooped);
}

bool USIK_MusicRemoteLibrary::UpdatePlaybackStatus(TEnumAsByte<ESIK_AudioPlayback_Status> Status)
{
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->UpdatePlaybackStatus(static_cast<AudioPlayback_Status>(Status.GetValue()));
}

bool USIK_MusicRemoteLibrary::UpdateShuffled(bool bShuffled)
{
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->UpdateShuffled(bShuffled);
}

bool USIK_MusicRemoteLibrary::UpdateVolume(float flValue)
{
	if(!SteamMusicRemote())
	{
		return false;
	}
	return SteamMusicRemote()->UpdateVolume(flValue);
}






