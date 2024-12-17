// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_MatchmakingSubsystem.h"

#include "Async/Async.h"
#include "Interfaces/IPv4/IPv4Address.h"


USIK_MatchmakingSubsystem::USIK_MatchmakingSubsystem()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	m_CallbackFavoritesListAccountsUpdated.Register(this, &USIK_MatchmakingSubsystem::OnFavoritesListAccountsCallbck);
	m_CallbackFavoritesListChanged.Register(this, &USIK_MatchmakingSubsystem::OnFavoritesListChangedCallback);
	m_CallbackLobbyChatMsg.Register(this, &USIK_MatchmakingSubsystem::OnLobbyChatMsgCallback);
	m_CallbackLobbyChatUpdate.Register(this, &USIK_MatchmakingSubsystem::OnLobbyChatUpdateCallback);
	m_CallbackLobbyCreated.Register(this, &USIK_MatchmakingSubsystem::OnLobbyCreatedCallback);
	m_CallbackLobbyDataUpdate.Register(this, &USIK_MatchmakingSubsystem::OnLobbyDataUpdateCallback);
	m_CallbackLobbyEnter.Register(this, &USIK_MatchmakingSubsystem::OnLobbyEnterCallback);
	m_CallbackLobbyGameCreated.Register(this, &USIK_MatchmakingSubsystem::OnLobbyGameCreatedCallback);
	m_CallbackLobbyInvite.Register(this, &USIK_MatchmakingSubsystem::OnLobbyInviteCallback);
	m_CallbackLobbyKicked.Register(this, &USIK_MatchmakingSubsystem::OnLobbyKickedCallback);
	m_CallbackLobbyMatchList.Register(this, &USIK_MatchmakingSubsystem::OnLobbyMatchListCallback);

 	if(IsRunningDedicatedServer())
 	{
	m_CallbackFavoritesListAccountsUpdated.SetGameserverFlag();
	m_CallbackFavoritesListChanged.SetGameserverFlag();
	m_CallbackLobbyChatMsg.SetGameserverFlag();
	m_CallbackLobbyChatUpdate.SetGameserverFlag();
	m_CallbackLobbyCreated.SetGameserverFlag();
	m_CallbackLobbyDataUpdate.SetGameserverFlag();
	m_CallbackLobbyEnter.SetGameserverFlag();
	m_CallbackLobbyGameCreated.SetGameserverFlag();
	m_CallbackLobbyInvite.SetGameserverFlag();
	m_CallbackLobbyKicked.SetGameserverFlag();
	m_CallbackLobbyMatchList.SetGameserverFlag();
}
#endif
}

USIK_MatchmakingSubsystem::~USIK_MatchmakingSubsystem()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	m_CallbackFavoritesListAccountsUpdated.Unregister();
	m_CallbackFavoritesListChanged.Unregister();
	m_CallbackLobbyChatMsg.Unregister();
	m_CallbackLobbyChatUpdate.Unregister();
	m_CallbackLobbyCreated.Unregister();
	m_CallbackLobbyDataUpdate.Unregister();
	m_CallbackLobbyEnter.Unregister();
	m_CallbackLobbyGameCreated.Unregister();
	m_CallbackLobbyInvite.Unregister();
	m_CallbackLobbyKicked.Unregister();
	m_CallbackLobbyMatchList.Unregister();
#endif
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
void USIK_MatchmakingSubsystem::OnFavoritesListAccountsCallbck(FavoritesListAccountsUpdated_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		TEnumAsByte<ESIK_Result> Result = static_cast<ESIK_Result>(Param.m_eResult);
		OnFavoritesListAccountsUpdated.Broadcast(Result);
	});
}

void USIK_MatchmakingSubsystem::OnFavoritesListChangedCallback(FavoritesListChanged_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		FString IP = FIPv4Address(Param.m_nIP).ToString();
		int32 QueryPort = Param.m_nQueryPort;
		int32 ConnPort = Param.m_nConnPort;
		FSIK_AppId AppID = Param.m_nAppID;
		int32 Flags = Param.m_nFlags;
		bool Add = Param.m_bAdd;
		int32 AccountId = Param.m_unAccountId;
		OnFavoritesListChanged.Broadcast(IP, QueryPort, ConnPort, AppID, Flags, Add, AccountId);
	});
}

void USIK_MatchmakingSubsystem::OnLobbyChatMsgCallback(LobbyChatMsg_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		FSIK_SteamId LobbyId = Param.m_ulSteamIDLobby;
		FSIK_SteamId UserId = Param.m_ulSteamIDUser;
		TEnumAsByte<ESIK_LobbyChatEntryType> ChatEntryType = static_cast<ESIK_LobbyChatEntryType>(Param.m_eChatEntryType);
		int32 ChatID = Param.m_iChatID;
		OnLobbyChatMsg.Broadcast(LobbyId, UserId, ChatEntryType, ChatID);
	});
}

void USIK_MatchmakingSubsystem::OnLobbyChatUpdateCallback(LobbyChatUpdate_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		FSIK_SteamId LobbyId = Param.m_ulSteamIDLobby;
		FSIK_SteamId UserId = Param.m_ulSteamIDUserChanged;
		FSIK_SteamId MemberIDMakingChange = Param.m_ulSteamIDMakingChange;
		TEnumAsByte<ESIK_LobbyChatMemberStateChange> ChatMemberStateChange = static_cast<ESIK_LobbyChatMemberStateChange>(Param.m_rgfChatMemberStateChange);
		OnLobbyChatUpdate.Broadcast(LobbyId, UserId, MemberIDMakingChange, ChatMemberStateChange);
	});
}

void USIK_MatchmakingSubsystem::OnLobbyCreatedCallback(LobbyCreated_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		FSIK_SteamId LobbyId = Param.m_ulSteamIDLobby;
		TEnumAsByte<ESIK_Result> Result = static_cast<ESIK_Result>(Param.m_eResult);
		OnLobbyCreated.Broadcast(LobbyId, Result);
	});
}

void USIK_MatchmakingSubsystem::OnLobbyDataUpdateCallback(LobbyDataUpdate_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		FSIK_SteamId LobbyId = Param.m_ulSteamIDLobby;
		FSIK_SteamId UserId = Param.m_ulSteamIDMember;
		bool Success = Param.m_bSuccess != 0;
		OnLobbyDataUpdate.Broadcast(LobbyId, UserId, Success);
	});
}

void USIK_MatchmakingSubsystem::OnLobbyEnterCallback(LobbyEnter_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		FSIK_SteamId LobbyId = Param.m_ulSteamIDLobby;
		bool bLocked = Param.m_bLocked;
		TEnumAsByte<ESIK_ChatRoomEnterResponse> Response = static_cast<ESIK_ChatRoomEnterResponse>(Param.m_EChatRoomEnterResponse);
		OnLobbyEnter.Broadcast(LobbyId, bLocked, Response);
	});
}

void USIK_MatchmakingSubsystem::OnLobbyGameCreatedCallback(LobbyGameCreated_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		FSIK_SteamId LobbyId = Param.m_ulSteamIDLobby;
		FSIK_SteamId GameServerId = Param.m_ulSteamIDGameServer;
		FString GameServerIP = FIPv4Address(Param.m_unIP).ToString();
		int32 GameServerPort = Param.m_usPort;
		OnLobbyGameCreated.Broadcast(LobbyId, GameServerId, GameServerIP, GameServerPort);
	});
}

void USIK_MatchmakingSubsystem::OnLobbyInviteCallback(LobbyInvite_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		FSIK_SteamId LobbyId = Param.m_ulSteamIDLobby;
		FSIK_SteamId SenderUserId = Param.m_ulSteamIDUser;
		FSIK_AppId AppId = Param.m_ulGameID;
		OnLobbyInvite.Broadcast(LobbyId, SenderUserId, AppId);
	});
}

void USIK_MatchmakingSubsystem::OnLobbyKickedCallback(LobbyKicked_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		FSIK_SteamId LobbyId = Param.m_ulSteamIDLobby;
		FSIK_SteamId AdminId = Param.m_ulSteamIDAdmin;
		bool bKickedDueToDisconnect = Param.m_bKickedDueToDisconnect != 0;
		OnLobbyKicked.Broadcast(LobbyId, AdminId, bKickedDueToDisconnect);
	});
}

void USIK_MatchmakingSubsystem::OnLobbyMatchListCallback(LobbyMatchList_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		int32 LobbyCount = Param.m_nLobbiesMatching;
		OnLobbyMatchList.Broadcast(LobbyCount);
	});
}
#endif