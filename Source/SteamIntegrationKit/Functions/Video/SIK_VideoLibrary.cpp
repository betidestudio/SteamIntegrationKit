// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_VideoLibrary.h"


void USIK_VideoLibrary::GetOPFSettings(FSIK_AppId AppID)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamVideo())
	{
		return;
	}
	SteamVideo()->GetOPFSettings(AppID.GetAppID());
#endif
}

bool USIK_VideoLibrary::GetOPFStringForApp(FSIK_AppId AppID, FString& OutString)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamVideo())
	{
		return false;
	}
	char* Buffer = new char[1024];
	int* BufferSize = new int(1024);
	bool bResult = SteamVideo()->GetOPFStringForApp(AppID.GetAppID(), Buffer, BufferSize);
	OutString = Buffer;
	delete[] Buffer;
	return bResult;
#else
	return false;
#endif
}

void USIK_VideoLibrary::GetVideoURL(FSIK_AppId AppID)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamVideo())
	{
		return;
	}
	SteamVideo()->GetVideoURL(AppID.GetAppID());
#endif
}

bool USIK_VideoLibrary::IsBroadcasting(int32& OutNumViewers)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamVideo())
	{
		return false;
	}
	return SteamVideo()->IsBroadcasting(&OutNumViewers);
#else
	return false;
#endif
}
