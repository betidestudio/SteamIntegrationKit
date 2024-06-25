// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_GameServerStatsSubsystem.h"


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