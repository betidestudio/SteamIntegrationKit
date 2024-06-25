// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_ScreenshotsLibrary.h"

FSIK_ScreenshotHandle USIK_ScreenshotsLibrary::AddScreenshotToLibrary(FString FileName, FString ThumbnailFileName, int32 Width,
	int32 Height)
{
	if(!SteamScreenshots())
	{
		return FSIK_ScreenshotHandle();
	}
	return SteamScreenshots()->AddScreenshotToLibrary(TCHAR_TO_ANSI(*FileName), TCHAR_TO_ANSI(*ThumbnailFileName), Width, Height);
}

FSIK_ScreenshotHandle USIK_ScreenshotsLibrary::AddVRScreenshotToLibrary(TEnumAsByte<ESIK_VRScreenshotType> Type,
	FString FileName, FString VR_Filename)
{
	if(!SteamScreenshots())
	{
		return FSIK_ScreenshotHandle();
	}
	return SteamScreenshots()->AddVRScreenshotToLibrary(static_cast<EVRScreenshotType>(Type.GetValue()), TCHAR_TO_ANSI(*FileName), TCHAR_TO_ANSI(*VR_Filename));
}

void USIK_ScreenshotsLibrary::HookScreenshots(bool bHook)
{
	if(!SteamScreenshots())
	{
		return;
	}
	SteamScreenshots()->HookScreenshots(bHook);
}

bool USIK_ScreenshotsLibrary::IsScreenshotsHooked()
{
	if(!SteamScreenshots())
	{
		return false;
	}
	return SteamScreenshots()->IsScreenshotsHooked();
}

bool USIK_ScreenshotsLibrary::SetLocation(FSIK_ScreenshotHandle Handle, FString Location)
{
	if(!SteamScreenshots())
	{
		return false;
	}
	return SteamScreenshots()->SetLocation(Handle.GetScreenshotHandle(), TCHAR_TO_ANSI(*Location));
}

bool USIK_ScreenshotsLibrary::TagPublishedFile(FSIK_ScreenshotHandle Handle, FSIK_PublishedFileId PublishedFileID)
{
	if(!SteamScreenshots())
	{
		return false;
	}
	return SteamScreenshots()->TagPublishedFile(Handle.GetScreenshotHandle(), PublishedFileID.GetPublishedFileId());
}

bool USIK_ScreenshotsLibrary::TagUser(FSIK_ScreenshotHandle Handle, FSIK_SteamId SteamID)
{
	if(!SteamScreenshots())
	{
		return false;
	}
	return SteamScreenshots()->TagUser(Handle.GetScreenshotHandle(), SteamID.GetSteamID());
}

void USIK_ScreenshotsLibrary::TriggerScreenshot()
{
	if(!SteamScreenshots())
	{
		return;
	}
	SteamScreenshots()->TriggerScreenshot();
}

FSIK_ScreenshotHandle USIK_ScreenshotsLibrary::WriteScreenshot(TArray<uint8> Data, int32 Width, int32 Height)
{
	if(!SteamScreenshots())
	{
		return FSIK_ScreenshotHandle();
	}
	return SteamScreenshots()->WriteScreenshot(Data.GetData(), Data.Num(), Width, Height);
}


