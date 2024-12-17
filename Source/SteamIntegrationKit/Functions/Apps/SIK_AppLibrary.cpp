// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_AppLibrary.h"

bool USIK_AppLibrary::GetDLCDataByIndex(int32 Index, FSIK_AppId& AppID, bool& Available, FString& Name)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamApps())
	{
		return false;
	}
	FString TempName;
	char pchName[256];
	int cchNameBufferSize = 256;
	AppId_t AppID_t;
	const bool bRes = SteamApps()->BGetDLCDataByIndex(Index, &AppID_t, &Available, pchName, cchNameBufferSize);
	if(bRes)
	{
		Name = FString(UTF8_TO_TCHAR(pchName));
		AppID = AppID_t;
	}
	return bRes;
#else
	return false;
#endif
}

bool USIK_AppLibrary::IsAppInstalled(FSIK_AppId AppID)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamApps())
	{
		return false;
	}
	return SteamApps()->BIsAppInstalled(AppID.GetAppID());
#else
	return false;
#endif
}

bool USIK_AppLibrary::IsCybercafe()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamApps())
	{
		return false;
	}
	return SteamApps()->BIsCybercafe();
#else
	return false;
#endif
}

bool USIK_AppLibrary::IsDLCInstalled(int32 AppID)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamApps())
	{
		return false;
	}
	return SteamApps()->BIsDlcInstalled(AppID);
#else
	return false;
#endif
}

bool USIK_AppLibrary::IsLowViolence()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamApps())
	{
		return false;
	}
	return SteamApps()->BIsLowViolence();
#else
	return false;
#endif
}

bool USIK_AppLibrary::IsSubscribed()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamApps())
	{
		return false;
	}
	return SteamApps()->BIsSubscribed();
#else
	return false;
#endif
}

bool USIK_AppLibrary::IsSubscribedApp(int32 AppID)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamApps())
	{
		return false;
	}
	return SteamApps()->BIsSubscribedApp(AppID);
#else
	return false;
#endif
}

bool USIK_AppLibrary::IsSubscribedFromFamilySharing()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamApps())
	{
		return false;
	}
	return SteamApps()->BIsSubscribedFromFamilySharing();
#else
	return false;
#endif
}

bool USIK_AppLibrary::IsSubscribedFromFreeWeekend()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamApps())
	{
		return false;
	}
	return SteamApps()->BIsSubscribedFromFreeWeekend();
#else
	return false;
#endif
}

bool USIK_AppLibrary::IsTimedTrial(int32& SecondsAllowed, int32& SecondsPlayed)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamApps())
	{
		return false;
	}
	uint32 SecondsAllowed_t;
	uint32 SecondsPlayed_t;
	auto Res = SteamApps()->BIsTimedTrial(&SecondsAllowed_t, &SecondsPlayed_t);
	SecondsAllowed = SecondsAllowed_t;
	SecondsPlayed = SecondsPlayed_t;
	return Res;
#else
	return false;
#endif
}

bool USIK_AppLibrary::IsVACBanned()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamApps())
	{
		return false;
	}
	return SteamApps()->BIsVACBanned();
#else
	return false;
#endif
}

int32 USIK_AppLibrary::GetAppBuildID()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamApps())
	{
		return 0;
	}
	return SteamApps()->GetAppBuildId();
#else
	return -1;
#endif
}

FString USIK_AppLibrary::GetAppInstallDir(int32 AppID)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamApps())
	{
		return FString();
	}
	char pchFolder[256];
	const int cchFolderBufferSize = 256;
	const uint32 bRes = SteamApps()->GetAppInstallDir(AppID, pchFolder, cchFolderBufferSize);
	if(bRes > 0)
	{
		return FString(UTF8_TO_TCHAR(pchFolder));
	}
	return FString();
#else
	return FString();
#endif
}

FSIK_SteamId USIK_AppLibrary::GetAppOwner()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamApps())
	{
		return FSIK_SteamId();
	}
	return SteamApps()->GetAppOwner();
#else
	return FSIK_SteamId();
#endif
}

TArray<FString> USIK_AppLibrary::GetAvailableGameLanguages()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	TArray<FString> Result;
	if(!SteamApps())
	{
		return Result;
	}
	const char *pchLanguages = SteamApps()->GetAvailableGameLanguages();
	FString Languages = FString(UTF8_TO_TCHAR(pchLanguages));
	Languages.ParseIntoArray(Result, TEXT(","), true);
	return Result;
#else
	return TArray<FString>();
#endif
}

bool USIK_AppLibrary::GetCurrentBetaName(FString& Name)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamApps())
	{
		return false;
	}
	char pchName[256];
	const int cchNameBufferSize = 256;
	const bool bRes = SteamApps()->GetCurrentBetaName(pchName, cchNameBufferSize);
	if(bRes)
	{
		Name = FString(UTF8_TO_TCHAR(pchName));
	}
	return bRes;
#else
	return false;
#endif
}

FString USIK_AppLibrary::GetCurrentGameLanguage()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamApps())
	{
		return FString();
	}
	const char *pchLanguage = SteamApps()->GetCurrentGameLanguage();
	return FString(UTF8_TO_TCHAR(pchLanguage));
#else
	return FString();
#endif
}

int32 USIK_AppLibrary::GetDLCCount()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamApps())
	{
		return 0;
	}
	return SteamApps()->GetDLCCount();
#else
	return 0;
#endif
}

bool USIK_AppLibrary::GetDLCDownloadProgress(FSIK_AppId AppID, int64& BytesDownloaded, int64& BytesTotal)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamApps())
	{
		return false;
	}
	uint64 BytesDownloaded_t;
	uint64 BytesTotal_t;
	const bool bRes = SteamApps()->GetDlcDownloadProgress(AppID.GetAppID(), &BytesDownloaded_t, &BytesTotal_t);
	BytesDownloaded = BytesDownloaded_t;
	BytesTotal = BytesTotal_t;
	return bRes;
#else
	return false;
#endif
}

int32 USIK_AppLibrary::GetEarliestPurchaseUnixTime(FSIK_AppId AppID)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamApps())
	{
		return 0;
	}
	return SteamApps()->GetEarliestPurchaseUnixTime(AppID.GetAppID());
#else
	return 0;
#endif
}

TArray<int32> USIK_AppLibrary::GetInstalledDepots(FSIK_AppId AppID)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	TArray<int32> Result;
	if(!SteamApps())
	{
		return Result;
	}
	uint32 *pDepots = new uint32[1024];
	const int cMaxDepots = 1024;
	const int cDepots = SteamApps()->GetInstalledDepots(AppID.GetAppID(), pDepots, cMaxDepots);
	for(int i = 0; i < cDepots; i++)
	{
		Result.Add(pDepots[i]);
	}
	delete[] pDepots;
	return Result;
#else
	return TArray<int32>();
#endif
}

int32 USIK_AppLibrary::GetLaunchCommandLine(FString& CommandLine)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamApps())
	{
		return 0;
	}
	char pchCommandLine[256];
	const int cchCommandLineBufferSize = 256;
	const int cchRes = SteamApps()->GetLaunchCommandLine(pchCommandLine, cchCommandLineBufferSize);
	if(cchRes > 0)
	{
		CommandLine = FString(UTF8_TO_TCHAR(pchCommandLine));
	}
	return cchRes;
#else
	return -1;
#endif
}

FString USIK_AppLibrary::GetLaunchQueryParam(FString Key)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamApps())
	{
		return FString();
	}
	const char *pchValue = SteamApps()->GetLaunchQueryParam(TCHAR_TO_UTF8(*Key));
	return FString(UTF8_TO_TCHAR(pchValue));
#else
	return FString();
#endif
}

void USIK_AppLibrary::InstallDLC(FSIK_AppId AppID)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamApps())
	{
		return;
	}
	SteamApps()->InstallDLC(AppID.GetAppID());
#endif
}

bool USIK_AppLibrary::MarkContentCorrupt(bool MissingFilesOnly)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamApps())
	{
		return false;
	}
	return SteamApps()->MarkContentCorrupt(MissingFilesOnly);
#else
	return false;
#endif
}

void USIK_AppLibrary::UninstallDLC(FSIK_AppId AppID)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamApps())
	{
		return;
	}
	SteamApps()->UninstallDLC(AppID.GetAppID());
#endif
}

