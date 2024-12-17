// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_UtilsSubsystem.h"

#include "SIK_SharedFile.h"
#include "Async/Async.h"

USIK_UtilsSubsystem::USIK_UtilsSubsystem()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	m_CallbackGamepadTextInputDismissed.Register(this, &USIK_UtilsSubsystem::OnGamepadTextInputDismissedCallbck);
	m_CallbackIPCountry.Register(this, &USIK_UtilsSubsystem::OnIPCountryCallbck);
	m_CallbackLowBatteryPower.Register(this, &USIK_UtilsSubsystem::OnLowBatteryPowerCallbck);
	m_CallbackAppResumingFromSuspend.Register(this, &USIK_UtilsSubsystem::OnAppResumingFromSuspendCallbck);
	m_CallbackSteamShutdown.Register(this, &USIK_UtilsSubsystem::OnSteamShutdownCallbck);

 	if(IsRunningDedicatedServer())
 	{
	m_CallbackGamepadTextInputDismissed.SetGameserverFlag();
	m_CallbackIPCountry.SetGameserverFlag();
	m_CallbackLowBatteryPower.SetGameserverFlag();
	m_CallbackAppResumingFromSuspend.SetGameserverFlag();
	m_CallbackSteamShutdown.SetGameserverFlag();
}
#endif
}

USIK_UtilsSubsystem::~USIK_UtilsSubsystem()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	m_CallbackGamepadTextInputDismissed.SetGameserverFlag();
	m_CallbackIPCountry.SetGameserverFlag();
	m_CallbackLowBatteryPower.SetGameserverFlag();
	m_CallbackAppResumingFromSuspend.SetGameserverFlag();
	m_CallbackSteamShutdown.SetGameserverFlag();
#endif
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)

void USIK_UtilsSubsystem::OnGamepadTextInputDismissedCallbck(GamepadTextInputDismissed_t* pCallback)
{
	auto Param = *pCallback;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnGamepadTextInputDismissed.Broadcast(Param.m_bSubmitted, Param.m_unSubmittedText);
	});
}

void USIK_UtilsSubsystem::OnIPCountryCallbck(IPCountry_t* pCallback)
{
	auto Param = *pCallback;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
		{
			OnIPCountry.Broadcast();
		});
}

void USIK_UtilsSubsystem::OnLowBatteryPowerCallbck(LowBatteryPower_t* pCallback)
{
	auto Param = *pCallback;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
		{
			OnLowBatteryPower.Broadcast(Param.m_nMinutesBatteryLeft);
		});
}

void USIK_UtilsSubsystem::OnAppResumingFromSuspendCallbck(AppResumingFromSuspend_t* pCallback)
{
	auto Param = *pCallback;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
		{
			OnAppResumingFromSuspend.Broadcast();
		});
}

void USIK_UtilsSubsystem::OnSteamShutdownCallbck(SteamShutdown_t* pCallback)
{
	auto Param = *pCallback;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
		{
			OnSteamShutdown.Broadcast();
		});
}

#endif