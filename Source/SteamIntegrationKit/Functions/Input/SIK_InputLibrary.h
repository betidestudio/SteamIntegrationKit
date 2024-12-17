// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SIK_SharedFile.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SIK_InputLibrary.generated.h"

/**
 * 
 */
UCLASS()
class STEAMINTEGRATIONKIT_API USIK_InputLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/*
	*Reconfigure the controller to use the specified action set (i.e. "Menu", "Walk", or "Drive").

	This is cheap, and can be safely called repeatedly. It's often easier to repeatedly call it in your state loops, instead of trying to place it in all of your state transitions.
	*/
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Input")
	static void ActivateActionSet(FSIK_InputHandle InputHandle, FSIK_InputActionSetHandle ActionSetHandle);

	//Reconfigure the controller to use the specified action set layer.
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Input")
	static void ActivateActionSetLayer(FSIK_InputHandle InputHandle, FSIK_InputActionSetHandle ActionSetLayerHandle);

	//Reconfigure the controller to stop using the specified action set layer.
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Input")
	static void DeactivateActionSetLayer(FSIK_InputHandle InputHandle, FSIK_InputActionSetHandle ActionSetLayerHandle);

	//Reconfigure the controller to stop using all action set layers.
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Input")
	static void DeactivateAllActionSetLayers(FSIK_InputHandle InputHandle);

	//Fill an array with all of the currently active action set layers for a specified controller handle.
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Input")
	static int64 GetActiveActionSetLayers(FSIK_InputHandle InputHandle, TArray<FSIK_InputActionSetHandle>& ActionSetHandles);

	//Lookup the handle for an Action Set. Best to do this once on startup, and store the handles for all future API calls
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Input")
	static FSIK_InputActionSetHandle GetActionSetHandle(FString ActionSetName);

	//Returns the current state of the supplied analog game action.
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Input")
	static FSIK_InputAnalogActionData GetAnalogActionData(FSIK_InputHandle InputHandle, FSIK_InputAnalogActionHandle AnalogActionHandle);

	//Get the handle of the specified Analog action.
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Input")
	static FSIK_InputAnalogActionHandle GetAnalogActionHandle(FString AnalogActionName);

	//Get the origin(s) for an analog action within an action set by filling originsOut with EInputActionOrigin handles. Use this to display the appropriate on-screen prompt for the action
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Input")
	static int64 GetAnalogActionOrigins(FSIK_InputHandle InputHandle, FSIK_InputActionSetHandle ActionSetHandle, FSIK_InputAnalogActionHandle AnalogActionHandle, TArray<TEnumAsByte<ESIK_InputActionOrigin>>& OriginsOut);

	//Enumerates currently connected controllers by filling handlesOut with controller handles.
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Input")
	static int64 GetConnectedControllers(TArray<FSIK_InputHandle>& HandlesOut);

	//Returns the associated controller handle for the specified emulated gamepad. Can be used with GetInputTypeForHandle to determine the type of controller using Steam Input Gamepad Emulation.
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Input")
	static FSIK_InputHandle GetControllerForGamepadIndex(int32 Index);

	//Get the currently active action set for the specified controller.
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Input")
	static FSIK_InputActionSetHandle GetCurrentActionSet(FSIK_InputHandle InputHandle);

	//Returns the current state of the supplied digital game action.
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Input")
	static FSIK_InputDigitalActionData GetDigitalActionData(FSIK_InputHandle InputHandle, FSIK_InputDigitalActionHandle DigitalActionHandle);

	//Get the handle of the specified digital action.
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Input")
	static FSIK_InputDigitalActionHandle GetDigitalActionHandle(FString DigitalActionName);

	//Get the origin(s) for a digital action within an action set by filling originsOut with EInputActionOrigin handles. Use this to display the appropriate on-screen prompt for the action
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Input")
	static int64 GetDigitalActionOrigins(FSIK_InputHandle InputHandle, FSIK_InputActionSetHandle ActionSetHandle, FSIK_InputDigitalActionHandle DigitalActionHandle, TArray<TEnumAsByte<ESIK_InputActionOrigin>>& OriginsOut);

	//Returns the associated gamepad index for the specified controller, if emulating a gamepad.
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Input")
	static int64 GetGamepadIndexForController(FSIK_InputHandle InputHandle);

	//Get a local path to art for on-screen glyph for a particular origin.
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Input")
	static FString GetGlyphForActionOrigin(TEnumAsByte<ESIK_InputActionOrigin> Origin);
	
	//Returns the input type (device model) for the specified controller. This tells you if a given controller is a Steam controller, Xbox 360 controller, PS4 controller, etc.
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Input")
	static ESIK_SteamInputType GetInputTypeForHandle(FSIK_InputHandle InputHandle);
	
	//Returns raw motion data for the specified controller.
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Input")
	static FSIK_InputMotionData GetMotionData(FSIK_InputHandle InputHandle);

	//Returns a localized string (from Steam's language setting) for the specified origin.
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Input")
	static FString GetStringForActionOrigin(TEnumAsByte<ESIK_InputActionOrigin> Origin);

	//Must be called when starting use of the ISteamInput interface.
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Input")
	static bool Init(bool bExplicitlyCallRunFrame);

	//Synchronize API state with the latest Steam Controller inputs available. This is performed automatically by SteamAPI_RunCallbacks, but for the absolute lowest possible latency, you can call this directly before reading controller state.
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Input")
	static void RunFrame();
	 
	//Set the trigger effect for a DualSense controller.
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Input")
	static void SetDualSenseTriggerEffect(FSIK_InputHandle InputHandle, FSIK_ScePadTriggerEffectCommand L2, FSIK_ScePadTriggerEffectCommand R2);

	//Set the controller LED color on supported controllers.
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Input")
	static void SetLEDColor(FSIK_InputHandle InputHandle, FLinearColor Color, TEnumAsByte<ESIK_SteamControllerLEDFlag> LEDFlag);


	//Invokes the Steam overlay and brings up the binding screen.
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Input")
	static bool ShowBindingPanel(FSIK_InputHandle InputHandle);

	//Must be called when ending use of the ISteamInput interface.
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Input")
	static bool Shutdown();

	//Stops the momentum of an analog action (where applicable, i.e. a touchpad w/ virtual trackball settings).
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Input")
	static void StopAnalogActionMomentum(FSIK_InputHandle InputHandle, FSIK_InputAnalogActionHandle AnalogActionHandle);

	//Triggers a (low-level) haptic pulse on supported controllers.
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Input")
	static void TriggerHapticPulse(FSIK_InputHandle InputHandle, TEnumAsByte<ESIK_SteamControllerPad> TargetPad, uint8 DurationMicroSec);

	//Triggers a repeated haptic pulse on supported controllers.
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Input")
	static void TriggerRepeatedHapticPulse(FSIK_InputHandle InputHandle, TEnumAsByte<ESIK_SteamControllerPad> TargetPad, uint8 DurationMicroSec, uint8 OffMicroSec, uint8 Repeat, uint8 Flags);

	//Trigger a vibration event on supported controllers.
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Input")
	static void TriggerVibration(FSIK_InputHandle InputHandle, uint8 LeftSpeed, uint8 RightSpeed);

	//Trigger a vibration event on supported controllers, including Xbox Impulse Trigger motor values.
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Input")
	static void TriggerVibrationExtended(FSIK_InputHandle InputHandle, uint8 LeftSpeed, uint8 RightSpeed, uint8 LeftTriggerSpeed, uint8 RightTriggerSpeed);

	//Get an action origin that you can use in your glyph look up table or passed into GetGlyphForActionOrigin or GetStringForActionOrigin
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Input")
	static TEnumAsByte<ESIK_InputActionOrigin> GetActionOriginFromXboxOrigin(FSIK_InputHandle InputHandle, TEnumAsByte<ESIK_XboxOrigin> XboxOrigin);

	//Get the equivalent origin for a given controller type or the closest controller type that existed in the SDK you built into your game if eDestinationInputType is k_ESteamInputType_Unknown. This action origin can be used in your glyph look up table or passed into GetGlyphForActionOrigin or GetStringForActionOrigin
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Input")
	static TEnumAsByte<ESIK_InputActionOrigin> TranslateActionOrigin(TEnumAsByte<ESIK_SteamInputType> eDestinationInputType, TEnumAsByte<ESIK_InputActionOrigin> eSourceActionOrigin);

	//Gets the major and minor device binding revisions for Steam Input API configurations. Major revisions are to be used when changing the number of action sets or otherwise reworking configurations to the degree that older configurations are no longer usable. When a user's binding disagrees with the major revision of the current official configuration Steam will forcibly update the user to the new configuration. New configurations will need to be made for every controller when updating the major revision. Minor revisions are for small changes such as adding a new optional action or updating localization in the configuration. When updating the minor revision you generally can update a single configuration and check the "Use Action Block" to apply the action block changes to the other configurations.
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Input")
	static bool GetDeviceBindingRevision(FSIK_InputHandle InputHandle, int32& Major, int32& Minor);

	//Get the Steam Remote Play session ID associated with a device, or 0 if there is no session associated with it. See isteamremoteplay.h for more information on Steam Remote Play sessions.
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Input")
	static int64 GetRemotePlaySessionID(FSIK_InputHandle InputHandle);

};
