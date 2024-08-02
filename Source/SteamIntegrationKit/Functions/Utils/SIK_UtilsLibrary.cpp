// Copyright (c) 2024 Betide Studio. All Rights Reserved.
// OpenSteamKeyboard & IsControllerConnected + Repairing the Get Image RGBA function by @MarOwNFR

#include "SIK_UtilsLibrary.h"

#if WITH_ENGINE_STEAM
#include <steam/isteamcontroller.h>
#include <steam/isteaminput.h>
#include <steam/steam_api_common.h>
#include <steam/steamtypes.h>
#else
#include <isteamcontroller.h>
#include <isteaminput.h>
#include <steam_api_common.h>
#include <steamtypes.h>
#endif

bool USIK_UtilsLibrary::IsControllerConnected()
{

	ISteamInput* SteamInputInterface = SteamInput();
	if (!SteamInputInterface)
	{
		return false;
	}

	if (!SteamInputInterface->Init(false))
	{
		return false;
	}

	SteamInputInterface->RunFrame();

	InputHandle_t handlesOut[STEAM_INPUT_MAX_COUNT] = { 0 };

	int numControllers = SteamInputInterface->GetConnectedControllers(handlesOut);

	if (numControllers > 0)
	{
		return true;
	}

	return false;
}
void USIK_UtilsLibrary::OpenSteamKeyboard(int32 KeyboardMode, int32 TextFieldXPosition, int32 TextFieldYPosition, int32 TextFieldWidth, int32 TextFieldHeight)
{
	if (SteamUtils())
	{
		SteamUtils()->ShowFloatingGamepadTextInput(static_cast<EFloatingGamepadTextInputMode>(KeyboardMode), TextFieldXPosition, TextFieldYPosition, TextFieldWidth, TextFieldHeight);
	}
}

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

bool USIK_UtilsLibrary::GetImageRGBA(int32 Image, TArray<FColor>& OutData, int32& OutWidth, int32& OutHeight)
{
	if (!SteamUtils())
	{
		return false;
	}
	uint32 Width, Height;
	if (!SteamUtils()->GetImageSize(Image, &Width, &Height))
	{
		return false;
	}
	uint32 Size = Width * Height * 4;
	uint8* rgubDest = new uint8[Size];
	if (!SteamUtils()->GetImageRGBA(Image, rgubDest, Size))
	{
		delete[] rgubDest;
		return false;
	}
	OutData.Empty(Width * Height);
	for (uint32 i = 0; i < Size; i += 4)
	{
		// Rearrange the color channels from BGRA to RGBA
		OutData.Add(FColor(rgubDest[i + 2], rgubDest[i + 1], rgubDest[i], rgubDest[i + 3]));
	}
	delete[] rgubDest;

	// Assign the width and height to the output parameters
	OutWidth = static_cast<int32>(Width);
	OutHeight = static_cast<int32>(Height);
	
	return true;
}

FString USIK_UtilsLibrary::GetIPCountry()
{
	if(!SteamUtils())
	{
		return FString();
	}
	return UTF8_TO_TCHAR(SteamUtils()->GetIPCountry());
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

bool USIK_UtilsLibrary::ShowGamepadTextInput(TEnumAsByte<ESIK_EGamepadTextInputMode> InputMode,
	TEnumAsByte<ESIK_EGamepadTextInputLineMode> LineInputMode, const FString& Description, int32 CharMax,
	const FString& ExistingText)
{
	if(!SteamUtils())
	{
		return false;
	}
	return SteamUtils()->ShowGamepadTextInput(static_cast<EGamepadTextInputMode>(InputMode.GetValue()), static_cast<EGamepadTextInputLineMode>(LineInputMode.GetValue()), TCHAR_TO_ANSI(*Description), CharMax, TCHAR_TO_ANSI(*ExistingText));
}

bool USIK_UtilsLibrary::ShowFloatingGamepadTextInput(TEnumAsByte<ESIK_EFloatingGamepadTextInputMode> KeyboardMode,
	int32 TextFieldXPosition, int32 TextFieldYPosition, int32 TextFieldWidth, int32 TextFieldHeight)
{
	if(!SteamUtils())
	{
		return false;
	}
	return SteamUtils()->ShowFloatingGamepadTextInput(static_cast<EFloatingGamepadTextInputMode>(KeyboardMode.GetValue()), TextFieldXPosition, TextFieldYPosition, TextFieldWidth, TextFieldHeight);
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