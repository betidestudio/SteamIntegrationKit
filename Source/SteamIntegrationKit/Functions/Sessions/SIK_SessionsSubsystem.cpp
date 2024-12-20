// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_SessionsSubsystem.h"

#include "OnlineSubsystem.h"
#include "OnlineSubsystemSteam.h"
#include "OnlineSubsystemUtils.h"
#include "SIK_SharedFile.h"
#include "Interfaces/OnlineSessionInterface.h"
#if !WITH_ENGINE_STEAM
#include "OnlineSubsystemSteam/Private/OnlineSessionInterfaceSteam.h"
#endif

void USIK_SessionsSubsystem::Func_OnSessionUserInviteAccepted(bool bWasSuccessful, int ControllerId, TSharedPtr<const FUniqueNetId> UniqueNetId,
	const FOnlineSessionSearchResult& OnlineSessionSearchResult)
{
	FBlueprintSessionResult Result;
	Result.OnlineResult = OnlineSessionSearchResult;
	OnSessionUserInviteAccepted.Broadcast(bWasSuccessful, Result);
}

USIK_SessionsSubsystem::USIK_SessionsSubsystem()
{
	if(	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get(STEAM_SUBSYSTEM))
	{
		if (IOnlineSessionPtr SessionPtr = OnlineSub->GetSessionInterface())
		{
			SessionPtr->AddOnSessionUserInviteAcceptedDelegate_Handle(FOnSessionUserInviteAcceptedDelegate::CreateUObject(this, &USIK_SessionsSubsystem::Func_OnSessionUserInviteAccepted));
		}
	}
}

USIK_SessionsSubsystem::~USIK_SessionsSubsystem()
{
#if !WITH_ENGINE_STEAM
	if(	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get(STEAM_SUBSYSTEM))
	{
		if (FOnlineSubsystemSteam* SteamRef = static_cast<FOnlineSubsystemSteam*>(OnlineSub))
		{
			if(FOnlineSessionSteamPtr SteamSessionPtr = StaticCastSharedPtr<FOnlineSessionSteam>(SteamRef->GetSessionInterface()))
			{
				SteamSessionPtr->ClearOnSessionUserInviteAcceptedDelegate_Handle(OnSessionUserInviteAcceptedDelegateHandle);
			}
		}
	}
#endif
}


TArray<FSIK_CurrentSessionInfo> USIK_SessionsSubsystem::GetAllJoinedSessionsAndLobbies(UObject* Context)
{
#if !WITH_ENGINE_STEAM
	if(Context)
	{
		if(!Context->GetWorld())
		{
			return TArray<FSIK_CurrentSessionInfo>();
		}
		if(	IOnlineSubsystem* OnlineSub = Online::GetSubsystem(Context->GetWorld(), STEAM_SUBSYSTEM))
		{
			if (FOnlineSubsystemSteam* SteamRef = static_cast<FOnlineSubsystemSteam*>(OnlineSub))
			{
				if(FOnlineSessionSteamPtr SteamSessionPtr = StaticCastSharedPtr<FOnlineSessionSteam>(SteamRef->GetSessionInterface()))
				{
					TArray<FSIK_CurrentSessionInfo> SessionNames;
					for(auto& SessionEntry : SteamSessionPtr->Sessions)
					{
						SessionNames.Add(FSIK_CurrentSessionInfo(SessionEntry.SessionName.ToString(), SessionEntry.SessionInfo.Get()->ToString()));
					}
					return SessionNames;
				}
			}
		}
	}
	return TArray<FSIK_CurrentSessionInfo>();
#else
	UE_LOG(LogTemp, Error, TEXT("GetAllJoinedSessionsAndLobbies is not supported in GitHub version"));
	return TArray<FSIK_CurrentSessionInfo>();
#endif
}

bool USIK_SessionsSubsystem::IsSIKActive(UObject* Context)
{
	if (const IOnlineSubsystem* OnlineSubsystem = Online::GetSubsystem(Context->GetWorld(), STEAM_SUBSYSTEM))
	{
		return true;
	}
	return false;
}