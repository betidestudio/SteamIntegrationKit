// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SIK_SharedFile.h"
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

	UFUNCTION(BlueprintCallable, DisplayName = "Is Controller Connected", meta = (Keywords = "IsControllerConnected"), Category = "Steam Integration Kit || SDK Functions || Inputs")
	static bool IsControllerConnected();

	UFUNCTION(BlueprintCallable, DisplayName = "Open Steam Keyboard", meta = (Keywords = "OpenSteamKeyboard"), Category = "Steam Integration Kit || SDK Functions || Utils")
	static bool OpenSteamKeyboard(int32 KeyboardMode, int32 TextFieldXPosition, int32 TextFieldYPosition, int32 TextFieldWidth, int32 TextFieldHeight);
	
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

	//Thanks to @marown for fixing this function
	UFUNCTION(BlueprintCallable, DisplayName = "Get Image RGBA", meta=(Keywords="GetImageRGBA"), Category="Steam Integration Kit || SDK Functions || Utils")
	static bool GetImageRGBA(int32 Image, TArray<FColor>& OutData, int32& OutWidth, int32& OutHeight);

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

	UFUNCTION(BlueprintCallable, DisplayName = "Filter Text", meta=(Keywords="FilterText", ToolTip="Filters text using Steam's content filtering system for Workshop content, chat, and names"), Category="Steam Integration Kit || SDK Functions || Utils")
	static int32 FilterText(TEnumAsByte<ESIK_TextFilteringContext> Context, FSIK_SteamId SourceSteamId, const FString& InputMessage, FString& OutFilteredText);

	UFUNCTION(BlueprintCallable, DisplayName = "Save Game Object to Byte Array", meta=(Keywords="SaveGameToByteArray", ToolTip="Converts a Save Game Object to Byte Array for Steam Cloud storage"), Category="Steam Integration Kit || Helper Functions || Utils")
	static TArray<uint8> SaveGameObjectToByteArray(USaveGame* SaveGameObject);

	UFUNCTION(BlueprintCallable, DisplayName = "Byte Array to Save Game Object", meta=(Keywords="ByteArrayToSaveGame", ToolTip="Converts Byte Array back to Save Game Object from Steam Cloud data"), Category="Steam Integration Kit || Helper Functions || Utils")
	static USaveGame* ByteArrayToSaveGameObject(const TArray<uint8>& Data, TSubclassOf<USaveGame> SaveGameClass);

	// UGC Validation Utilities
	UFUNCTION(BlueprintCallable, DisplayName = "Is Valid UGC Tag", meta=(Keywords="IsValidUGCTag", ToolTip="Checks if a UGC tag meets Steam's requirements: ≤255 chars, no commas, printable characters only"), Category="Steam Integration Kit || Helper Functions || UGC")
	static bool IsValidUGCTag(const FString& TagName);

	UFUNCTION(BlueprintCallable, DisplayName = "Sanitize UGC Tag", meta=(Keywords="SanitizeUGCTag", ToolTip="Cleans a UGC tag by removing commas, non-printable chars, and truncating to 255 chars"), Category="Steam Integration Kit || Helper Functions || UGC")
	static FString SanitizeUGCTag(const FString& TagName);

	UFUNCTION(BlueprintCallable, DisplayName = "Validate UGC Tags Array", meta=(Keywords="ValidateUGCTagsArray", ToolTip="Validates an array of UGC tags and returns invalid ones for debugging"), Category="Steam Integration Kit || Helper Functions || UGC")
	static bool ValidateUGCTagsArray(const TArray<FString>& Tags, TArray<FString>& InvalidTags);

	UFUNCTION(BlueprintCallable, DisplayName = "Sanitize UGC Tags Array", meta=(Keywords="SanitizeUGCTagsArray", ToolTip="Sanitizes an array of UGC tags, removing invalid ones and cleaning valid ones"), Category="Steam Integration Kit || Helper Functions || UGC")
	static TArray<FString> SanitizeUGCTagsArray(const TArray<FString>& Tags);

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

	UFUNCTION(BlueprintCallable, DisplayName = "Show Gamepad Text Input", meta=(Keywords="ShowGamepadTextInput"), Category="Steam Integration Kit || SDK Functions || Utils")
	static bool ShowGamepadTextInput(TEnumAsByte<ESIK_EGamepadTextInputMode> InputMode, TEnumAsByte<ESIK_EGamepadTextInputLineMode> LineInputMode, const FString& Description, int32 CharMax, const FString& ExistingText);

	UFUNCTION(BlueprintCallable, DisplayName = "Show Floating Gamepad Text Input", meta=(Keywords="ShowFloatingGamepadTextInput"), Category="Steam Integration Kit || SDK Functions || Utils")
	static bool ShowFloatingGamepadTextInput(TEnumAsByte<ESIK_EFloatingGamepadTextInputMode> KeyboardMode, int32 TextFieldXPosition, int32 TextFieldYPosition, int32 TextFieldWidth, int32 TextFieldHeight);


	UFUNCTION(BlueprintCallable, DisplayName = "Start Vr Dashboard", meta=(Keywords="StartVrDashboard"), Category="Steam Integration Kit || SDK Functions || Utils")
	static void StartVrDashboard();

	UFUNCTION(BlueprintCallable, DisplayName = "Set Game Launcher Mode", meta=(Keywords="SetGameLauncherMode"), Category="Steam Integration Kit || SDK Functions || Utils")
	static void SetGameLauncherMode(bool bLauncherMode);
	
};
