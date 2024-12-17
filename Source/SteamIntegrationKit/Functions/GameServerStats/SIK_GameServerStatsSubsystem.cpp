// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_GameServerStatsSubsystem.h"


USIK_GameServerStatsSubsystem::USIK_GameServerStatsSubsystem()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	m_CallbackGSStatsReceived.Register(this, &USIK_GameServerStatsSubsystem::OnGSStatsReceivedCallbck);
	m_CallbackGSStatsStored.Register(this, &USIK_GameServerStatsSubsystem::OnGSStatsStoredCallbck);
	m_CallbackGSStatsUnloaded.Register(this, &USIK_GameServerStatsSubsystem::OnGSStatsUnloadedCallbck);

	if (IsRunningDedicatedServer())
	{
		m_CallbackGSStatsReceived.SetGameserverFlag();
		m_CallbackGSStatsStored.SetGameserverFlag();
		m_CallbackGSStatsUnloaded.SetGameserverFlag();
	}
#endif
}

USIK_GameServerStatsSubsystem::~USIK_GameServerStatsSubsystem()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	m_CallbackGSStatsReceived.Unregister();
	m_CallbackGSStatsStored.Unregister();
	m_CallbackGSStatsUnloaded.Unregister();
#endif
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)

void USIK_GameServerStatsSubsystem::OnGSStatsReceivedCallbck(GSStatsReceived_t* pCallback)
{
	FSIK_SteamId SteamID = pCallback->m_steamIDUser;
	TEnumAsByte<ESIK_Result> Result = static_cast<ESIK_Result>(pCallback->m_eResult);
	OnGSStatsReceived.Broadcast(SteamID, Result);
}

void USIK_GameServerStatsSubsystem::OnGSStatsStoredCallbck(GSStatsStored_t* pCallback)
{
	FSIK_SteamId SteamID = pCallback->m_steamIDUser;
	TEnumAsByte<ESIK_Result> Result = static_cast<ESIK_Result>(pCallback->m_eResult);
	OnGSStatsStored.Broadcast(SteamID, Result);
}

void USIK_GameServerStatsSubsystem::OnGSStatsUnloadedCallbck(GSStatsUnloaded_t* pCallback)
{
	FSIK_SteamId SteamID = pCallback->m_steamIDUser;
	OnGSStatsUnloaded.Broadcast(SteamID);
}
#endif