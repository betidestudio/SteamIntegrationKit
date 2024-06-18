// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_UtilsLibrary.h"


bool USIK_UtilsLibrary::OverlayNeedsPresent()
{
	if(!SteamUtils())
	{
		return false;
	}
	return SteamUtils()->BOverlayNeedsPresent();
}

FSIK_AppId USIK_UtilsLibrary::GetAppID()
{
	if(!SteamUtils())
	{
		return FSIK_AppId();
	}
	return SteamUtils()->GetAppID();
}

int32 USIK_UtilsLibrary::GetCurrentBatteryPower()
{
	if(!SteamUtils())
	{
		return 0;
	}
	return SteamUtils()->GetCurrentBatteryPower();
}

FString USIK_UtilsLibrary::GetEnteredGamepadTextInput()
{
	if(!SteamUtils())
	{
		return FString();
	}
	char *	rgchText = new char[128];
	SteamUtils()->GetEnteredGamepadTextInput(rgchText, 128);
	FString result = FString(UTF8_TO_TCHAR(rgchText));
	delete[] rgchText;
	return result;
}

int32 USIK_UtilsLibrary::GetEnteredGamepadTextLength()
{
	if(!SteamUtils())
	{
		return 0;
	}
	return SteamUtils()->GetEnteredGamepadTextLength();
}

UTexture2D* USIK_UtilsLibrary:: GetFriendAvatarImage(int32 Image)
{	
	if (!SteamUtils())
	{
		return nullptr;
	}

	uint32 Width, Height;
	if (!SteamUtils()->GetImageSize(Image, &Width, &Height))
	{
		return nullptr;
	}

	uint32 Size = Width * Height * 4;
	uint8* rgubDest = new uint8[Size];
	if (!SteamUtils()->GetImageRGBA(Image, rgubDest, Size))
	{
		delete[] rgubDest;
		return nullptr;
	}

	UTexture2D* Texture = UTexture2D::CreateTransient(Width, Height);
	if (!Texture)
	{
		delete[] rgubDest;
		return nullptr;
	}

	uint8* MipData = static_cast<uint8*>(Texture->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE));
	FMemory::Memcpy(MipData, rgubDest, Height * Width * 4);
	Texture->GetPlatformData()->Mips[0].BulkData.Unlock();

	Texture->NeverStream = true;
	Texture->UpdateResource();

	delete[] rgubDest;
	return Texture;
}	

FString USIK_UtilsLibrary::GetIPCountry()
{
	if(!SteamUtils())
	{
		return FString();
	}
	return FString(UTF8_TO_TCHAR(SteamUtils()->GetIPCountry()));
}

int32 USIK_UtilsLibrary::GetSecondsSinceAppActive()
{
	if(!SteamUtils())
	{
		return 0;
	}
	return SteamUtils()->GetSecondsSinceAppActive();
}

int32 USIK_UtilsLibrary::GetSecondsSinceComputerActive()
{
	if(!SteamUtils())
	{
		return 0;
	}
	return SteamUtils()->GetSecondsSinceComputerActive();
}

int32 USIK_UtilsLibrary::GetServerRealTime()
{
	if(!SteamUtils())
	{
		return 0;
	}
	return SteamUtils()->GetServerRealTime();
}

FString USIK_UtilsLibrary::GetSteamUILanguage()
{
	if(!SteamUtils())
	{
		return FString();
	}
	return FString(UTF8_TO_TCHAR(SteamUtils()->GetSteamUILanguage()));
}

bool USIK_UtilsLibrary::IsOverlayEnabled()
{
	if(!SteamUtils())
	{
		return false;
	}
	return SteamUtils()->IsOverlayEnabled();
}

bool USIK_UtilsLibrary::IsSteamChinaLauncher()
{
	if(!SteamUtils())
	{
		return false;
	}
	return SteamUtils()->IsSteamChinaLauncher();
}

bool USIK_UtilsLibrary::InitFilterText()
{
	if(!SteamUtils())
	{
		return false;
	}
	return SteamUtils()->InitFilterText();
}

bool USIK_UtilsLibrary::IsSteamInBigPictureMode()
{
	if(!SteamUtils())
	{
		return false;
	}
	return SteamUtils()->IsSteamInBigPictureMode();
}

bool USIK_UtilsLibrary::IsSteamRunningInVR()
{
	if(!SteamUtils())
	{
		return false;
	}
	return SteamUtils()->IsSteamRunningInVR();
}

bool USIK_UtilsLibrary::IsVRHeadsetStreamingEnabled()
{
	if(!SteamUtils())
	{
		return false;
	}
	return SteamUtils()->IsVRHeadsetStreamingEnabled();
}

bool USIK_UtilsLibrary::IsSteamRunningOnSteamDeck()
{
	if(!SteamUtils())
	{
		return false;
	}
	return SteamUtils()->IsSteamRunningOnSteamDeck();
}

void USIK_UtilsLibrary::SetOverlayNotificationInset(int32 HorizontalInset, int32 VerticalInset)
{
	if(!SteamUtils())
	{
		return;
	}
	SteamUtils()->SetOverlayNotificationInset(HorizontalInset, VerticalInset);
}

void USIK_UtilsLibrary::SetOverlayNotificationPosition(TEnumAsByte<ESIK_NotificationPosition> NotificationPosition)
{
	if(!SteamUtils())
	{
		return;
	}
	SteamUtils()->SetOverlayNotificationPosition(static_cast<ENotificationPosition>(NotificationPosition.GetValue()));
}

void USIK_UtilsLibrary::SetVRHeadsetStreamingEnabled(bool bEnabled)
{
	if(!SteamUtils())
	{
		return;
	}
	SteamUtils()->SetVRHeadsetStreamingEnabled(bEnabled);
}

void USIK_UtilsLibrary::StartVrDashboard()
{
	if(!SteamUtils())
	{
		return;
	}
	SteamUtils()->StartVRDashboard();
}

void USIK_UtilsLibrary::SetGameLauncherMode(bool bLauncherMode)
{
	if(!SteamUtils())
	{
		return;
	}
	SteamUtils()->SetGameLauncherMode(bLauncherMode);
}



