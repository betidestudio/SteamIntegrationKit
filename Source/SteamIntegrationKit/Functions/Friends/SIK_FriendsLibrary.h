// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SIK_SharedFile.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "Serialization/BulkData.h"
#include "Runtime/Core/Public/PixelFormat.h"
#include "Engine/Texture.h"
#include "Runtime/Launch/Resources/Version.h"
#include "Async/Async.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SIK_FriendsLibrary.generated.h"

USTRUCT(BlueprintType)
struct FSIK_FriendGameInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Steam Integration Kit || SDK Functions || Friends")
	FSIK_SteamId LobbySteamId;

	UPROPERTY(BlueprintReadOnly, Category = "Steam Integration Kit || SDK Functions || Friends")
	FSIK_GameID GameId;

	UPROPERTY(BlueprintReadOnly, Category = "Steam Integration Kit || SDK Functions || Friends")
	int32 IP;

	UPROPERTY(BlueprintReadOnly, Category = "Steam Integration Kit || SDK Functions || Friends")
	int32 GamePort;

	UPROPERTY(BlueprintReadOnly, Category = "Steam Integration Kit || SDK Functions || Friends")
	int32 QueryPort;
	
	FSIK_FriendGameInfo()
	{
		LobbySteamId = 0;
		GameId = FSIK_GameID();
		IP = 0;
		GamePort = 0;
		QueryPort = 0;
	};
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	FSIK_FriendGameInfo(FriendGameInfo_t FriendGameInfo)
	{
		LobbySteamId = FriendGameInfo.m_steamIDLobby;
		GameId = FriendGameInfo.m_gameID;
		IP = FriendGameInfo.m_unGameIP;
		GamePort = FriendGameInfo.m_usGamePort;
		QueryPort = FriendGameInfo.m_usQueryPort;
	};
#endif
	
};

UENUM(BlueprintType)
enum ESIK_PersonaState
{
	PersonaStateOffline = 0 UMETA(DisplayName = "Offline"),
	PersonaStateOnline = 1 UMETA(DisplayName = "Online"),
	PersonaStateBusy = 2 UMETA(DisplayName = "Busy"),
	PersonaStateAway = 3 UMETA(DisplayName = "Away"),
	PersonaStateSnooze = 4 UMETA(DisplayName = "Snooze"),
	PersonaStateLookingToTrade = 5 UMETA(DisplayName = "Looking To Trade"),
	PersonaStateLookingToPlay = 6 UMETA(DisplayName = "Looking To Play"),
	PersonaStateMax = 7 UMETA(DisplayName = "Max")
};

UENUM(BlueprintType)
enum ESIK_FriendRelationship
{
	FriendRelationshipNone = 0 UMETA(DisplayName = "None"),
	FriendRelationshipBlocked = 1 UMETA(DisplayName = "Blocked"),
	FriendRelationshipRequestRecipient = 2 UMETA(DisplayName = "Request Recipient"),
	FriendRelationshipFriend = 3 UMETA(DisplayName = "Friend"),
	FriendRelationshipRequestInitiator = 4 UMETA(DisplayName = "Request Initiator"),
	FriendRelationshipIgnored = 5 UMETA(DisplayName = "Ignored"),
	FriendRelationshipIgnoredFriend = 6 UMETA(DisplayName = "Ignored Friend"),
	FriendRelationshipSuggested = 7 UMETA(DisplayName = "Suggested"),
	FriendRelationshipMax = 8 UMETA(DisplayName = "Max")
};
UCLASS()
class STEAMINTEGRATIONKIT_API USIK_FriendsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/*
	Activates the game overlay, with an optional dialog to open.
	@param DialogToOpen - Valid options include "Friends", "Community", "Players", "Settings", "OfficialGameGroup", "Stats", "Achievements", "chatroomgroup/nnnn".
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Activate Steam Game Overlay", meta=(Keywords="ActivateGameOverlay"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static void ActivateGameOverlay(const FString& DialogToOpen);

	/*
	Activates game overlay to open the invite dialog. Invitations will be sent for the provided lobby.
	@param SteamIdLobby - The Steam ID of the lobby to invite to.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Activate Steam Game Overlay Invite Dialog", meta=(Keywords="ActivateGameOverlayInviteDialog"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static void ActivateGameOverlayInviteDialog(const int64& SteamIdLobby);

	/*
	Activates game overlay to the store page for an app.
	@param AppID - The AppID of the app to show.
	@param bAddToCartAndShow - If true, add to cart and show.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Activate Steam Game Overlay To Store", meta=(Keywords="ActivateGameOverlayToStore"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static void ActivateGameOverlayToStore(const FSIK_AppId& AppID, bool bAddToCartAndShow = true);

	/*
	Activates game overlay to a specific place.
	@param Dialog - Valid options include "steamid", "chat", "jointrade", "stats", "achievements", "friendadd", "friendremove", "friendrequestaccept", "friendrequestignore".
	@param SteamIdUser - The Steam ID of the user to interact with.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Activate Steam Game Overlay To User", meta=(Keywords="ActivateGameOverlayToUser"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static void ActivateGameOverlayToUser(const FString& Dialog, int64 SteamIdUser);

	/*
	Activates game overlay web browser directly to the specified URL.
	@param URL - The full address with protocol type.
	@param bUseModal - If true, the browser will be opened in a special overlay configuration.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Activate Steam Game Overlay To WebPage", meta=(Keywords="ActivateGameOverlayToWebPage"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static void ActivateGameOverlayToWebPage(const FString& URL, bool bUseModal = false);

	/*
	Clears the rich presence data of the local user.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Clear Steam Rich Presence", meta=(Keywords="ClearRichPresence"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static void ClearRichPresence();

	/*
	Closes the Steam clan chat window in Steam.
	@param SteamIdClanChat - The Steam ID of the clan chat.
	@return - true if successful, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Close Steam Clan Chat Window In Steam", meta=(Keywords="CloseClanChatWindow"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static bool CloseClanChatWindowInSteam(int64 SteamIdClanChat);

	/*
	Gets a Steam chat member by index.
	@param SteamIdClan - The Steam ID of the clan.
	@param MemberIndex - The index of the member.
	@return - The Steam ID of the member.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Get Steam Chat Member By Index", meta=(Keywords="GetChatMemberByIndex"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static FSIK_SteamId GetChatMemberByIndex(FSIK_SteamId SteamIdClan, int32 MemberIndex);

	/*
	Gets the activity counts for a Steam clan.
	@param SteamIdClan - The Steam ID of the clan.
	@param Online - The number of members online.
	@param InGame - The number of members in-game.
	@param Chatting - The number of members chatting.
	@return - true if successful, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Get Steam Clan Activity Counts", meta=(Keywords="GetClanActivityCounts"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static bool GetClanActivityCounts(FSIK_SteamId SteamIdClan, int32& Online, int32& InGame, int32& Chatting);

	/*
	Gets a Steam clan by index.
	@param ClanIndex - The index of the clan.
	@return - The Steam ID of the clan.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Get Steam Clan By Index", meta=(Keywords="GetClanByIndex"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static FSIK_SteamId GetClanByIndex(int32 ClanIndex);

	/*
	Gets the number of chat members in a Steam clan.
	@param SteamIdClan - The Steam ID of the clan.
	@return - The number of chat members.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Get Steam Clan Chat Member Count", meta=(Keywords="GetClanChatMemberCount"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static int32 GetClanChatMemberCount(FSIK_SteamId SteamIdClan);

	/*
	Gets a chat message from a Steam clan chat.
	@param SteamIdClan - The Steam ID of the clan.
	@param MessageIndex - The index of the message.
	@param Text - The text of the message.
	@param SteamIdUser - The Steam ID of the user who sent the message.
	@param ChatEntryType - The type of chat entry.
	@return - The number of bytes in the message.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Get Steam Clan Chat Message", meta=(Keywords="GetClanChatMessage"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static int32 GetClanChatMessage(FSIK_SteamId SteamIdClan, int32 MessageIndex, const TArray<uint8>& Text, FSIK_SteamId& SteamIdUser, FString& ChatEntryType);

	/*
	Gets the number of Steam clans.
	@return - The number of clans.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Get Steam Clan Count", meta=(Keywords="GetClanCount"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static int32 GetClanCount();

	UFUNCTION(BlueprintCallable, DisplayName = "Get Steam Clan Name", meta=(Keywords="GetClanName"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static FString GetClanName(FSIK_SteamId SteamIdClan);
/*
	Gets the officer of a Steam clan by index.
	@param SteamIdClan - The Steam ID of the clan.
	@param OfficerIndex - The index of the officer.
	@return - The Steam ID of the officer.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Get Steam Clan Officer By Index", meta=(Keywords="GetClanOfficerByIndex"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static FSIK_SteamId GetClanOfficerByIndex(FSIK_SteamId SteamIdClan, int32 OfficerIndex);

	/*
	Gets the number of officers in a Steam clan.
	@param SteamIdClan - The Steam ID of the clan.
	@return - The number of officers.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Get Steam Clan Officer Count", meta=(Keywords="GetClanOfficerCount"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static int32 GetClanOfficerCount(FSIK_SteamId SteamIdClan);

	/*
	Gets the owner of a Steam clan.
	@param SteamIdClan - The Steam ID of the clan.
	@return - The Steam ID of the clan owner.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Get Steam Clan Owner", meta=(Keywords="GetClanOwner"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static FSIK_SteamId GetClanOwner(FSIK_SteamId SteamIdClan);

	/*
	Gets the tag of a Steam clan.
	@param SteamIdClan - The Steam ID of the clan.
	@return - The tag of the clan.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Get Steam Clan Tag", meta=(Keywords="GetClanTag"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static FString GetClanTag(FSIK_SteamId SteamIdClan);

	/*
	Gets a Steam co-play friend by index.
	@param CoplayFriend - The index of the co-play friend.
	@return - The Steam ID of the co-play friend.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Get Steam Coplay Friend", meta=(Keywords="GetCoplayFriend"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static FSIK_SteamId GetCoplayFriend(int32 CoplayFriend);
	
	/*
	Gets the number of Steam co-play friends.
	@return - The number of co-play friends.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Get Steam Coplay Friend Count", meta=(Keywords="GetCoplayFriendCount"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static int32 GetCoplayFriendCount();

	/*
	Gets a Steam friend by index.
	@param FriendIndex - The index of the friend.
	@param FriendFlags - Flags to filter friends.
	@return - The Steam ID of the friend.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Get Steam Friend By Index", meta=(Keywords="GetFriendByIndex"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static FSIK_SteamId GetFriendByIndex(int32 FriendIndex, TArray<TEnumAsByte<ESIK_FriendFlags>> FriendFlags);

	/*
	Gets the game that a Steam friend is currently playing.
	@param SteamIdFriend - The Steam ID of the friend.
	@return - The Steam ID of the game.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Get Steam Friend Coplay Game", meta=(Keywords="GetFriendCoplayGame"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static FSIK_AppId GetFriendCoplayGame(FSIK_SteamId SteamIdFriend);
	
	/*
	Gets the co-play time with a Steam friend.
	@param SteamIdFriend - The Steam ID of the friend.
	@return - The co-play time as a FDateTime object.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Get Steam Friend Coplay Time", meta=(Keywords="GetFriendCoplayTime"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static FDateTime GetFriendCoplayTime(FSIK_SteamId SteamIdFriend);

	/*
	Gets the number of friends for a specific friend list.
	@param FriendFlags - Flags to filter the friend list.
	@return - The number of friends.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Get Steam Friend Count", meta=(Keywords="GetFriendCount"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static int32 GetFriendCount(TArray<TEnumAsByte<ESIK_FriendFlags>> FriendFlags);

	/*
	Gets the number of friends from a specific source.
	@param SteamIdSource - The Steam ID of the source.
	@return - The number of friends from the source.
	*/
	UFUNCTION(BlueprintCallable, DisplayName ="Get Steam Friend Count From Source", meta=(Keywords="GetFriendCountFromSource"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static int32 GetFriendCountFromSource(FSIK_SteamId SteamIdSource);

	/*
	Gets a friend from a specific source by index.
	@param SteamIdSource - The Steam ID of the source.
	@param FriendIndex - The index of the friend.
	@return - The Steam ID of the friend.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Get Steam Friend From Source By Index", meta=(Keywords="GetFriendFromSourceByIndex"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static FSIK_SteamId GetFriendFromSourceByIndex(FSIK_SteamId SteamIdSource, int32 FriendIndex);

	/*
	Gets the game played information of a Steam friend.
	@param SteamIdFriend - The Steam ID of the friend.
	@param GameInfo - The game information structure to populate.
	@return - true if successful, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Get Steam Friend Game Played", meta=(Keywords="GetFriendGamePlayed"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static bool GetFriendGamePlayed(FSIK_SteamId SteamIdFriend, FSIK_FriendGameInfo& GameInfo);

	/*
	Gets a message from a Steam friend.
	@param SteamIdFriend - The Steam ID of the friend.
	@param MessageIndex - The index of the message.
	@param Text - The text of the message.
	@param ChatEntryType - The type of chat entry.
	@return - The number of bytes in the message.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Get Steam Friend Message", meta=(Keywords="GetFriendMessage"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static int32 GetFriendMessage(FSIK_SteamId SteamIdFriend, int32 MessageIndex, TArray<uint8>& Text, FString& ChatEntryType);

	/*
	Gets the persona name of a Steam friend.
	@param SteamIdFriend - The Steam ID of the friend.
	@return - The persona name of the friend.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Get Steam Friend Persona Name", meta=(Keywords="GetFriendPersonaName"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static FString GetFriendPersonaName(FSIK_SteamId SteamIdFriend);
	
	/*
	Gets the history of persona names for a Steam friend.
	@param SteamIdFriend - The Steam ID of the friend.
	@param PersonaNameIndex - The index of the persona name.
	@return - The persona name.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Get Steam Friend Persona Name History", meta=(Keywords="GetFriendPersonaNameHistory"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static FString GetFriendPersonaNameHistory(FSIK_SteamId SteamIdFriend, int32 PersonaNameIndex);

	/*
	Gets the current persona state of a Steam friend.
	@param SteamIdFriend - The Steam ID of the friend.
	@return - The persona state as an ESIK_PersonaState enum.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Get Steam Friend Persona State", meta=(Keywords="GetFriendPersonaState"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static TEnumAsByte<ESIK_PersonaState> GetFriendPersonaState(FSIK_SteamId SteamIdFriend);

	/*
	Gets the relationship to a Steam friend.
	@param SteamIdFriend - The Steam ID of the friend.
	@return - The relationship as an ESIK_FriendRelationship enum.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Get Steam Friend Relationship", meta=(Keywords="GetFriendRelationship"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static TEnumAsByte<ESIK_FriendRelationship> GetFriendRelationship(FSIK_SteamId SteamIdFriend);

	/*
	Gets the rich presence value of a Steam friend by key.
	@param SteamIdFriend - The Steam ID of the friend.
	@param Key - The key to look up.
	@return - The rich presence value.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Get Steam Friend Rich Presence", meta=(Keywords="GetFriendRichPresence"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static FString GetFriendRichPresence(FSIK_SteamId SteamIdFriend, const FString& Key);

	/*
	Gets the rich presence key by index for a Steam friend.
	@param SteamIdFriend - The Steam ID of the friend.
	@param KeyIndex - The index of the key.
	@return - The rich presence key.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Get Steam Friend Rich Presence Key By Index", meta=(Keywords="GetFriendRichPresenceKeyByIndex"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static FString GetFriendRichPresenceKeyByIndex(FSIK_SteamId SteamIdFriend, int32 KeyIndex);

	/*
	Gets the number of rich presence keys for a Steam friend.
	@param SteamIdFriend - The Steam ID of the friend.
	@return - The number of rich presence keys.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Get Steam Friend Rich Presence Key Count", meta=(Keywords="GetFriendRichPresenceKeyCount"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static int32 GetFriendRichPresenceKeyCount(FSIK_SteamId SteamIdFriend);

	/*
	Gets the number of friends groups.
	@return - The number of friends groups.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Get Steam Friends Group Count", meta=(Keywords="GetFriendsGroupCount"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static int32 GetFriendGroupCount();

	/*
	Gets the friends group ID by index.
	@param GroupIndex - The index of the friends group.
	@return - The Steam ID of the friends group.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Get Steam Friends Group ID By Index", meta=(Keywords="GetFriendsGroupIDByIndex"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static FSIK_FriendsGroupID GetFriendGroupIDByIndex(int32 GroupIndex);

	/*
	Gets the number of members in a friends group.
	@param FriendsGroupID - The Steam ID of the friends group.
	@return - The number of members.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Get Steam Friends Group Members Count", meta=(Keywords="GetFriendsGroupMembersCount"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static int32 GetFriendGroupMembersCount(FSIK_FriendsGroupID FriendsGroupID);

	/*
	Gets the list of members in a friends group.
	@param FriendsGroupID - The Steam ID of the friends group.
	@param MembersCount - The number of members.
	@return - An array of Steam IDs of the members.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Get Steam Friends Group Members List", meta=(Keywords="GetFriendsGroupMembersList"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static TArray<FSIK_SteamId> GetFriendsGroupMembersList(FSIK_FriendsGroupID FriendsGroupID, int32 MembersCount);

	/*
	Gets the name of a friends group.
	@param FriendsGroupID - The Steam ID of the friends group.
	@return - The name of the friends group.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Get Steam Friends Group Name", meta=(Keywords="GetFriendsGroupName"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static FString GetFriendsGroupName(FSIK_FriendsGroupID FriendsGroupID);

	/*
	Gets the Steam level of a friend.
	@param SteamIdFriend - The Steam ID of the friend.
	@return - The Steam level of the friend.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Get Steam Friend Steam Level", meta=(Keywords="GetFriendSteamLevel"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static int32 GetFriendSteamLevel(FSIK_SteamId SteamIdFriend);

	/*
	Gets the large avatar of a friend.
	@param SteamIdFriend - The Steam ID of the friend.
	@return - The large avatar as an int.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Get Steam Large Friend Avatar", meta=(Keywords="GetLargeFriendAvatar"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static UTexture2D* GetLargeFriendAvatar(FSIK_SteamId SteamIdFriend, int32& Avatar);

	/*
	Gets the medium avatar of a friend.
	@param SteamIdFriend - The Steam ID of the friend.
	@return - The medium avatar as an int.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Get Steam Medium Friend Avatar", meta=(Keywords="GetMediumFriendAvatar"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static UTexture2D* GetMediumFriendAvatar(FSIK_SteamId SteamIdFriend, int32& Avatar);

	/*
	Gets the current persona name of the local user.
	@return - The persona name.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Get Steam Persona Name", meta=(Keywords="GetPersonaName"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static FString GetPersonaName();

	/*
	Gets the current persona state of the local user.
	@return - The persona state as an ESIK_PersonaState enum.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Get Steam Persona State", meta=(Keywords="GetPersonaState"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static TEnumAsByte<ESIK_PersonaState> GetPersonaState();

	/*
	Gets the nickname of a player.
	@param SteamIdPlayer - The Steam ID of the player.
	@return - The player's nickname.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Get Steam Player Nickname", meta=(Keywords="GetPlayerNickname"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static FString GetPlayerNickname(FSIK_SteamId SteamIdPlayer);

	/*
	Gets the small avatar of a friend.
	@param SteamIdFriend - The Steam ID of the friend.
	@return - The small avatar as an int.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Get Steam Small Friend Avatar", meta=(Keywords="GetSmallFriendAvatar"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static UTexture2D* GetSmallFriendAvatar(FSIK_SteamId SteamIdFriend, int32& Avatar);

	/*
	Gets the user restrictions.
	@return - The user restrictions as an int.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Get Steam User Restrictions", meta=(Keywords="GetUserRestrictions"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static int32 GetUserRestrictions();

	/*
	Checks if the user has a specific friend.
	@param SteamIdFriend - The Steam ID of the friend.
	@param FriendFlags - Flags to filter friends.
	@return - true if the user has the friend, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Has Steam Friend", meta=(Keywords="HasFriend"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static bool HasFriend(FSIK_SteamId SteamIdFriend, TArray<TEnumAsByte<ESIK_FriendFlags>> FriendFlags);

	/*
	Invites a user to a game.
	@param SteamIdFriend - The Steam ID of the friend.
	@param ConnectString - The connection string for the invite.
	@return - true if the invite was successful, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Invite Steam User To Game", meta=(Keywords="InviteUserToGame"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static bool InviteUserToGame(FSIK_SteamId SteamIdFriend, const FString& ConnectString);

	/*
	Checks if a user is an admin in a clan chat.
	@param SteamIdClanChat - The Steam ID of the clan chat.
	@param SteamIdUser - The Steam ID of the user.
	@return - true if the user is an admin, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Is Steam Clan Chat Admin", meta=(Keywords="IsClanChatAdmin"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static bool IsClanChatAdmin(FSIK_SteamId SteamIdClanChat, FSIK_SteamId SteamIdUser);

	/*
	Checks if a clan is public.
	@param SteamIdClan - The Steam ID of the clan.
	@return - true if the clan is public, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Is Steam Clan Public", meta=(Keywords="IsClanPublic"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static bool IsClanPublic(FSIK_SteamId SteamIdClan);

	/*
	Checks if a clan is an official game group.
	@param SteamIdClan - The Steam ID of the clan.
	@return - true if the clan is an official game group, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Is Steam Clan Official Game Group", meta=(Keywords="IsClanOfficialGameGroup"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static bool IsClanOfficialGameGroup(FSIK_SteamId SteamIdClan);

	/*
	Checks if a clan chat window is open in Steam.
	@param SteamIdClanChat - The Steam ID of the clan chat.
	@return - true if the clan chat window is open, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Is Steam Clan Chat Window Open In Steam", meta=(Keywords="IsClanChatWindowOpen"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static bool IsClanChatWindowOpenInSteam(FSIK_SteamId SteamIdClanChat);

	/*
	Checks if the user is following another user.
	@param SteamIdFriend - The Steam ID of the friend.
	@return - true if the user is following the friend, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Is Steam Following", meta=(Keywords="IsFollowing"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static bool IsFollowing(FSIK_SteamId SteamIdFriend);

	/*
	Checks if a user is in a specific source.
	@param SteamIdFriend - The Steam ID of the friend.
	@param SteamIdSource - The Steam ID of the source.
	@return - true if the user is in the source, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Is Steam User In Source", meta=(Keywords="IsUserInSource"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static bool IsUserInSource(FSIK_SteamId SteamIdFriend, FSIK_SteamId SteamIdSource);

	/*
	Leaves a clan chat room.
	@param SteamIdClanChat - The Steam ID of the clan chat.
	@return - true if successful, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Leave Steam Clan Chat Room", meta=(Keywords="LeaveClanChatRoom"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static bool LeaveClanChatRoom(FSIK_SteamId SteamIdClanChat);
	
	/*
	Replies to a message from a Steam friend.
	@param SteamIdFriend - The Steam ID of the friend.
	@param Text - The text of the reply.
	@return - true if successful, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Reply To Steam Friend Message", meta=(Keywords="ReplyToFriendMessage"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static bool ReplyToFriendMessage(FSIK_SteamId SteamIdFriend, const FString& Text);

	/*
	Requests rich presence data from a Steam friend.
	@param SteamIdFriend - The Steam ID of the friend.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Request Steam Friend Rich Presence", meta=(Keywords="RequestFriendRichPresence"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static void RequestFriendRichPresence(FSIK_SteamId SteamIdFriend);

	/*
	Requests information about a Steam user.
	@param SteamIdUser - The Steam ID of the user.
	@param bRequireNameOnly - If true, only the name is required.
	@return - true if successful, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Request Steam User Information", meta=(Keywords="RequestUserInfo"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static bool RequestUserInfo(FSIK_SteamId SteamIdUser, bool bRequireNameOnly);

	/*
	Sends a message to a Steam clan chat.
	@param SteamIdClanChat - The Steam ID of the clan chat.
	@param Text - The text of the message.
	@return - true if successful, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Send Steam Clan Chat Message", meta=(Keywords="SendClanChatMessage"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static bool SendClanChatMessage(FSIK_SteamId SteamIdClanChat, const FString& Text);

	/*
	Sets whether the local player is speaking in-game voice.
	@param SteamIdFriend - The Steam ID of the friend.
	@param bSpeaking - If true, the player is speaking.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Set Steam In Game Voice Speaking", meta=(Keywords="SetInGameVoiceSpeaking"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static void SetInGameVoiceSpeaking(FSIK_SteamId SteamIdFriend, bool bSpeaking);

	/*
	Sets whether to listen for friend messages.
	@param bInterceptEnabled - If true, interception is enabled.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Set Steam Listen For Friend Message", meta=(Keywords="SetListenForFriendMessage"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static void SetListenForFriendMessage(bool bInterceptEnabled = true);

		/*
	
	*Mark a target user as 'played with'.
	NOTE: The current user must be in game with the other player for the association to work.
	You can view the players you have recently played with here on the Steam community and in the Steam Overlay.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Set Steam Played With", meta=(Keywords="SetPlayedWith"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static void SetPlayedWith(FSIK_SteamId SteamIdUser);

	/*
	*
	Sets a Rich Presence key/value for the current user that is automatically shared to all friends playing the same game.
	Each user can have up to 20 keys set as defined by k_cchMaxRichPresenceKeys.
	There are two special keys used for viewing/joining games:
	"status" - A UTF-8 string that will show up in the 'view game info' dialog in the Steam friends list.
	"connect" - A UTF-8 string that contains the command-line for how a friend can connect to a game. This enables the 'join game' button in the 'view game info' dialog, in the steam friends list right click menu, and on the players Steam community profile. Be sure your app implements ISteamApps::GetLaunchCommandLine so you can disable the popup warning when launched via a command line.
	There are three additional special keys used by the new Steam Chat:
	"steam_display" - Names a rich presence localization token that will be displayed in the viewing user's selected language in the Steam client UI. See Rich Presence Localization for more info, including a link to a page for testing this rich presence data. If steam_display is not set to a valid localization tag, then rich presence will not be displayed in the Steam client.
	"steam_player_group" - When set, indicates to the Steam client that the player is a member of a particular group. Players in the same group may be organized together in various places in the Steam UI. This string could identify a party, a server, or whatever grouping is relevant for your game. The string itself is not displayed to users.
	"steam_player_group_size" - When set, indicates the total number of players in the steam_player_group. The Steam client may use this number to display additional information about a group when all of the members are not part of a user's friends list. (For example, "Bob, Pete, and 4 more".)
	You can clear all of the keys for the current user with ClearRichPresence.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Set Steam Rich Presence", meta=(Keywords="SetRichPresence"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static bool SetRichPresence(const FString& Key, const FString& Value);

	//After calling RequestEquippedProfileItems, you can use this function to check if the user has a type of profile item equipped or not
	UFUNCTION(BlueprintCallable, DisplayName = "B Has Equipped Profile Item", meta=(Keywords="BHasEquippedProfileItem"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static bool BHasEquippedProfileItem(FSIK_SteamId SteamIdUser, TEnumAsByte<ESIK_ECommunityProfileItemType> ItemType);

	//Returns a string property for a user's equipped profile item
	UFUNCTION(BlueprintCallable, DisplayName = "Get Profile Item Property String", meta=(Keywords="GetProfileItemPropertyString"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static FString GetProfileItemPropertyString(FSIK_SteamId SteamIdUser, TEnumAsByte<ESIK_ECommunityProfileItemType> ItemType, TEnumAsByte<ESIK_ECommunityProfileItemProperty> Property);

	//Returns an unsigned integer property for a user's equipped profile item.
	UFUNCTION(BlueprintCallable, DisplayName = "Get Profile Item Property Uint", meta=(Keywords="GetProfileItemPropertyUint"), Category = "Steam Integration Kit || SDK Functions || Friends")
	static int32 GetProfileItemPropertyUint(FSIK_SteamId SteamIdUser, TEnumAsByte<ESIK_ECommunityProfileItemType> ItemType, TEnumAsByte<ESIK_ECommunityProfileItemProperty> Property);
};
