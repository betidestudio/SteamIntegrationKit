// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_GameServerStatsLibrary.h"


bool USIK_GameServerStatsLibrary::ClearUserAchievement(FSIK_SteamId SteamId, FString AchievementName)
{
	if(!SteamGameServerStats())
	{
		return false;
	}
	return SteamGameServerStats()->ClearUserAchievement(SteamId.GetSteamID(), TCHAR_TO_ANSI(*AchievementName));
}

bool USIK_GameServerStatsLibrary::GetUserAchievement(FSIK_SteamId SteamId, FString AchievementName, bool& bAchieved)
{
	if(!SteamGameServerStats())
	{
		return false;
	}
	return SteamGameServerStats()->GetUserAchievement(SteamId.GetSteamID(), TCHAR_TO_ANSI(*AchievementName), &bAchieved);
}

bool USIK_GameServerStatsLibrary::GetIntUserStat(FSIK_SteamId SteamId, FString StatName, int32& Data)
{
	if(!SteamGameServerStats())
	{
		return false;
	}
	return SteamGameServerStats()->GetUserStat(SteamId.GetSteamID(), TCHAR_TO_ANSI(*StatName), &Data);
}

bool USIK_GameServerStatsLibrary::GetFloatUserStat(FSIK_SteamId SteamId, FString StatName, float& Data)
{
	if(!SteamGameServerStats())
	{
		return false;
	}
	return SteamGameServerStats()->GetUserStat(SteamId.GetSteamID(), TCHAR_TO_ANSI(*StatName), &Data);
}

bool USIK_GameServerStatsLibrary::RequestUserStats(FSIK_SteamId SteamId)
{
	if(!SteamGameServerStats())
	{
		return false;
	}
	SteamAPICall_t Val = SteamGameServerStats()->RequestUserStats(SteamId.GetSteamID());
	if(Val == k_uAPICallInvalid)
	{
		return false;
	}
	return true;
}

bool USIK_GameServerStatsLibrary::SetUserAchievement(FSIK_SteamId SteamId, FString AchievementName)
{
	if(!SteamGameServerStats())
	{
		return false;
	}
	return SteamGameServerStats()->SetUserAchievement(SteamId.GetSteamID(), TCHAR_TO_ANSI(*AchievementName));
}

bool USIK_GameServerStatsLibrary::SetIntUserStat(FSIK_SteamId SteamId, FString StatName, int32 Data)
{
	if(!SteamGameServerStats())
	{
		return false;
	}
	return SteamGameServerStats()->SetUserStat(SteamId.GetSteamID(), TCHAR_TO_ANSI(*StatName), Data);
}

bool USIK_GameServerStatsLibrary::SetFloatUserStat(FSIK_SteamId SteamId, FString StatName, float Data)
{
	if(!SteamGameServerStats())
	{
		return false;
	}
	return SteamGameServerStats()->SetUserStat(SteamId.GetSteamID(), TCHAR_TO_ANSI(*StatName), Data);
}

bool USIK_GameServerStatsLibrary::StoreUserStats(FSIK_SteamId SteamId)
{
	if(!SteamGameServerStats())
	{
		return false;
	}
	SteamAPICall_t Api = SteamGameServerStats()->StoreUserStats(SteamId.GetSteamID());
	if(Api == k_uAPICallInvalid)
	{
		return false;
	}
	return true;
}

bool USIK_GameServerStatsLibrary::UpdateUserAvgRateStat(FSIK_SteamId SteamId, FString StatName, float CountThisSession,
	float SessionLength)
{
	if(!SteamGameServerStats())
	{
		return false;
	}
	return SteamGameServerStats()->UpdateUserAvgRateStat(SteamId.GetSteamID(), TCHAR_TO_ANSI(*StatName), CountThisSession, SessionLength);
}
