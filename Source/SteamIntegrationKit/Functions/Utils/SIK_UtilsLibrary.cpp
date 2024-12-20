// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_UtilsLibrary.h"

bool USIK_UtilsLibrary::IsControllerConnected()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
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
#else
	return false;
#endif
}
bool USIK_UtilsLibrary::OpenSteamKeyboard(int32 KeyboardMode, int32 TextFieldXPosition, int32 TextFieldYPosition, int32 TextFieldWidth, int32 TextFieldHeight)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if (SteamUtils())
	{
		return SteamUtils()->ShowFloatingGamepadTextInput(static_cast<EFloatingGamepadTextInputMode>(KeyboardMode), TextFieldXPosition, TextFieldYPosition, TextFieldWidth, TextFieldHeight);
	}
	return false;
#else
	return false;
#endif
}

bool USIK_UtilsLibrary::OverlayNeedsPresent()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUtils())
	{
		return false;
	}
	return SteamUtils()->BOverlayNeedsPresent();
#else
	return false;
#endif
}

FSIK_AppId USIK_UtilsLibrary::GetAppID()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUtils())
	{
		return FSIK_AppId();
	}
	return SteamUtils()->GetAppID();
#else
	return FSIK_AppId();
#endif	
}

int32 USIK_UtilsLibrary::GetCurrentBatteryPower()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUtils())
	{
		return 0;
	}
	return SteamUtils()->GetCurrentBatteryPower();
#else
	return 0;
#endif
}

FString USIK_UtilsLibrary::GetEnteredGamepadTextInput()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUtils())
	{
		return FString();
	}
	char *	rgchText = new char[128];
	SteamUtils()->GetEnteredGamepadTextInput(rgchText, 128);
	FString result = FString(UTF8_TO_TCHAR(rgchText));
	delete[] rgchText;
	return result;
#else
	return FString();
#endif
}

int32 USIK_UtilsLibrary::GetEnteredGamepadTextLength()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUtils())
	{
		return 0;
	}
	return SteamUtils()->GetEnteredGamepadTextLength();
#else
	return 0;
#endif
}

bool USIK_UtilsLibrary::GetImageRGBA(int32 Image, TArray<FColor>& OutData, int32& OutWidth, int32& OutHeight)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
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
#else
	return false;
#endif
}

FString USIK_UtilsLibrary::GetIPCountry()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUtils())
	{
		return FString();
	}
	return UTF8_TO_TCHAR(SteamUtils()->GetIPCountry());
#else
	return FString();
#endif
}

int32 USIK_UtilsLibrary::GetSecondsSinceAppActive()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUtils())
	{
		return 0;
	}
	return SteamUtils()->GetSecondsSinceAppActive();
#else
	return 0;
#endif
}

int32 USIK_UtilsLibrary::GetSecondsSinceComputerActive()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUtils())
	{
		return 0;
	}
	return SteamUtils()->GetSecondsSinceComputerActive();
#else
	return 0;
#endif
}

int32 USIK_UtilsLibrary::GetServerRealTime()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUtils())
	{
		return 0;
	}
	return SteamUtils()->GetServerRealTime();
#else
	return 0;
#endif
}

FString USIK_UtilsLibrary::GetSteamUILanguage()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUtils())
	{
		return FString();
	}
	return FString(UTF8_TO_TCHAR(SteamUtils()->GetSteamUILanguage()));
#else
	return FString();
#endif
}

bool USIK_UtilsLibrary::IsOverlayEnabled()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUtils())
	{
		return false;
	}
	return SteamUtils()->IsOverlayEnabled();
#else
	return false;
#endif
}

bool USIK_UtilsLibrary::IsSteamChinaLauncher()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUtils())
	{
		return false;
	}
	return SteamUtils()->IsSteamChinaLauncher();
#else
	return false;
#endif
}

bool USIK_UtilsLibrary::InitFilterText()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUtils())
	{
		return false;
	}
	return SteamUtils()->InitFilterText();
#else
	return false;
#endif
}

bool USIK_UtilsLibrary::IsSteamInBigPictureMode()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUtils())
	{
		return false;
	}
	return SteamUtils()->IsSteamInBigPictureMode();
#else
	return false;
#endif
}

bool USIK_UtilsLibrary::IsSteamRunningInVR()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUtils())
	{
		return false;
	}
	return SteamUtils()->IsSteamRunningInVR();
#else
	return false;
#endif
}

bool USIK_UtilsLibrary::IsVRHeadsetStreamingEnabled()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUtils())
	{
		return false;
	}
	return SteamUtils()->IsVRHeadsetStreamingEnabled();
#else
	return false;
#endif
}

bool USIK_UtilsLibrary::IsSteamRunningOnSteamDeck()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUtils())
	{
		return false;
	}
	return SteamUtils()->IsSteamRunningOnSteamDeck();
#else
	return false;
#endif
}

void USIK_UtilsLibrary::SetOverlayNotificationInset(int32 HorizontalInset, int32 VerticalInset)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUtils())
	{
		return;
	}
	SteamUtils()->SetOverlayNotificationInset(HorizontalInset, VerticalInset);
#endif
}

void USIK_UtilsLibrary::SetOverlayNotificationPosition(TEnumAsByte<ESIK_NotificationPosition> NotificationPosition)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUtils())
	{
		return;
	}
	SteamUtils()->SetOverlayNotificationPosition(static_cast<ENotificationPosition>(NotificationPosition.GetValue()));
#endif
}

void USIK_UtilsLibrary::SetVRHeadsetStreamingEnabled(bool bEnabled)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUtils())
	{
		return;
	}
	SteamUtils()->SetVRHeadsetStreamingEnabled(bEnabled);
#endif
}

bool USIK_UtilsLibrary::ShowGamepadTextInput(TEnumAsByte<ESIK_EGamepadTextInputMode> InputMode,
	TEnumAsByte<ESIK_EGamepadTextInputLineMode> LineInputMode, const FString& Description, int32 CharMax,
	const FString& ExistingText)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUtils())
	{
		return false;
	}
	return SteamUtils()->ShowGamepadTextInput(static_cast<EGamepadTextInputMode>(InputMode.GetValue()), static_cast<EGamepadTextInputLineMode>(LineInputMode.GetValue()), TCHAR_TO_ANSI(*Description), CharMax, TCHAR_TO_ANSI(*ExistingText));
#else
	return false;
#endif
}

bool USIK_UtilsLibrary::ShowFloatingGamepadTextInput(TEnumAsByte<ESIK_EFloatingGamepadTextInputMode> KeyboardMode,
	int32 TextFieldXPosition, int32 TextFieldYPosition, int32 TextFieldWidth, int32 TextFieldHeight)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUtils())
	{
		return false;
	}
	return SteamUtils()->ShowFloatingGamepadTextInput(static_cast<EFloatingGamepadTextInputMode>(KeyboardMode.GetValue()), TextFieldXPosition, TextFieldYPosition, TextFieldWidth, TextFieldHeight);
#else
	return false;
#endif
}

void USIK_UtilsLibrary::StartVrDashboard()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUtils())
	{
		return;
	}
	SteamUtils()->StartVRDashboard();
#endif
}

void USIK_UtilsLibrary::SetGameLauncherMode(bool bLauncherMode)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUtils())
	{
		return;
	}
	SteamUtils()->SetGameLauncherMode(bLauncherMode);
#endif
}



