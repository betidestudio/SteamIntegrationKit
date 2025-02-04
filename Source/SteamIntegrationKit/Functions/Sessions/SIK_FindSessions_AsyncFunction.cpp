// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_FindSessions_AsyncFunction.h"

#include "FindSessionsCallbackProxy.h"
#include "OnlineSubsystem.h"
#include "Runtime/Launch/Resources/Version.h"
#include "OnlineSubsystemUtils.h"
#include "Online/OnlineSessionNames.h"

USIK_FindSessions_AsyncFunction* USIK_FindSessions_AsyncFunction::FindSIKSessions(
	TMap<FName, FSIKAttribute> SessionSettings, ESMatchType MatchType, int32 MaxResults, bool bLanSearch, bool bEmptyServerOnly, bool bSecureServerOnly)

{
	USIK_FindSessions_AsyncFunction* Ueik_FindSessionObject= NewObject<USIK_FindSessions_AsyncFunction>();
	Ueik_FindSessionObject->E_MatchType = MatchType;
	Ueik_FindSessionObject->SessionSettings = SessionSettings;
	Ueik_FindSessionObject->B_bLanSearch = bLanSearch;
	Ueik_FindSessionObject->I_MaxResults = MaxResults;
	Ueik_FindSessionObject->B_bEmptyServerOnly = bEmptyServerOnly;
	Ueik_FindSessionObject->B_bSecureServerOnly = bSecureServerOnly;
	return Ueik_FindSessionObject;
}

void USIK_FindSessions_AsyncFunction::Activate()
{
	FindSession();
	Super::Activate();
}

void USIK_FindSessions_AsyncFunction::FindSession()
{
	if(const IOnlineSubsystem *SubsystemRef = Online::GetSubsystem(GetWorld(), STEAM_SUBSYSTEM))
	{
		if(const IOnlineSessionPtr SessionPtrRef = SubsystemRef->GetSessionInterface())
		{
			SessionSearch = MakeShareable(new FOnlineSessionSearch());
			SessionSearch->QuerySettings.SearchParams.Empty();
			SessionSearch->bIsLanQuery = B_bLanSearch;
			SessionSearch->MaxSearchResults = I_MaxResults;
			if(E_MatchType == ESMatchType::MT_Lobby)
			{
#if ENGINE_MINOR_VERSION >= 5
				SessionSearch->QuerySettings.Set("SEARCH_PRESENCE", true, EOnlineComparisonOp::Equals);
#else
				SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
#endif
			}
			if(B_bEmptyServerOnly)
			{
				SessionSearch->QuerySettings.Set(SEARCH_EMPTY_SERVERS_ONLY, true, EOnlineComparisonOp::Equals);
			}
			if(B_bSecureServerOnly)
			{
				SessionSearch->QuerySettings.Set(SEARCH_SECURE_SERVERS_ONLY, true, EOnlineComparisonOp::Equals);
			}
			
			for(auto& Elem : SessionSettings)
			{
				SessionSearch->QuerySettings.SearchParams.Add(Elem.Key, Elem.Value.GetVariantData());
			}
			SessionPtrRef->OnFindSessionsCompleteDelegates.AddUObject(this, &USIK_FindSessions_AsyncFunction::OnFindSessionCompleted);
			SessionPtrRef->FindSessions(0,SessionSearch.ToSharedRef());
		}
		else
		{
			if(bDelegateCalled)
			{
				return;
			}
			OnFail.Broadcast(TArray<FSSessionFindStruct>());
			SetReadyToDestroy();
			MarkAsGarbage();
		}
	}
	else
	{
		if(bDelegateCalled)
		{
			return;
		}
		OnFail.Broadcast(TArray<FSSessionFindStruct>());
		SetReadyToDestroy();
MarkAsGarbage();
	}
}

void USIK_FindSessions_AsyncFunction::OnFindSessionCompleted(bool bWasSuccess)
{
	if(!bWasSuccess)
	{
		if(bDelegateCalled)
		{
			return;
		}
		OnFail.Broadcast(TArray<FSSessionFindStruct>());
		bDelegateCalled = true;
		SetReadyToDestroy();
		MarkAsGarbage();
	}
	else
	{
		if (const IOnlineSubsystem* OnlineSub = Online::GetSubsystem(GetWorld(), STEAM_SUBSYSTEM))
		{
			TArray<FSSessionFindStruct> SessionResult_Array;
			IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
			if (Sessions.IsValid())
			{
				if (SessionSearch->SearchResults.Num() > 0)
				{
					for (int32 SearchIdx = 0; SearchIdx < SessionSearch->SearchResults.Num(); SearchIdx++)
					{
						FBlueprintSessionResult SessionResult;
						SessionResult.OnlineResult = SessionSearch->SearchResults[SearchIdx];
						FOnlineSessionSettings LocalSessionSettings = SessionResult.OnlineResult.Session.SessionSettings;
						TMap<FName, FString> AllSettingsWithData;
						TMap<FName, FOnlineSessionSetting>::TIterator It(LocalSessionSettings.Settings);

						TMap<FString, FSIKAttribute> LocalArraySettings;
						while (It)
						{
							const FName& SettingName = It.Key();
							const FOnlineSessionSetting& Setting = It.Value();
							LocalArraySettings.Add(*SettingName.ToString(), Setting.Data);
							++It;
						}

						bool IsServer = LocalArraySettings.Contains("IsDedicatedServer") ? true : false;
						FSSessionFindStruct LocalStruct;
						LocalStruct.SessionName = "GameSession";
						LocalStruct.CurrentNumberOfPlayers = (SessionResult.OnlineResult.Session.SessionSettings.NumPublicConnections + SessionResult.OnlineResult.Session.SessionSettings.NumPrivateConnections) - (SessionResult.OnlineResult.Session.NumOpenPublicConnections + SessionResult.OnlineResult.Session.NumOpenPrivateConnections);
						LocalStruct.MaxNumberOfPlayers = SessionResult.OnlineResult.Session.SessionSettings.NumPublicConnections + SessionResult.OnlineResult.Session.SessionSettings.NumPrivateConnections;
						LocalStruct.SessionResult = SessionResult;
						LocalStruct.SessionSettings = LocalArraySettings;
						LocalStruct.bIsDedicatedServer = IsServer;
						SessionResult_Array.Add(LocalStruct);
					}
				}
			}
			if (bDelegateCalled)
			{
				return;
			}
			bDelegateCalled = true;
			OnSuccess.Broadcast(SessionResult_Array);
			SetReadyToDestroy();
			MarkAsGarbage();
		}
	}
}
