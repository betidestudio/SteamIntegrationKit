// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SIK_SharedFile.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SIK_UtilsSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGamepadTextInputDismissed, bool, bSubmitted, int32, nSubmittedText);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnIPCountry);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLowBatteryPower, int32, nMinutesBatteryLeft);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAppResumingFromSuspend);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSteamShutdown);

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_UtilsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	USIK_UtilsSubsystem();
	~USIK_UtilsSubsystem();
	
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | Utils")
	FOnGamepadTextInputDismissed OnGamepadTextInputDismissed;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | Utils")
	FOnIPCountry OnIPCountry;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | Utils")
	FOnLowBatteryPower OnLowBatteryPower;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | Utils")
	FOnAppResumingFromSuspend OnAppResumingFromSuspend;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | Utils")
	FOnSteamShutdown OnSteamShutdown;
	
private:
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	STEAM_CALLBACK_MANUAL(USIK_UtilsSubsystem, OnGamepadTextInputDismissedCallbck, GamepadTextInputDismissed_t, m_CallbackGamepadTextInputDismissed);
	STEAM_CALLBACK_MANUAL(USIK_UtilsSubsystem, OnIPCountryCallbck, IPCountry_t, m_CallbackIPCountry);
	STEAM_CALLBACK_MANUAL(USIK_UtilsSubsystem, OnLowBatteryPowerCallbck, LowBatteryPower_t, m_CallbackLowBatteryPower);
	STEAM_CALLBACK_MANUAL(USIK_UtilsSubsystem, OnAppResumingFromSuspendCallbck, AppResumingFromSuspend_t, m_CallbackAppResumingFromSuspend);
	STEAM_CALLBACK_MANUAL(USIK_UtilsSubsystem, OnSteamShutdownCallbck, SteamShutdown_t, m_CallbackSteamShutdown);
#endif
};
