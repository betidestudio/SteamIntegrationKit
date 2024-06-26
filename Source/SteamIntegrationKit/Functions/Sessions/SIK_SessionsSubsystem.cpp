// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_SessionsSubsystem.h"

#include "OnlineSubsystem.h"
#include "OnlineSubsystemSteam.h"
#include "SIK_SharedFile.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSubsystemSteam/Private/OnlineSessionInterfaceSteam.h"

TArray<FEIK_CurrentSessionInfo> USIK_SessionsSubsystem::GetAllJoinedSessionsAndLobbies(UObject* Context)
{
	if(Context)
	{
		if(!Context->GetWorld())
		{
			return TArray<FEIK_CurrentSessionInfo>();
		}
		if(	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get())
		{
			if (FOnlineSubsystemSteam* SteamRef = static_cast<FOnlineSubsystemSteam*>(OnlineSub))
			{
				if(FOnlineSessionSteamPtr SteamSessionPtr = StaticCastSharedPtr<FOnlineSessionSteam>(SteamRef->GetSessionInterface()))
				{
					TArray<FEIK_CurrentSessionInfo> SessionNames;
					for(auto& SessionEntry : SteamSessionPtr->Sessions)
					{
						SessionNames.Add(FEIK_CurrentSessionInfo(SessionEntry.SessionName.ToString(), SessionEntry.SessionInfo.Get()->ToString()));
					}
					return SessionNames;
				}
			}
		}
	}
	return TArray<FEIK_CurrentSessionInfo>();
}

bool USIK_SessionsSubsystem::IsSIKActive(UObject* Context)
{
	if (const IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get())
	{
		if(OnlineSubsystem->GetSubsystemName() == STEAM_SUBSYSTEM)
		{
			return true;
		}
	}
	if(const IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get(STEAM_SUBSYSTEM))
	{
		return true;
	}
	return false;
}