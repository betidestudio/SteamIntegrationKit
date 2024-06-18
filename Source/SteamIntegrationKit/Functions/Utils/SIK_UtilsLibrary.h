// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SIK_SharedFile.h"
THIRD_PARTY_INCLUDES_START
#if WITH_ENGINE_STEAM
#include "steam/isteamutils.h"
#else
#include "isteamutils.h"
#endif
THIRD_PARTY_INCLUDES_END
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SIK_UtilsLibrary.generated.h"

/**
 * 
 */
UCLASS()
class STEAMINTEGRATIONKIT_API USIK_UtilsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, DisplayName = "Overlay Needs Present", meta=(Keywords="BOverlayNeedsPresent"), Category="Steam Integration Kit || SDK Functions || Utils")
	static bool OverlayNeedsPresent();
	
	UFUNCTION(BlueprintCallable, DisplayName = "Get App ID", meta=(Keywords="GetAppID"), Category="Steam Integration Kit || SDK Functions || Utils")
	static FSIK_AppId GetAppID();

	UFUNCTION(BlueprintCallable, DisplayName = "Get Current Battery Power", meta=(Keywords="GetCurrentBatteryPower"), Category="Steam Integration Kit || SDK Functions || Utils")
	static int32 GetCurrentBatteryPower();

	UFUNCTION(BlueprintCallable, DisplayName = "Get Entered Gamepad Text Input", meta=(Keywords="GetEnteredGamepadTextInput"), Category="Steam Integration Kit || SDK Functions || Utils")
	static FString GetEnteredGamepadTextInput();

	UFUNCTION(BlueprintCallable, DisplayName = "Get Entered Gamepad Text Length", meta=(Keywords="GetEnteredGamepadTextLength"), Category="Steam Integration Kit || SDK Functions || Utils")
	static int32 GetEnteredGamepadTextLength();

	UFUNCTION(BlueprintCallable, DisplayName = "Get FriendAvatar Image", meta=(Keywords="GetFriendAvatarImage"), Category="Steam Integration Kit || SDK Functions || Utils")
	static UTexture2D* GetFriendAvatarImage(int32 Image);

	UFUNCTION(BlueprintCallable, DisplayName = "Get IP Country", meta=(Keywords="GetIPCountry"), Category="Steam Integration Kit || SDK Functions || Utils")
	static FString GetIPCountry();

	UFUNCTION(BlueprintCallable, DisplayName = "Get Seconds Since App Active", meta=(Keywords="GetSecondsSinceAppActive"), Category="Steam Integration Kit || SDK Functions || Utils")
	static int32 GetSecondsSinceAppActive();

	UFUNCTION(BlueprintCallable, DisplayName = "Get Seconds Since Computer Active", meta=(Keywords="GetSecondsSinceComputerActive"), Category="Steam Integration Kit || SDK Functions || Utils")
	static int32 GetSecondsSinceComputerActive();

	UFUNCTION(BlueprintCallable, DisplayName = "Get Server Real Time", meta=(Keywords="GetServerRealTime"), Category="Steam Integration Kit || SDK Functions || Utils")
	static int32 GetServerRealTime();

	UFUNCTION(BlueprintCallable, DisplayName = "Get Steam UI Language", meta=(Keywords="GetSteamUILanguage"), Category="Steam Integration Kit || SDK Functions || Utils")
	static FString GetSteamUILanguage();

	UFUNCTION(BlueprintCallable, DisplayName = "Is Overlay Enabled", meta=(Keywords="IsOverlayEnabled"), Category="Steam Integration Kit || SDK Functions || Utils")
	static bool IsOverlayEnabled();

	UFUNCTION(BlueprintCallable, DisplayName = "Is Steam China Launcher", meta=(Keywords="IsSteamChinaLauncher"), Category="Steam Integration Kit || SDK Functions || Utils")
	static bool IsSteamChinaLauncher();

	UFUNCTION(BlueprintCallable, DisplayName = "Init Filter Text", meta=(Keywords="InitFilterText"), Category="Steam Integration Kit || SDK Functions || Utils")
	static bool InitFilterText();

	UFUNCTION(BlueprintCallable, DisplayName = "Is Steam In Big Picture Mode", meta=(Keywords="IsSteamInBigPictureMode"), Category="Steam Integration Kit || SDK Functions || Utils")
	static bool IsSteamInBigPictureMode();

	UFUNCTION(BlueprintCallable, DisplayName = "Is Steam Running In VR", meta=(Keywords="IsSteamRunningInVR"), Category="Steam Integration Kit || SDK Functions || Utils")
	static bool IsSteamRunningInVR();

	UFUNCTION(BlueprintCallable, DisplayName = "Is VR Headset Streaming Enabled", meta=(Keywords="IsVRHeadsetStreamingEnabled"), Category="Steam Integration Kit || SDK Functions || Utils")
	static bool IsVRHeadsetStreamingEnabled();

	UFUNCTION(BlueprintCallable, DisplayName = "Is Steam Running On Steam Deck", meta=(Keywords="IsSteamRunningOnSteamDeck"), Category="Steam Integration Kit || SDK Functions || Utils")
	static bool IsSteamRunningOnSteamDeck();

	UFUNCTION(BlueprintCallable, DisplayName = "Set Overlay Notification Inset", meta=(Keywords="SetOverlayNotificationInset"), Category="Steam Integration Kit || SDK Functions || Utils")
	static void SetOverlayNotificationInset(int32 HorizontalInset, int32 VerticalInset);

	UFUNCTION(BlueprintCallable, DisplayName = "Set Overlay Notification Position", meta=(Keywords="SetOverlayNotificationPosition"), Category="Steam Integration Kit || SDK Functions || Utils")
	static void SetOverlayNotificationPosition(TEnumAsByte<ESIK_NotificationPosition> NotificationPosition);

	UFUNCTION(BlueprintCallable, DisplayName = "Set VR Headset Streaming Enabled", meta=(Keywords="SetVRHeadsetStreamingEnabled"), Category="Steam Integration Kit || SDK Functions || Utils")
	static void SetVRHeadsetStreamingEnabled(bool bEnabled);

	UFUNCTION(BlueprintCallable, DisplayName = "Start Vr Dashboard", meta=(Keywords="StartVrDashboard"), Category="Steam Integration Kit || SDK Functions || Utils")
	static void StartVrDashboard();

	UFUNCTION(BlueprintCallable, DisplayName = "Set Game Launcher Mode", meta=(Keywords="SetGameLauncherMode"), Category="Steam Integration Kit || SDK Functions || Utils")
	static void SetGameLauncherMode(bool bLauncherMode);
	
};
