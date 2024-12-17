// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SIK_SharedFile.h"
#include "SIK_MatchmakingSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFavoritesListAccountsUpdated, TEnumAsByte<ESIK_Result>, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_SevenParams(FOnFavoritesListChanged, FString, IP, int32, QueryPort, int32, ConnPort, FSIK_AppId, AppID, int32, Flags, bool, Add, int32, AccountId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnLobbyMessageDel, FSIK_SteamId, LobbyId, FSIK_SteamId, UserId, TEnumAsByte<ESIK_LobbyChatEntryType>, ChatEntryType, int32, ChatID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnLobbyChatUpdateDel, FSIK_SteamId, LobbyId, FSIK_SteamId, UserId, FSIK_SteamId, MemberIDMakingChange, TEnumAsByte<ESIK_LobbyChatMemberStateChange>, ChatMemberStateChange);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLobbyCreatedDel, FSIK_SteamId, LobbyId, TEnumAsByte<ESIK_Result>, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnLobbyDataUpdateDel, FSIK_SteamId, LobbyId, FSIK_SteamId, UserId, bool, Success);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnLobbyEnterDel, FSIK_SteamId, LobbyId, bool, bLocked,TEnumAsByte<ESIK_ChatRoomEnterResponse>, Response);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnLobbyGameCreatedDel, FSIK_SteamId, LobbyId, FSIK_SteamId, GameServerId, FString, GameServerIP, int32, GameServerPort);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnLobbyInviteDel, FSIK_SteamId, LobbyId, FSIK_SteamId, SenderUserId, FSIK_AppId, AppId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnLobbyKickedDel, FSIK_SteamId, LobbyId, FSIK_SteamId, AdminId, bool, bKickedDueToDisconnect);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLobbyMatchListDel, int32, LobbyCount);

UCLASS(Category = "Steam Integration Kit | Matchmaking")
class STEAMINTEGRATIONKIT_API USIK_MatchmakingSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	USIK_MatchmakingSubsystem();
	~USIK_MatchmakingSubsystem();

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | Matchmaking | Callbacks")
	FOnFavoritesListAccountsUpdated OnFavoritesListAccountsUpdated;

	//A server was added/removed from the favorites list, you should refresh now.
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | Matchmaking | Callbacks")
	FOnFavoritesListChanged OnFavoritesListChanged;

	//A chat (text or binary) message for this lobby has been received. After getting this you must use GetLobbyChatEntry to retrieve the contents of this message.
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | Matchmaking | Callbacks")
	FOnLobbyMessageDel OnLobbyChatMsg;

	//A lobby chat room state has changed, this is usually sent when a user has joined or left the lobby.
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | Matchmaking | Callbacks")
	FOnLobbyChatUpdateDel OnLobbyChatUpdate;

	//Result of our request to create a Lobby. At this point, the lobby has been joined and is ready for use, a LobbyEnter_t callback will also be received (since the local user is joining their own lobby).
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | Matchmaking | Callbacks")
	FOnLobbyCreatedDel OnLobbyCreated;

	/*
	The lobby metadata has changed.

	If m_ulSteamIDMember is a user in the lobby, then use GetLobbyMemberData to access per-user details; otherwise, if m_ulSteamIDMember == m_ulSteamIDLobby, use GetLobbyData to access the lobby metadata.
	*/
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | Matchmaking | Callbacks")
	FOnLobbyDataUpdateDel OnLobbyDataUpdate;

	//Recieved upon attempting to enter a lobby. Lobby metadata is available to use immediately after receiving this.
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | Matchmaking | Callbacks")
	FOnLobbyEnterDel OnLobbyEnter;

	//A game server has been set via SetLobbyGameServer for all of the members of the lobby to join. It's up to the individual clients to take action on this; the typical game behavior is to leave the lobby and connect to the specified game server; but the lobby may stay open throughout the session if desired.
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | Matchmaking | Callbacks")
	FOnLobbyGameCreatedDel OnLobbyGameCreated;

	/*
	Someone has invited you to join a Lobby. Normally you don't need to do anything with this, as the Steam UI will also display a '<user> has invited you to the lobby, join?' notification and message.

	If the user outside a game chooses to join, your game will be launched with the parameter +connect_lobby <64-bit lobby id>, or with the callback GameLobbyJoinRequested_t if they're already in-game.
	*/
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | Matchmaking | Callbacks")
	FOnLobbyInviteDel OnLobbyInvite;

	//Currently unused! If you want to implement kicking at this time then do it with a special packet sent with SendLobbyChatMsg, when the user gets the packet they should call LeaveLobby.
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | Matchmaking | Callbacks")
	FOnLobbyKickedDel OnLobbyKicked;

	//Result when requesting the lobby list. You should iterate over the returned lobbies with GetLobbyByIndex, from 0 to m_nLobbiesMatching-1.
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | Matchmaking | Callbacks")
	FOnLobbyMatchListDel OnLobbyMatchList;

private:
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	STEAM_CALLBACK_MANUAL(USIK_MatchmakingSubsystem, OnFavoritesListAccountsCallbck, FavoritesListAccountsUpdated_t, m_CallbackFavoritesListAccountsUpdated);
	STEAM_CALLBACK_MANUAL(USIK_MatchmakingSubsystem, OnFavoritesListChangedCallback, FavoritesListChanged_t, m_CallbackFavoritesListChanged);
	STEAM_CALLBACK_MANUAL(USIK_MatchmakingSubsystem, OnLobbyChatMsgCallback, LobbyChatMsg_t, m_CallbackLobbyChatMsg);
	STEAM_CALLBACK_MANUAL(USIK_MatchmakingSubsystem, OnLobbyChatUpdateCallback, LobbyChatUpdate_t, m_CallbackLobbyChatUpdate);
	STEAM_CALLBACK_MANUAL(USIK_MatchmakingSubsystem, OnLobbyCreatedCallback, LobbyCreated_t, m_CallbackLobbyCreated);
	STEAM_CALLBACK_MANUAL(USIK_MatchmakingSubsystem, OnLobbyDataUpdateCallback, LobbyDataUpdate_t, m_CallbackLobbyDataUpdate);
	STEAM_CALLBACK_MANUAL(USIK_MatchmakingSubsystem, OnLobbyEnterCallback, LobbyEnter_t, m_CallbackLobbyEnter);
	STEAM_CALLBACK_MANUAL(USIK_MatchmakingSubsystem, OnLobbyGameCreatedCallback, LobbyGameCreated_t, m_CallbackLobbyGameCreated);
	STEAM_CALLBACK_MANUAL(USIK_MatchmakingSubsystem, OnLobbyInviteCallback, LobbyInvite_t, m_CallbackLobbyInvite);
	STEAM_CALLBACK_MANUAL(USIK_MatchmakingSubsystem, OnLobbyKickedCallback, LobbyKicked_t, m_CallbackLobbyKicked);
	STEAM_CALLBACK_MANUAL(USIK_MatchmakingSubsystem, OnLobbyMatchListCallback, LobbyMatchList_t, m_CallbackLobbyMatchList);
#endif
};
