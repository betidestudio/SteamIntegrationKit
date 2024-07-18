// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_FriendsLibrary.h"

void USIK_FriendsLibrary::ActivateGameOverlay(const FString& DialogToOpen)
{
	if(SteamFriends() != nullptr)
	{
		SteamFriends()->ActivateGameOverlay(TCHAR_TO_ANSI(*DialogToOpen));
	}
}

void USIK_FriendsLibrary::ActivateGameOverlayInviteDialog(const int64& SteamIdLobby)
{
	if(SteamFriends() != nullptr)
	{
		CSteamID SteamId;
		SteamId.SetFromUint64(SteamIdLobby);
		SteamFriends()->ActivateGameOverlayInviteDialog(SteamId);
	}
}

void USIK_FriendsLibrary::ActivateGameOverlayToStore(const FSIK_AppId& AppID, bool bAddToCartAndShow)
{
	if(SteamFriends() != nullptr)
	{
		SteamFriends()->ActivateGameOverlayToStore(AppID.GetAppID(), bAddToCartAndShow ? k_EOverlayToStoreFlag_AddToCartAndShow : k_EOverlayToStoreFlag_None);
	}
}

void USIK_FriendsLibrary::ActivateGameOverlayToUser(const FString& Dialog, int64 SteamIdUser)
{
	if(SteamFriends() != nullptr)
	{
		CSteamID SteamId;
		SteamId.SetFromUint64(SteamIdUser);
		SteamFriends()->ActivateGameOverlayToUser(TCHAR_TO_ANSI(*Dialog), SteamId);
	}
}

void USIK_FriendsLibrary::ActivateGameOverlayToWebPage(const FString& URL, bool bUseModal)
{
	if(SteamFriends() != nullptr)
	{
		SteamFriends()->ActivateGameOverlayToWebPage(TCHAR_TO_ANSI(*URL), bUseModal ? k_EActivateGameOverlayToWebPageMode_Modal : k_EActivateGameOverlayToWebPageMode_Default);
	}
}

void USIK_FriendsLibrary::ClearRichPresence()
{
	if(SteamFriends() != nullptr)
	{
		SteamFriends()->ClearRichPresence();
	}
}

bool USIK_FriendsLibrary::CloseClanChatWindowInSteam(int64 SteamIdClanChat)
{
	if(SteamFriends() != nullptr)
	{
		CSteamID SteamId;
		SteamId.SetFromUint64(SteamIdClanChat);
		return SteamFriends()->CloseClanChatWindowInSteam(SteamId);
	}
	return false;
}

FSIK_SteamId USIK_FriendsLibrary::GetChatMemberByIndex(FSIK_SteamId SteamIdClan, int32 MemberIndex)
{
	if(SteamFriends() != nullptr)
	{
		CSteamID SteamId = SteamIdClan.GetSteamID();
		return  SteamFriends()->GetChatMemberByIndex(SteamId, MemberIndex);
	}
	return FSIK_SteamId();
}

bool USIK_FriendsLibrary::GetClanActivityCounts(FSIK_SteamId SteamIdClan, int32& Online, int32& InGame, int32& Chatting)
{
	if(SteamFriends() != nullptr)
	{
		CSteamID SteamId = SteamIdClan.GetSteamID();
		return SteamFriends()->GetClanActivityCounts(SteamId, &Online, &InGame, &Chatting);
	}
	return false;
}

FSIK_SteamId USIK_FriendsLibrary::GetClanByIndex(int32 ClanIndex)
{
	if(SteamFriends() != nullptr)
	{
		return SteamFriends()->GetClanByIndex(ClanIndex);
	}
	return FSIK_SteamId();
}

int32 USIK_FriendsLibrary::GetClanChatMemberCount(FSIK_SteamId SteamIdClan)
{
	if(SteamFriends() != nullptr)
	{
		CSteamID SteamId = SteamIdClan.GetSteamID();
		return SteamFriends()->GetClanChatMemberCount(SteamId);
	}
	return 0;
}

int32 USIK_FriendsLibrary::GetClanChatMessage(FSIK_SteamId SteamIdClan, int32 MessageIndex, const TArray<uint8>& Text,
	FSIK_SteamId& SteamIdUser, FString& ChatEntryType)
{
	if(SteamFriends() != nullptr)
	{
		CSteamID SteamId = SteamIdClan.GetSteamID();
		CSteamID SteamIdUserOut;
		EChatEntryType EChatEntryType2;
		int32 Result = SteamFriends()->GetClanChatMessage(SteamId, MessageIndex, (char*)Text.GetData(), Text.Num(),&EChatEntryType2, &SteamIdUserOut);
		SteamIdUser = SteamIdUserOut;
		ChatEntryType = FString::Printf(TEXT("%d"), EChatEntryType2);
		return Result;
	}
	return 0;
}

int32 USIK_FriendsLibrary::GetClanCount()
{
	if(SteamFriends() != nullptr)
	{
		return SteamFriends()->GetClanCount();
	}
	return -1;
}

FString USIK_FriendsLibrary::GetClanName(FSIK_SteamId SteamIdClan)
{
	if(SteamFriends() != nullptr)
	{
		CSteamID SteamId = SteamIdClan.GetSteamID();
		return SteamFriends()->GetClanName(SteamId);
	}
	return FString();
}

FSIK_SteamId USIK_FriendsLibrary::GetClanOfficerByIndex(FSIK_SteamId SteamIdClan, int32 OfficerIndex)
{
	if(SteamFriends() != nullptr)
	{
		CSteamID SteamId = SteamIdClan.GetSteamID();
		return SteamFriends()->GetClanOfficerByIndex(SteamId, OfficerIndex);
	}
	return FSIK_SteamId();
}

int32 USIK_FriendsLibrary::GetClanOfficerCount(FSIK_SteamId SteamIdClan)
{
	if(SteamFriends() != nullptr)
	{
		CSteamID SteamId = SteamIdClan.GetSteamID();
		return SteamFriends()->GetClanOfficerCount(SteamId);
	}
	return -1;
}

FSIK_SteamId USIK_FriendsLibrary::GetClanOwner(FSIK_SteamId SteamIdClan)
{
	if(SteamFriends() != nullptr)
	{
		CSteamID SteamId = SteamIdClan.GetSteamID();
		return SteamFriends()->GetClanOwner(SteamId);
	}
	return FSIK_SteamId();
}

FString USIK_FriendsLibrary::GetClanTag(FSIK_SteamId SteamIdClan)
{
	if(SteamFriends() != nullptr)
	{
		CSteamID SteamId = SteamIdClan.GetSteamID();
		return SteamFriends()->GetClanTag(SteamId);
	}
	return FString();
}

FSIK_SteamId USIK_FriendsLibrary::GetCoplayFriend(int32 CoplayFriend)
{
	if(SteamFriends() != nullptr)
	{
		return SteamFriends()->GetCoplayFriend(CoplayFriend);
	}
	return FSIK_SteamId();
}

int32 USIK_FriendsLibrary::GetCoplayFriendCount()
{
	if(SteamFriends() != nullptr)
	{
		return SteamFriends()->GetCoplayFriendCount();
	}
	return -1;
}

FSIK_SteamId USIK_FriendsLibrary::GetFriendByIndex(int32 FriendIndex, TArray<TEnumAsByte<ESIK_FriendFlags>> FriendFlags)
{
	if(SteamFriends() != nullptr)
	{
		int iFriendFlags = 0;
		for (int i = 0; i < FriendFlags.Num(); i++)
		{
			iFriendFlags |= FriendFlags[i].GetIntValue();
		}
		return SteamFriends()->GetFriendByIndex(FriendIndex, iFriendFlags);
	}
	return FSIK_SteamId();
}

FSIK_AppId USIK_FriendsLibrary::GetFriendCoplayGame(FSIK_SteamId SteamIdFriend)
{
	if(SteamFriends() != nullptr)
	{
		CSteamID SteamId = SteamIdFriend.GetSteamID();
		return SteamFriends()->GetFriendCoplayGame(SteamId);
	}
	return FSIK_AppId();
}

FDateTime USIK_FriendsLibrary::GetFriendCoplayTime(FSIK_SteamId SteamIdFriend)
{
	if(SteamFriends() != nullptr)
	{
		CSteamID SteamId = SteamIdFriend.GetSteamID();
		return FDateTime::FromUnixTimestamp(SteamFriends()->GetFriendCoplayTime(SteamId));
	}
	return FDateTime();
}

int32 USIK_FriendsLibrary::GetFriendCount(TArray<TEnumAsByte<ESIK_FriendFlags>> FriendFlags)
{
	if(SteamFriends() != nullptr)
	{
		int iFriendFlags = 0;
		for (int i = 0; i < FriendFlags.Num(); i++)
		{
			iFriendFlags |= FriendFlags[i].GetIntValue();
			UE_LOG(LogTemp, Warning, TEXT("FriendFlags: %d"), iFriendFlags);
		}
		return SteamFriends()->GetFriendCount(iFriendFlags);
	}
	return -1;
}

int32 USIK_FriendsLibrary::GetFriendCountFromSource(FSIK_SteamId SteamIdSource)
{
	if(SteamFriends() != nullptr)
	{
		CSteamID SteamId = SteamIdSource.GetSteamID();
		return SteamFriends()->GetFriendCountFromSource(SteamId);
	}
	return -1;
}

FSIK_SteamId USIK_FriendsLibrary::GetFriendFromSourceByIndex(FSIK_SteamId SteamIdSource, int32 FriendIndex)
{
	if(SteamFriends() != nullptr)
	{
		CSteamID SteamId = SteamIdSource.GetSteamID();
		return SteamFriends()->GetFriendFromSourceByIndex(SteamId, FriendIndex);
	}
	return FSIK_SteamId();
}

bool USIK_FriendsLibrary::GetFriendGamePlayed(FSIK_SteamId SteamIdFriend, FSIK_FriendGameInfo& GameInfo)
{
	if(SteamFriends() != nullptr)
	{
		CSteamID SteamId = SteamIdFriend.GetSteamID();
		FriendGameInfo_t FriendGameInfo;
		bool bResult = SteamFriends()->GetFriendGamePlayed(SteamId, &FriendGameInfo);
		GameInfo = FriendGameInfo;
		return bResult;
	}
	return false;
}

int32 USIK_FriendsLibrary::GetFriendMessage(FSIK_SteamId SteamIdFriend, int32 MessageIndex, TArray<uint8>& Text, FString& ChatEntryType)
{
	if(SteamFriends() != nullptr)
	{
		void *pText;
		int32 nSize = 0;
		EChatEntryType ChatEntryTypeV;
		int32 Val = SteamFriends()->GetFriendMessage(SteamIdFriend.GetSteamID(), MessageIndex, &pText, nSize, &ChatEntryTypeV);
		Text.SetNum(nSize);
		FMemory::Memcpy(Text.GetData(), pText, nSize);
		ChatEntryType = FString::Printf(TEXT("%d"), ChatEntryTypeV);
		return Val;
	}
	return 0;
}

FString USIK_FriendsLibrary::GetFriendPersonaName(FSIK_SteamId SteamIdFriend)
{
	if(SteamFriends() != nullptr)
	{
		return SteamFriends()->GetFriendPersonaName(SteamIdFriend.GetSteamID());
	}
	return FString();
}

FString USIK_FriendsLibrary::GetFriendPersonaNameHistory(FSIK_SteamId SteamIdFriend, int32 PersonaNameIndex)
{
	if(SteamFriends() != nullptr)
	{
		return SteamFriends()->GetFriendPersonaNameHistory(SteamIdFriend.GetSteamID(), PersonaNameIndex);
	}
	return FString();
}

TEnumAsByte<ESIK_PersonaState> USIK_FriendsLibrary::GetFriendPersonaState(FSIK_SteamId SteamIdFriend)
{
	if(SteamFriends() != nullptr)
	{
		return static_cast<ESIK_PersonaState>(SteamFriends()->GetFriendPersonaState(SteamIdFriend.GetSteamID()));
	}
	return ESIK_PersonaState::PersonaStateOffline;
}

TEnumAsByte<ESIK_FriendRelationship> USIK_FriendsLibrary::GetFriendRelationship(FSIK_SteamId SteamIdFriend)
{
	if(SteamFriends() != nullptr)
	{
		return static_cast<ESIK_FriendRelationship>(SteamFriends()->GetFriendRelationship(SteamIdFriend.GetSteamID()));
	}
	return ESIK_FriendRelationship::FriendRelationshipNone;
}

FString USIK_FriendsLibrary::GetFriendRichPresence(FSIK_SteamId SteamIdFriend, const FString& Key)
{
	if(SteamFriends() != nullptr)
	{
		return SteamFriends()->GetFriendRichPresence(SteamIdFriend.GetSteamID(), TCHAR_TO_ANSI(*Key));
	}
	return FString();
}

FString USIK_FriendsLibrary::GetFriendRichPresenceKeyByIndex(FSIK_SteamId SteamIdFriend, int32 KeyIndex)
{
	if(SteamFriends() != nullptr)
	{
		return SteamFriends()->GetFriendRichPresenceKeyByIndex(SteamIdFriend.GetSteamID(), KeyIndex);
	}
	return FString();
}

int32 USIK_FriendsLibrary::GetFriendRichPresenceKeyCount(FSIK_SteamId SteamIdFriend)
{
	if(SteamFriends() != nullptr)
	{
		return SteamFriends()->GetFriendRichPresenceKeyCount(SteamIdFriend.GetSteamID());
	}
	return -1;
}

int32 USIK_FriendsLibrary::GetFriendGroupCount()
{
	if(SteamFriends() != nullptr)
	{
		return SteamFriends()->GetFriendsGroupCount();
	}
	return -1;
}

FSIK_FriendsGroupID USIK_FriendsLibrary::GetFriendGroupIDByIndex(int32 GroupIndex)
{
	if(SteamFriends() != nullptr)
	{
		return SteamFriends()->GetFriendsGroupIDByIndex(GroupIndex);
	}
	return FSIK_FriendsGroupID();
}

int32 USIK_FriendsLibrary::GetFriendGroupMembersCount(FSIK_FriendsGroupID FriendsGroupID)
{
	if(SteamFriends() != nullptr)
	{
		return SteamFriends()->GetFriendsGroupMembersCount(FriendsGroupID.GetFriendsGroupID());
	}
	return -1;
}

TArray<FSIK_SteamId> USIK_FriendsLibrary::GetFriendsGroupMembersList(FSIK_FriendsGroupID FriendsGroupID, int32 MembersCount)
{
	if(SteamFriends() != nullptr)
	{
		int32 nCount = SteamFriends()->GetFriendsGroupMembersCount(FriendsGroupID.GetFriendsGroupID());
		TArray<FSIK_SteamId> FriendsList;
		CSteamID SteamId1[50];
		SteamFriends()->GetFriendsGroupMembersList(FriendsGroupID.GetFriendsGroupID(), SteamId1, MembersCount);
		for (int32 i = 0; i < nCount; i++)
		{
			FriendsList.Add(FSIK_SteamId(SteamId1[i].ConvertToUint64()));
		}
		return FriendsList;
	}
	return TArray<FSIK_SteamId>();
}

FString USIK_FriendsLibrary::GetFriendsGroupName(FSIK_FriendsGroupID FriendsGroupID)
{
	if(SteamFriends() != nullptr)
	{
		return SteamFriends()->GetFriendsGroupName(FriendsGroupID.GetFriendsGroupID());
	}
	return FString();
}

int32 USIK_FriendsLibrary::GetFriendSteamLevel(FSIK_SteamId SteamIdFriend)
{
	if(SteamFriends() != nullptr)
	{
		return SteamFriends()->GetFriendSteamLevel(SteamIdFriend.GetSteamID());
	}
	return -1;
}

int32 USIK_FriendsLibrary::GetLargeFriendAvatar(FSIK_SteamId SteamIdFriend)
{
	if(SteamFriends() != nullptr)
	{
		return SteamFriends()->GetLargeFriendAvatar(SteamIdFriend.GetSteamID());
	}
	return -1;
}

int32 USIK_FriendsLibrary::GetMediumFriendAvatar(FSIK_SteamId SteamIdFriend)
{
	if(SteamFriends() != nullptr)
	{
		return SteamFriends()->GetMediumFriendAvatar(SteamIdFriend.GetSteamID());
	}
	return -1;
}

FString USIK_FriendsLibrary::GetPersonaName()
{
	if(SteamFriends() != nullptr)
	{
		return UTF8_TO_TCHAR(SteamFriends()->GetPersonaName());
	}
	return FString();
}

TEnumAsByte<ESIK_PersonaState> USIK_FriendsLibrary::GetPersonaState()
{
	if(SteamFriends() != nullptr)
	{
		return static_cast<ESIK_PersonaState>(SteamFriends()->GetPersonaState());
	}
	return ESIK_PersonaState::PersonaStateOffline;
}

FString USIK_FriendsLibrary::GetPlayerNickname(FSIK_SteamId SteamIdPlayer)
{
	if(SteamFriends() != nullptr)
	{
		return UTF8_TO_TCHAR(SteamFriends()->GetPlayerNickname(SteamIdPlayer.GetSteamID()));
	}
	return FString();
}

UTexture2D* USIK_FriendsLibrary::GetSmallFriendAvatar(FSIK_SteamId SteamIdFriend)
{
	if(!SteamFriends())
	{
		return nullptr;
	}
	int Avatar = SteamFriends()->GetSmallFriendAvatar(SteamIdFriend.GetSteamID());
	if(Avatar == -1)
	{
		return nullptr;
	}
	uint8* AvatarData = new uint8[4 * 32 * 32];
	bool bSuccess = SteamUtils()->GetImageRGBA(Avatar, AvatarData, 4 * 32 * 32);
	if(!bSuccess)
	{
		delete[] AvatarData;
		return nullptr;
	}
	UTexture2D* Texture = UTexture2D::CreateTransient(32, 32,PF_R8G8B8A8);
	if(Texture)
	{
		uint8* MipData = static_cast<uint8*>(Texture->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE));
		FMemory::Memcpy(MipData, AvatarData, 4 * 32 * 32);
		Texture->GetPlatformData()->Mips[0].BulkData.Unlock();
		Texture->UpdateResource();
	}
	delete[] AvatarData;
	return Texture;
}

int32 USIK_FriendsLibrary::GetUserRestrictions()
{
	if(SteamFriends() != nullptr)
	{
		return SteamFriends()->GetUserRestrictions();
	}
	return -1;
}

bool USIK_FriendsLibrary::HasFriend(FSIK_SteamId SteamIdFriend, TArray<TEnumAsByte<ESIK_FriendFlags>> FriendFlags)
{
	if(SteamFriends() != nullptr)
	{
		int iFriendFlags = 0;
		for (int i = 0; i < FriendFlags.Num(); i++)
		{
			iFriendFlags |= FriendFlags[i].GetIntValue();
		}
		return SteamFriends()->HasFriend(SteamIdFriend.GetSteamID(), iFriendFlags);
	}
	return false;
}

bool USIK_FriendsLibrary::InviteUserToGame(FSIK_SteamId SteamIdFriend, const FString& ConnectString)
{
	if(SteamFriends() != nullptr)
	{
		return SteamFriends()->InviteUserToGame(SteamIdFriend.GetSteamID(), TCHAR_TO_ANSI(*ConnectString));
	}
	return false;
}

bool USIK_FriendsLibrary::IsClanChatAdmin(FSIK_SteamId SteamIdClanChat, FSIK_SteamId SteamIdUser)
{
	if(SteamFriends() != nullptr)
	{
		CSteamID SteamId1 = SteamIdClanChat.GetSteamID();
		CSteamID SteamId2 = SteamIdUser.GetSteamID();
		return SteamFriends()->IsClanChatAdmin(SteamId1, SteamId2);
	}
	return false;
}

bool USIK_FriendsLibrary::IsClanPublic(FSIK_SteamId SteamIdClan)
{
	if(SteamFriends() != nullptr)
	{
		CSteamID SteamId = SteamIdClan.GetSteamID();
		return SteamFriends()->IsClanPublic(SteamId);
	}
	return false;
}

bool USIK_FriendsLibrary::IsClanOfficialGameGroup(FSIK_SteamId SteamIdClan)
{
	if(SteamFriends() != nullptr)
	{
		CSteamID SteamId = SteamIdClan.GetSteamID();
		return SteamFriends()->IsClanOfficialGameGroup(SteamId);
	}
	return false;
}

bool USIK_FriendsLibrary::IsClanChatWindowOpenInSteam(FSIK_SteamId SteamIdClanChat)
{
	if(SteamFriends() != nullptr)
	{
		CSteamID SteamId = SteamIdClanChat.GetSteamID();
		return SteamFriends()->IsClanChatWindowOpenInSteam(SteamId);
	}
	return false;
}

bool USIK_FriendsLibrary::IsFollowing(FSIK_SteamId SteamIdFriend)
{
	if(SteamFriends() != nullptr)
	{
		SteamFriends()->IsFollowing(SteamIdFriend.GetSteamID());
		return true;
	}
	return false;
}

bool USIK_FriendsLibrary::IsUserInSource(FSIK_SteamId SteamIdFriend, FSIK_SteamId SteamIdSource)
{
	if(SteamFriends() != nullptr)
	{
		return SteamFriends()->IsUserInSource(SteamIdFriend.GetSteamID(), SteamIdSource.GetSteamID());
	}
	return false;
}

bool USIK_FriendsLibrary::LeaveClanChatRoom(FSIK_SteamId SteamIdClanChat)
{
	if(SteamFriends() != nullptr)
	{
		CSteamID SteamId = SteamIdClanChat.GetSteamID();
		return SteamFriends()->LeaveClanChatRoom(SteamId);
	}
	return false;
}

bool USIK_FriendsLibrary::ReplyToFriendMessage(FSIK_SteamId SteamIdFriend, const FString& Text)
{
	if(SteamFriends() != nullptr)
	{
		return SteamFriends()->ReplyToFriendMessage(SteamIdFriend.GetSteamID(), TCHAR_TO_ANSI(*Text));
	}
	return false;
}

void USIK_FriendsLibrary::RequestFriendRichPresence(FSIK_SteamId SteamIdFriend)
{
	if(SteamFriends() != nullptr)
	{
		SteamFriends()->RequestFriendRichPresence(SteamIdFriend.GetSteamID());
	}
}

bool USIK_FriendsLibrary::RequestUserInfo(FSIK_SteamId SteamIdUser, bool bRequireNameOnly)
{
	if(SteamFriends() != nullptr)
	{
		CSteamID SteamId = SteamIdUser.GetSteamID();
		return SteamFriends()->RequestUserInformation(SteamId, bRequireNameOnly);
	}
	return false;
}

bool USIK_FriendsLibrary::SendClanChatMessage(FSIK_SteamId SteamIdClanChat, const FString& Text)
{
	if(SteamFriends() != nullptr)
	{
		CSteamID SteamId = SteamIdClanChat.GetSteamID();
		return SteamFriends()->SendClanChatMessage(SteamId, TCHAR_TO_ANSI(*Text));
	}
	return false;
}

void USIK_FriendsLibrary::SetInGameVoiceSpeaking(FSIK_SteamId SteamIdFriend, bool bSpeaking)
{
	if(SteamFriends() != nullptr)
	{
		SteamFriends()->SetInGameVoiceSpeaking(SteamIdFriend.GetSteamID(), bSpeaking);
	}
}

void USIK_FriendsLibrary::SetListenForFriendMessage(bool bInterceptEnabled)
{
	if(SteamFriends() != nullptr)
	{
		SteamFriends()->SetListenForFriendsMessages(bInterceptEnabled);
	}
}

void USIK_FriendsLibrary::SetPlayedWith(FSIK_SteamId SteamIdUser)
{
	if(SteamFriends() != nullptr)
	{
		CSteamID SteamId = SteamIdUser.GetSteamID();
		SteamFriends()->SetPlayedWith(SteamId);
	}
}

bool USIK_FriendsLibrary::SetRichPresence(const FString& Key, const FString& Value)
{
	if(SteamFriends() != nullptr)
	{
		return SteamFriends()->SetRichPresence(TCHAR_TO_ANSI(*Key), TCHAR_TO_ANSI(*Value));
	}
	return false;
}

bool USIK_FriendsLibrary::BHasEquippedProfileItem(FSIK_SteamId SteamIdUser,
	TEnumAsByte<ESIK_ECommunityProfileItemType> ItemType)
{
#if WITH_ENGINE_STEAM
	return false;
#else
	if(SteamFriends() != nullptr)
	{
		return SteamFriends()->BHasEquippedProfileItem(SteamIdUser.GetSteamID(), static_cast<ECommunityProfileItemType>(ItemType.GetValue()));
	}
	return false;
#endif
}

FString USIK_FriendsLibrary::GetProfileItemPropertyString(FSIK_SteamId SteamIdUser,
	TEnumAsByte<ESIK_ECommunityProfileItemType> ItemType, TEnumAsByte<ESIK_ECommunityProfileItemProperty> Property)
{
#if WITH_ENGINE_STEAM
	return FString();
#else
	if(SteamFriends() != nullptr)
	{
		return SteamFriends()->GetProfileItemPropertyString(SteamIdUser.GetSteamID(), static_cast<ECommunityProfileItemType>(ItemType.GetValue()), static_cast<ECommunityProfileItemProperty>(Property.GetValue()));
	}
	return FString();
#endif
}

int32 USIK_FriendsLibrary::GetProfileItemPropertyUint(FSIK_SteamId SteamIdUser,
	TEnumAsByte<ESIK_ECommunityProfileItemType> ItemType, TEnumAsByte<ESIK_ECommunityProfileItemProperty> Property)
{
#if WITH_ENGINE_STEAM
	return -1;
#else
	if(SteamFriends() != nullptr)
	{
		return SteamFriends()->GetProfileItemPropertyUint(SteamIdUser.GetSteamID(), static_cast<ECommunityProfileItemType>(ItemType.GetValue()), static_cast<ECommunityProfileItemProperty>(Property.GetValue()));
	}
	return -1;
#endif
}