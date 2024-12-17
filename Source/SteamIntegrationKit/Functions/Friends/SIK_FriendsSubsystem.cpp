// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_FriendsSubsystem.h"
#include "Async/Async.h"


USIK_FriendsSubsystem::USIK_FriendsSubsystem()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		m_CallbackAvatarImageLoaded.Register(this, &USIK_FriendsSubsystem::OnAvatarImageLoadedCallback);
		m_CallbackFriendRichPresenceUpdate.Register(this, &USIK_FriendsSubsystem::OnFriendRichPresenceUpdateCallback);
		m_CallbackDownloadClanActivityCountsResult.Register(this, &USIK_FriendsSubsystem::OnDownloadClanActivityCountsResultCallback);
		m_CallbackFriendEnumerateFollowingList.Register(this, &USIK_FriendsSubsystem::OnFriendEnumerateFollowingListCallback);
		m_CallbackFriendsGetFollowerCount.Register(this, &USIK_FriendsSubsystem::OnFriendsGetFollowerCountCallback);
		m_CallbackFriendsIsFollowing.Register(this, &USIK_FriendsSubsystem::OnFriendsIsFollowingCallback);
		m_CallbackGameConnectedChatJoin.Register(this, &USIK_FriendsSubsystem::OnGameConnectedChatJoinCallback);
		m_CallbackGameConnectedChatLeave.Register(this, &USIK_FriendsSubsystem::OnGameConnectedChatLeaveCallback);
		m_CallbackGameConnectedClanChatMsg.Register(this, &USIK_FriendsSubsystem::OnGameConnectedClanChatMsgCallback);
		m_CallbackGameConnectedFriendChatMsg.Register(this, &USIK_FriendsSubsystem::OnGameConnectedFriendChatMsgCallback);
		m_CallbackGameLobbyJoinRequested.Register(this, &USIK_FriendsSubsystem::OnGameLobbyJoinRequestedCallback);
		m_CallbackGameOverlayActivated.Register(this, &USIK_FriendsSubsystem::OnGameOverlayActivatedCallback);
		m_CallbackGameRichPresenceJoinRequested.Register(this, &USIK_FriendsSubsystem::OnGameRichPresenceJoinRequestedCallback);
		m_CallbackGameServerChangeRequested.Register(this, &USIK_FriendsSubsystem::OnGameServerChangeRequestedCallback);
		m_CallbackJoinClanChatRoomCompletionResult.Register(this, &USIK_FriendsSubsystem::OnJoinClanChatRoomCompletionResultCallback);
		m_CallbackPersonaStateChange.Register(this, &USIK_FriendsSubsystem::OnPersonaStateChangeCallback);
		m_CallbackSetPersonaNameResponse.Register(this, &USIK_FriendsSubsystem::OnSetPersonaNameResponseCallback);
		m_CallbackClanOfficerList.Register(this, &USIK_FriendsSubsystem::OnClanOfficerListCallback);

		if(IsRunningDedicatedServer())
		{
			m_CallbackAvatarImageLoaded.SetGameserverFlag();
			m_CallbackFriendRichPresenceUpdate.SetGameserverFlag();
			m_CallbackDownloadClanActivityCountsResult.SetGameserverFlag();
			m_CallbackFriendEnumerateFollowingList.SetGameserverFlag();
			m_CallbackFriendsGetFollowerCount.SetGameserverFlag();
			m_CallbackFriendsIsFollowing.SetGameserverFlag();
			m_CallbackGameConnectedChatJoin.SetGameserverFlag();
			m_CallbackGameConnectedChatLeave.SetGameserverFlag();
			m_CallbackGameConnectedClanChatMsg.SetGameserverFlag();
			m_CallbackGameConnectedFriendChatMsg.SetGameserverFlag();
			m_CallbackGameLobbyJoinRequested.SetGameserverFlag();
			m_CallbackGameOverlayActivated.SetGameserverFlag();
			m_CallbackGameRichPresenceJoinRequested.SetGameserverFlag();
			m_CallbackGameServerChangeRequested.SetGameserverFlag();
			m_CallbackJoinClanChatRoomCompletionResult.SetGameserverFlag();
			m_CallbackPersonaStateChange.SetGameserverFlag();
			m_CallbackSetPersonaNameResponse.SetGameserverFlag();
			m_CallbackClanOfficerList.SetGameserverFlag();
		}
	}
#endif
}

USIK_FriendsSubsystem::~USIK_FriendsSubsystem()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	m_CallbackAvatarImageLoaded.Unregister();
	m_CallbackFriendRichPresenceUpdate.Unregister();
	m_CallbackDownloadClanActivityCountsResult.Unregister();
	m_CallbackFriendEnumerateFollowingList.Unregister();
	m_CallbackFriendsGetFollowerCount.Unregister();
	m_CallbackFriendsIsFollowing.Unregister();
	m_CallbackGameConnectedChatJoin.Unregister();
	m_CallbackGameConnectedChatLeave.Unregister();
	m_CallbackGameConnectedClanChatMsg.Unregister();
	m_CallbackGameConnectedFriendChatMsg.Unregister();
	m_CallbackGameLobbyJoinRequested.Unregister();
	m_CallbackGameOverlayActivated.Unregister();
	m_CallbackGameRichPresenceJoinRequested.Unregister();
	m_CallbackGameServerChangeRequested.Unregister();
	m_CallbackJoinClanChatRoomCompletionResult.Unregister();
	m_CallbackPersonaStateChange.Unregister();
	m_CallbackSetPersonaNameResponse.Unregister();
	m_CallbackClanOfficerList.Unregister();
#endif
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)

void USIK_FriendsSubsystem::OnAvatarImageLoadedCallback(AvatarImageLoaded_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnAvatarImageLoaded.Broadcast(Param.m_steamID, Param.m_iImage, Param.m_iWide, Param.m_iTall);
	});
}

void USIK_FriendsSubsystem::OnFriendRichPresenceUpdateCallback(FriendRichPresenceUpdate_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnFriendRichPresenceUpdate.Broadcast(Param.m_steamIDFriend, Param.m_nAppID);
	});
}

void USIK_FriendsSubsystem::OnDownloadClanActivityCountsResultCallback(DownloadClanActivityCountsResult_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnDownloadClanActivityCountsResult.Broadcast(Param.m_bSuccess);
	});
}

void USIK_FriendsSubsystem::OnFriendEnumerateFollowingListCallback(FriendsEnumerateFollowingList_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		TArray<FSIK_SteamId> SteamIDList;
		for (int32 i = 0; i < Param.m_nResultsReturned; i++)
		{
			SteamIDList.Add(Param.m_rgSteamID[i]);
		}
		OnFriendEnumerateFollowingList.Broadcast(static_cast<ESIK_Result>(Param.m_eResult), SteamIDList, Param.m_nResultsReturned, Param.m_nTotalResultCount);
	});
}

void USIK_FriendsSubsystem::OnFriendsGetFollowerCountCallback(FriendsGetFollowerCount_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnFriendsGetFollowerCount.Broadcast(static_cast<ESIK_Result>(Param.m_eResult), Param.m_steamID, Param.m_nCount);
	});
}

void USIK_FriendsSubsystem::OnFriendsIsFollowingCallback(FriendsIsFollowing_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnFriendsIsFollowing.Broadcast(static_cast<ESIK_Result>(Param.m_eResult), Param.m_steamID, Param.m_bIsFollowing);
	});
}

void USIK_FriendsSubsystem::OnGameConnectedChatJoinCallback(GameConnectedChatJoin_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnGameConnectedChatJoin.Broadcast(Param.m_steamIDClanChat, Param.m_steamIDUser);
	});
}

void USIK_FriendsSubsystem::OnGameConnectedChatLeaveCallback(GameConnectedChatLeave_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnGameConnectedChatLeave.Broadcast(Param.m_steamIDClanChat, Param.m_steamIDUser, Param.m_bKicked, Param.m_bDropped);
	});
}

void USIK_FriendsSubsystem::OnGameConnectedClanChatMsgCallback(GameConnectedClanChatMsg_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnGameConnectedClanChatMsg.Broadcast(Param.m_steamIDClanChat, Param.m_steamIDUser, Param.m_iMessageID);
	});
}

void USIK_FriendsSubsystem::OnGameConnectedFriendChatMsgCallback(GameConnectedFriendChatMsg_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnGameConnectedFriendChatMsg.Broadcast(Param.m_steamIDUser, Param.m_iMessageID);
	});
}

void USIK_FriendsSubsystem::OnGameLobbyJoinRequestedCallback(GameLobbyJoinRequested_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnGameLobbyJoinRequested.Broadcast(Param.m_steamIDFriend, Param.m_steamIDLobby);
	});
}
void USIK_FriendsSubsystem::OnGameOverlayActivatedCallback(GameOverlayActivated_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnGameOverlayActivated.Broadcast(Param.m_bActive != 0);
	});
}

void USIK_FriendsSubsystem::OnGameRichPresenceJoinRequestedCallback(GameRichPresenceJoinRequested_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnGameRichPresenceJoinRequested.Broadcast(Param.m_steamIDFriend, Param.m_rgchConnect);
	});
}

void USIK_FriendsSubsystem::OnGameServerChangeRequestedCallback(GameServerChangeRequested_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnGameServerChangeRequested.Broadcast(Param.m_rgchServer, Param.m_rgchPassword);
	});
}

void USIK_FriendsSubsystem::OnJoinClanChatRoomCompletionResultCallback(JoinClanChatRoomCompletionResult_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnJoinClanChatRoomCompletionResult.Broadcast(Param.m_steamIDClanChat, static_cast<ESIK_ChatRoomEnterResponse>(Param.m_eChatRoomEnterResponse));
	});
}

void USIK_FriendsSubsystem::OnPersonaStateChangeCallback(PersonaStateChange_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnPersonaStateChange.Broadcast(Param.m_ulSteamID, Param.m_nChangeFlags);
	});
}

void USIK_FriendsSubsystem::OnSetPersonaNameResponseCallback(SetPersonaNameResponse_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnSetPersonaNameResponse.Broadcast(static_cast<ESIK_Result>(Param.m_result), Param.m_bLocalSuccess, Param.m_bSuccess);
	});
}

void USIK_FriendsSubsystem::OnClanOfficerListCallback(ClanOfficerListResponse_t* ClanOfficerListResponse)
{
	auto Param = *ClanOfficerListResponse;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnClanOfficerList.Broadcast(Param.m_steamIDClan, Param.m_cOfficers, Param.m_bSuccess != 0);
	});
}
#endif
