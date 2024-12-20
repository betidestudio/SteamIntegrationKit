// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_ScreenshotsLibrary.h"

FSIK_ScreenshotHandle USIK_ScreenshotsLibrary::AddScreenshotToLibrary(FString FileName, FString ThumbnailFileName, int32 Width,
	int32 Height)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamScreenshots())
	{
		return FSIK_ScreenshotHandle();
	}
	return SteamScreenshots()->AddScreenshotToLibrary(TCHAR_TO_ANSI(*FileName), TCHAR_TO_ANSI(*ThumbnailFileName), Width, Height);
#else
	return FSIK_ScreenshotHandle();
#endif
}

FSIK_ScreenshotHandle USIK_ScreenshotsLibrary::AddVRScreenshotToLibrary(TEnumAsByte<ESIK_VRScreenshotType> Type,
	FString FileName, FString VR_Filename)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamScreenshots())
	{
		return FSIK_ScreenshotHandle();
	}
	return SteamScreenshots()->AddVRScreenshotToLibrary(static_cast<EVRScreenshotType>(Type.GetValue()), TCHAR_TO_ANSI(*FileName), TCHAR_TO_ANSI(*VR_Filename));
#else
	return FSIK_ScreenshotHandle();
#endif
}

void USIK_ScreenshotsLibrary::HookScreenshots(bool bHook)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamScreenshots())
	{
		return;
	}
	SteamScreenshots()->HookScreenshots(bHook);
#endif
}

bool USIK_ScreenshotsLibrary::IsScreenshotsHooked()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamScreenshots())
	{
		return false;
	}
	return SteamScreenshots()->IsScreenshotsHooked();
#else
	return false;
#endif
}

bool USIK_ScreenshotsLibrary::SetLocation(FSIK_ScreenshotHandle Handle, FString Location)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamScreenshots())
	{
		return false;
	}
	return SteamScreenshots()->SetLocation(Handle.GetScreenshotHandle(), TCHAR_TO_ANSI(*Location));
#else
	return false;
#endif
}

bool USIK_ScreenshotsLibrary::TagPublishedFile(FSIK_ScreenshotHandle Handle, FSIK_PublishedFileId PublishedFileID)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamScreenshots())
	{
		return false;
	}
	return SteamScreenshots()->TagPublishedFile(Handle.GetScreenshotHandle(), PublishedFileID.GetPublishedFileId());
#else
	return false;
#endif
}

bool USIK_ScreenshotsLibrary::TagUser(FSIK_ScreenshotHandle Handle, FSIK_SteamId SteamID)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamScreenshots())
	{
		return false;
	}
	return SteamScreenshots()->TagUser(Handle.GetScreenshotHandle(), SteamID.GetSteamID());
#else
	return false;
#endif
}

void USIK_ScreenshotsLibrary::TriggerScreenshot()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamScreenshots())
	{
		return;
	}
	SteamScreenshots()->TriggerScreenshot();
#endif
}

FSIK_ScreenshotHandle USIK_ScreenshotsLibrary::WriteScreenshot(TArray<uint8> Data, int32 Width, int32 Height)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamScreenshots())
	{
		return FSIK_ScreenshotHandle();
	}
	return SteamScreenshots()->WriteScreenshot(Data.GetData(), Data.Num(), Width, Height);
#else
	return FSIK_ScreenshotHandle();
#endif
}


