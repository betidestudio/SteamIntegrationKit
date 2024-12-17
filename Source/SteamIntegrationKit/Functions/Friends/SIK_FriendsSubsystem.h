// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SIK_SharedFile.h"
#include "SIK_FriendsSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnAvatarImageLoaded, FSIK_SteamId, SteamId, int32, Image, int32, Wide, int32, Tall);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnClanOfficerList, FSIK_SteamId, SteamId, int32, OfficerCount, bool, bSuccess);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnFriendRichPresenceUpdate, FSIK_SteamId, SteamId, FSIK_AppId, AppId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDownloadClanActivityCountsResult, bool, bSuccess);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnFriendEnumerateFollowingList, TEnumAsByte<ESIK_Result>, Result, TArray<FSIK_SteamId>, SteamId, int32, ResultsReturned, int32, TotalResults);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnFriendsGetFollowerCount, TEnumAsByte<ESIK_Result>, Result, FSIK_SteamId, SteamId, int32, Count);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnFriendsIsFollowing, TEnumAsByte<ESIK_Result>, Result, FSIK_SteamId, SteamId, bool, bIsFollowing);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGameConnectedChatJoin, FSIK_SteamId, ClanChatId, FSIK_SteamId, User);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnGameConnectedChatLeave, FSIK_SteamId, ClanChatId, FSIK_SteamId, User, bool, Kicked, bool, Dropped);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnGameConnectedClanChatMsg, FSIK_SteamId, ClanChatId, FSIK_SteamId, User, int32, MessageID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGameConnectedFriendChatMsg, FSIK_SteamId, User, int32, MessageID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGameLobbyJoinRequested, FSIK_SteamId, SteamId, FSIK_SteamId, LobbyId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameOverlayActivated, bool, bActive);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGameRichPresenceJoinRequested, FSIK_SteamId, SteamId, FString, ConnectString);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGameServerChangeRequested, FString, Server, FString, Password);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnJoinClanChatRoomCompletionResult, FSIK_SteamId, ClanChatId, TEnumAsByte<ESIK_ChatRoomEnterResponse>, ChatRoomEnterResponse);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPersonaStateChange, FSIK_SteamId, SteamId, int32, ChangeFlags);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnSetPersonaNameResponse, TEnumAsByte<ESIK_Result>, Result, bool, bLocalSuccess, bool, bRemoteSuccess);




UCLASS()
class STEAMINTEGRATIONKIT_API USIK_FriendsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	USIK_FriendsSubsystem();
	~USIK_FriendsSubsystem();

	//Marks the return of a request officer list call.
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | Friends | Response")
	FOnClanOfficerList OnClanOfficerList;

	//Called when Rich Presence data has been updated for a user, this can happen automatically when friends in the same game update their rich presence, or after a call to RequestFriendRichPresence.
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | Friends | Response")
	FOnFriendRichPresenceUpdate OnFriendRichPresenceUpdate;

	//Called when a Steam group activity has been received.
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | Friends | Response")
	FOnDownloadClanActivityCountsResult OnDownloadClanActivityCountsResult;

	//Returns the result of EnumerateFollowingList.
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | Friends | Response")
	FOnFriendEnumerateFollowingList OnFriendEnumerateFollowingList;

	//Returns the result of GetFollowerCount.
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | Friends | Response")
	FOnFriendsGetFollowerCount OnFriendsGetFollowerCount;

	//Returns the result of IsFollowing.
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | Friends | Response")
	FOnFriendsIsFollowing OnFriendsIsFollowing;

	//Called when a user has joined a Steam group chat that we are in.
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | Friends | Response")
	FOnGameConnectedChatJoin OnGameConnectedChatJoin;

	//Called when a user has left a Steam group chat that the we are in.
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | Friends | Response")
	FOnGameConnectedChatLeave OnGameConnectedChatLeave;

	//Called when a chat message has been received in a Steam group chat that we are in.
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | Friends | Response")
	FOnGameConnectedClanChatMsg OnGameConnectedClanChatMsg;

	//Called when chat message has been received from a friend.
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | Friends | Response")
	FOnGameConnectedFriendChatMsg OnGameConnectedFriendChatMsg;

	/*
	
	Called when the user tries to join a lobby from their friends list or from an invite. The game client should attempt to connect to specified lobby when this is received. If the game isn't running yet then the game will be automatically launched with the command line parameter +connect_lobby <64-bit lobby Steam ID> instead.

	NOTE: This callback is made when joining a lobby. If the user is attempting to join a game but not a lobby, then the callback GameRichPresenceJoinRequested_t will be made.
	*/
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | Friends | Response")
	FOnGameLobbyJoinRequested OnGameLobbyJoinRequested;

	//Posted when the Steam Overlay activates or deactivates. The game can use this to pause or resume single player games.
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | Friends | Response")
	FOnGameOverlayActivated OnGameOverlayActivated;

	/*
	 Called when the user tries to join a game from their friends list or after a user accepts an invite by a friend with InviteUserToGame.

	NOTE: This callback is made when joining a game. If the user is attempting to join a lobby, then the callback GameLobbyJoinRequested_t will be made.
	 */
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | Friends | Response")
	FOnGameRichPresenceJoinRequested OnGameRichPresenceJoinRequested;

	//Called when the user tries to join a different game server from their friends list. The game client should attempt to connect to the specified server when this is received.
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | Friends | Response")
	FOnGameServerChangeRequested OnGameServerChangeRequested;

	//Posted when the user has attempted to join a Steam group chat via JoinClanChatRoom
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | Friends | Response")
	FOnJoinClanChatRoomCompletionResult OnJoinClanChatRoomCompletionResult;

	//Called whenever a friends' status changes.
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | Friends | Response")
	FOnPersonaStateChange OnPersonaStateChange;

	//Reports the result of an attempt to change the current user's persona name.
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | Friends | Response")
	FOnSetPersonaNameResponse OnSetPersonaNameResponse;

	//Called when a large avatar is loaded if you have tried requesting it when it was unavailable.
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | Friends | Response")
	FOnAvatarImageLoaded OnAvatarImageLoaded;
private:

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	STEAM_CALLBACK_MANUAL(USIK_FriendsSubsystem, OnAvatarImageLoadedCallback, AvatarImageLoaded_t, m_CallbackAvatarImageLoaded);
	STEAM_CALLBACK_MANUAL(USIK_FriendsSubsystem, OnClanOfficerListCallback, ClanOfficerListResponse_t, m_CallbackClanOfficerList);
	STEAM_CALLBACK_MANUAL(USIK_FriendsSubsystem, OnFriendRichPresenceUpdateCallback, FriendRichPresenceUpdate_t, m_CallbackFriendRichPresenceUpdate);
	STEAM_CALLBACK_MANUAL(USIK_FriendsSubsystem, OnDownloadClanActivityCountsResultCallback, DownloadClanActivityCountsResult_t, m_CallbackDownloadClanActivityCountsResult);
	STEAM_CALLBACK_MANUAL(USIK_FriendsSubsystem, OnFriendEnumerateFollowingListCallback, FriendsEnumerateFollowingList_t, m_CallbackFriendEnumerateFollowingList);
	STEAM_CALLBACK_MANUAL(USIK_FriendsSubsystem, OnFriendsGetFollowerCountCallback, FriendsGetFollowerCount_t, m_CallbackFriendsGetFollowerCount);
	STEAM_CALLBACK_MANUAL(USIK_FriendsSubsystem, OnFriendsIsFollowingCallback, FriendsIsFollowing_t, m_CallbackFriendsIsFollowing);
	STEAM_CALLBACK_MANUAL(USIK_FriendsSubsystem, OnGameConnectedChatJoinCallback, GameConnectedChatJoin_t, m_CallbackGameConnectedChatJoin);
	STEAM_CALLBACK_MANUAL(USIK_FriendsSubsystem, OnGameConnectedChatLeaveCallback, GameConnectedChatLeave_t, m_CallbackGameConnectedChatLeave);
	STEAM_CALLBACK_MANUAL(USIK_FriendsSubsystem, OnGameConnectedClanChatMsgCallback, GameConnectedClanChatMsg_t, m_CallbackGameConnectedClanChatMsg);
	STEAM_CALLBACK_MANUAL(USIK_FriendsSubsystem, OnGameConnectedFriendChatMsgCallback, GameConnectedFriendChatMsg_t, m_CallbackGameConnectedFriendChatMsg);
	STEAM_CALLBACK_MANUAL(USIK_FriendsSubsystem, OnGameLobbyJoinRequestedCallback, GameLobbyJoinRequested_t, m_CallbackGameLobbyJoinRequested);
	STEAM_CALLBACK_MANUAL(USIK_FriendsSubsystem, OnGameOverlayActivatedCallback, GameOverlayActivated_t, m_CallbackGameOverlayActivated);
	STEAM_CALLBACK_MANUAL(USIK_FriendsSubsystem, OnGameRichPresenceJoinRequestedCallback, GameRichPresenceJoinRequested_t, m_CallbackGameRichPresenceJoinRequested);
	STEAM_CALLBACK_MANUAL(USIK_FriendsSubsystem, OnGameServerChangeRequestedCallback, GameServerChangeRequested_t, m_CallbackGameServerChangeRequested);
	STEAM_CALLBACK_MANUAL(USIK_FriendsSubsystem, OnJoinClanChatRoomCompletionResultCallback, JoinClanChatRoomCompletionResult_t, m_CallbackJoinClanChatRoomCompletionResult);
	STEAM_CALLBACK_MANUAL(USIK_FriendsSubsystem, OnPersonaStateChangeCallback, PersonaStateChange_t, m_CallbackPersonaStateChange);
	STEAM_CALLBACK_MANUAL(USIK_FriendsSubsystem, OnSetPersonaNameResponseCallback, SetPersonaNameResponse_t, m_CallbackSetPersonaNameResponse);
#endif
};
