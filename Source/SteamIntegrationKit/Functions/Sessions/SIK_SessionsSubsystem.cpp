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
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
#include <isteammatchmaking.h>
#include <isteamuser.h>
#include <steam_api_common.h>
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
	TArray<FSIK_CurrentSessionInfo> SessionNames;
	
	if(Context)
	{
		if(!Context->GetWorld())
		{
			return SessionNames;
		}
		if(	IOnlineSubsystem* OnlineSub = Online::GetSubsystem(Context->GetWorld(), STEAM_SUBSYSTEM))
		{
			if (FOnlineSubsystemSteam* SteamRef = static_cast<FOnlineSubsystemSteam*>(OnlineSub))
			{
				if(FOnlineSessionSteamPtr SteamSessionPtr = StaticCastSharedPtr<FOnlineSessionSteam>(SteamRef->GetSessionInterface()))
				{
					// First, add all sessions from the Sessions array (SIK-created lobbies)
					for(auto& SessionEntry : SteamSessionPtr->Sessions)
					{
						if(SessionEntry.SessionInfo.IsValid())
						{
							FOnlineSessionInfoSteam* SessionInfo = (FOnlineSessionInfoSteam*)SessionEntry.SessionInfo.Get();
							if(SessionInfo->SessionId->IsValid())
							{
								// Extract the Steam ID from SessionId (FUniqueNetIdSteam contains CSteamID)
								FString SessionIdString = SessionInfo->SessionId->ToString();
								FSIK_SteamId LobbySteamId(SessionIdString);
								SessionNames.Add(FSIK_CurrentSessionInfo(SessionEntry.SessionName.ToString(), LobbySteamId));
							}
						}
					}
					
					// Then, query Steam directly for all lobbies the user is a member of
					// This includes lobbies created via SDK methods (SteamMatchmaking()->CreateLobby)
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
					if(SteamMatchmaking())
					{
						// Steam allows up to 64 lobbies to be tracked
						// Iterate through indices and check if we're a member
						for(int32 LobbyIdx = 0; LobbyIdx < 64; LobbyIdx++)
						{
							CSteamID LobbyID = SteamMatchmaking()->GetLobbyByIndex(LobbyIdx);
							if(LobbyID.IsValid())
							{
								// Verify we're actually a member by checking if we can access lobby members
								int32 NumMembers = SteamMatchmaking()->GetNumLobbyMembers(LobbyID);
								if(NumMembers > 0)
								{
									// Check if we're actually in this lobby by looking for our Steam ID in members
									CSteamID OurSteamID = SteamUser()->GetSteamID();
									bool bIsMember = false;
									for(int32 MemberIdx = 0; MemberIdx < NumMembers; MemberIdx++)
									{
										CSteamID MemberID = SteamMatchmaking()->GetLobbyMemberByIndex(LobbyID, MemberIdx);
										if(MemberID == OurSteamID)
										{
											bIsMember = true;
											break;
										}
									}
									
									if(bIsMember)
									{
										// Check if this lobby is already in our SessionNames list
										FSIK_SteamId LobbySteamId = FSIK_SteamId(LobbyID);
										bool bAlreadyAdded = false;
										for(const FSIK_CurrentSessionInfo& ExistingSession : SessionNames)
										{
											// Compare lobby IDs to avoid duplicates
											FString ExistingLobbyIdString = FString::Printf(TEXT("%llu"), ExistingSession.LobbyId.Result);
											FString NewLobbyIdString = FString::Printf(TEXT("%llu"), LobbySteamId.Result);
											if(ExistingLobbyIdString == NewLobbyIdString)
											{
												bAlreadyAdded = true;
												break;
											}
										}
										
										// Add if not already in the list
										if(!bAlreadyAdded)
										{
											SessionNames.Add(FSIK_CurrentSessionInfo(TEXT("SDK_Lobby"), LobbySteamId));
										}
									}
								}
							}
							else
							{
								// No more lobbies at this index or beyond
								break;
							}
						}
					}
#endif
					
					return SessionNames;
				}
			}
		}
	}
	return SessionNames;
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