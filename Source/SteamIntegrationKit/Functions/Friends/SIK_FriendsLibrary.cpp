// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_FriendsLibrary.h"

void USIK_FriendsLibrary::ActivateGameOverlay(const FString& DialogToOpen)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		SteamFriends()->ActivateGameOverlay(TCHAR_TO_ANSI(*DialogToOpen));
	}
#endif
}

void USIK_FriendsLibrary::ActivateGameOverlayInviteDialog(const int64& SteamIdLobby)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		CSteamID SteamId;
		SteamId.SetFromUint64(SteamIdLobby);
		SteamFriends()->ActivateGameOverlayInviteDialog(SteamId);
	}
#endif
}

void USIK_FriendsLibrary::ActivateGameOverlayToStore(const FSIK_AppId& AppID, bool bAddToCartAndShow)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		SteamFriends()->ActivateGameOverlayToStore(AppID.GetAppID(), bAddToCartAndShow ? k_EOverlayToStoreFlag_AddToCartAndShow : k_EOverlayToStoreFlag_None);
	}
#endif
}

void USIK_FriendsLibrary::ActivateGameOverlayToUser(const FString& Dialog, int64 SteamIdUser)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		CSteamID SteamId;
		SteamId.SetFromUint64(SteamIdUser);
		SteamFriends()->ActivateGameOverlayToUser(TCHAR_TO_ANSI(*Dialog), SteamId);
	}
#endif
}

void USIK_FriendsLibrary::ActivateGameOverlayToWebPage(const FString& URL, bool bUseModal)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		SteamFriends()->ActivateGameOverlayToWebPage(TCHAR_TO_ANSI(*URL), bUseModal ? k_EActivateGameOverlayToWebPageMode_Modal : k_EActivateGameOverlayToWebPageMode_Default);
	}
#endif
}

void USIK_FriendsLibrary::ClearRichPresence()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		SteamFriends()->ClearRichPresence();
	}
#endif
}

bool USIK_FriendsLibrary::CloseClanChatWindowInSteam(int64 SteamIdClanChat)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		CSteamID SteamId;
		SteamId.SetFromUint64(SteamIdClanChat);
		return SteamFriends()->CloseClanChatWindowInSteam(SteamId);
	}
	return false;
#else
	return false;
#endif
}

FSIK_SteamId USIK_FriendsLibrary::GetChatMemberByIndex(FSIK_SteamId SteamIdClan, int32 MemberIndex)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		CSteamID SteamId = SteamIdClan.GetSteamID();
		return  SteamFriends()->GetChatMemberByIndex(SteamId, MemberIndex);
	}
	return FSIK_SteamId();
#else
	return FSIK_SteamId();
#endif
}

bool USIK_FriendsLibrary::GetClanActivityCounts(FSIK_SteamId SteamIdClan, int32& Online, int32& InGame, int32& Chatting)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		CSteamID SteamId = SteamIdClan.GetSteamID();
		return SteamFriends()->GetClanActivityCounts(SteamId, &Online, &InGame, &Chatting);
	}
	return false;
#else
	return false;
#endif
}

FSIK_SteamId USIK_FriendsLibrary::GetClanByIndex(int32 ClanIndex)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		return SteamFriends()->GetClanByIndex(ClanIndex);
	}
	return FSIK_SteamId();
#else
	return FSIK_SteamId();
#endif
}

int32 USIK_FriendsLibrary::GetClanChatMemberCount(FSIK_SteamId SteamIdClan)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		CSteamID SteamId = SteamIdClan.GetSteamID();
		return SteamFriends()->GetClanChatMemberCount(SteamId);
	}
	return 0;
#else
	return 0;
#endif
}

int32 USIK_FriendsLibrary::GetClanChatMessage(FSIK_SteamId SteamIdClan, int32 MessageIndex, const TArray<uint8>& Text,
	FSIK_SteamId& SteamIdUser, FString& ChatEntryType)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
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
#else
	return 0;
#endif
}

int32 USIK_FriendsLibrary::GetClanCount()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		return SteamFriends()->GetClanCount();
	}
	return -1;
#else
	return 0;
#endif
}

FString USIK_FriendsLibrary::GetClanName(FSIK_SteamId SteamIdClan)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		CSteamID SteamId = SteamIdClan.GetSteamID();
		return UTF8_TO_TCHAR(SteamFriends()->GetClanName(SteamId));
	}
	return FString();
#else
	return FString();
#endif
}

FSIK_SteamId USIK_FriendsLibrary::GetClanOfficerByIndex(FSIK_SteamId SteamIdClan, int32 OfficerIndex)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		CSteamID SteamId = SteamIdClan.GetSteamID();
		return SteamFriends()->GetClanOfficerByIndex(SteamId, OfficerIndex);
	}
	return FSIK_SteamId();
#else
	return FSIK_SteamId();
#endif
}

int32 USIK_FriendsLibrary::GetClanOfficerCount(FSIK_SteamId SteamIdClan)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		CSteamID SteamId = SteamIdClan.GetSteamID();
		return SteamFriends()->GetClanOfficerCount(SteamId);
	}
	return -1;
#else
	return 0;
#endif
}

FSIK_SteamId USIK_FriendsLibrary::GetClanOwner(FSIK_SteamId SteamIdClan)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		CSteamID SteamId = SteamIdClan.GetSteamID();
		return SteamFriends()->GetClanOwner(SteamId);
	}
	return FSIK_SteamId();
#else
	return FSIK_SteamId();
#endif
}

FString USIK_FriendsLibrary::GetClanTag(FSIK_SteamId SteamIdClan)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		CSteamID SteamId = SteamIdClan.GetSteamID();
		return SteamFriends()->GetClanTag(SteamId);
	}
	return FString();
#else
    	return FString();
#endif
}

FSIK_SteamId USIK_FriendsLibrary::GetCoplayFriend(int32 CoplayFriend)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		return SteamFriends()->GetCoplayFriend(CoplayFriend);
	}
	return FSIK_SteamId();
#else
	return FSIK_SteamId();
#endif
}

int32 USIK_FriendsLibrary::GetCoplayFriendCount()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		return SteamFriends()->GetCoplayFriendCount();
	}
	return -1;
#else
	return 0;
#endif
}

FSIK_SteamId USIK_FriendsLibrary::GetFriendByIndex(int32 FriendIndex, TArray<TEnumAsByte<ESIK_FriendFlags>> FriendFlags)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		int iFriendFlags = 0;
		for (int i = 0; i < FriendFlags.Num(); i++)
		{
#if ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 2
			iFriendFlags |= FriendFlags[i].GetIntValue();
#else
			iFriendFlags |= FriendFlags[i].GetValue();
#endif
		}
		return SteamFriends()->GetFriendByIndex(FriendIndex, iFriendFlags);
	}
	return FSIK_SteamId();
#else
	return FSIK_SteamId();
#endif
}

FSIK_AppId USIK_FriendsLibrary::GetFriendCoplayGame(FSIK_SteamId SteamIdFriend)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		CSteamID SteamId = SteamIdFriend.GetSteamID();
		return SteamFriends()->GetFriendCoplayGame(SteamId);
	}
	return FSIK_AppId();
#else
	return FSIK_AppId();
#endif
}

FDateTime USIK_FriendsLibrary::GetFriendCoplayTime(FSIK_SteamId SteamIdFriend)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		CSteamID SteamId = SteamIdFriend.GetSteamID();
		return FDateTime::FromUnixTimestamp(SteamFriends()->GetFriendCoplayTime(SteamId));
	}
	return FDateTime();
#else
	return FDateTime();
#endif
}

int32 USIK_FriendsLibrary::GetFriendCount(TArray<TEnumAsByte<ESIK_FriendFlags>> FriendFlags)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		int iFriendFlags = 0;
		for (int i = 0; i < FriendFlags.Num(); i++)
		{
#if ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 2
			iFriendFlags |= FriendFlags[i].GetIntValue();
#else
			iFriendFlags |= FriendFlags[i].GetValue();
#endif
		}
		return SteamFriends()->GetFriendCount(iFriendFlags);
	}
	return -1;
#else
	return 0;
#endif
}

int32 USIK_FriendsLibrary::GetFriendCountFromSource(FSIK_SteamId SteamIdSource)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		CSteamID SteamId = SteamIdSource.GetSteamID();
		return SteamFriends()->GetFriendCountFromSource(SteamId);
	}
	return -1;
#else
	return 0;
#endif
}

FSIK_SteamId USIK_FriendsLibrary::GetFriendFromSourceByIndex(FSIK_SteamId SteamIdSource, int32 FriendIndex)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		CSteamID SteamId = SteamIdSource.GetSteamID();
		return SteamFriends()->GetFriendFromSourceByIndex(SteamId, FriendIndex);
	}
	return FSIK_SteamId();
#else
	return FSIK_SteamId();
#endif
}

bool USIK_FriendsLibrary::GetFriendGamePlayed(FSIK_SteamId SteamIdFriend, FSIK_FriendGameInfo& GameInfo)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		CSteamID SteamId = SteamIdFriend.GetSteamID();
		FriendGameInfo_t FriendGameInfo;
		bool bResult = SteamFriends()->GetFriendGamePlayed(SteamId, &FriendGameInfo);
		GameInfo = FriendGameInfo;
		return bResult;
	}
	return false;
#else
	return false;
#endif
}

int32 USIK_FriendsLibrary::GetFriendMessage(FSIK_SteamId SteamIdFriend, int32 MessageIndex, TArray<uint8>& Text, FString& ChatEntryType)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
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
#else
	return 0;
#endif
}

FString USIK_FriendsLibrary::GetFriendPersonaName(FSIK_SteamId SteamIdFriend)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		return UTF8_TO_TCHAR(SteamFriends()->GetFriendPersonaName(SteamIdFriend.GetSteamID()));
	}
	return FString();
#else
	return FString();
#endif
}

FString USIK_FriendsLibrary::GetFriendPersonaNameHistory(FSIK_SteamId SteamIdFriend, int32 PersonaNameIndex)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		return UTF8_TO_TCHAR(SteamFriends()->GetFriendPersonaNameHistory(SteamIdFriend.GetSteamID(), PersonaNameIndex));
	}
	return FString();
#else
	return FString();
#endif
}

TEnumAsByte<ESIK_PersonaState> USIK_FriendsLibrary::GetFriendPersonaState(FSIK_SteamId SteamIdFriend)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		return static_cast<ESIK_PersonaState>(SteamFriends()->GetFriendPersonaState(SteamIdFriend.GetSteamID()));
	}
	return ESIK_PersonaState::PersonaStateOffline;
#else
	return ESIK_PersonaState::PersonaStateOffline;
#endif
}

TEnumAsByte<ESIK_FriendRelationship> USIK_FriendsLibrary::GetFriendRelationship(FSIK_SteamId SteamIdFriend)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		return static_cast<ESIK_FriendRelationship>(SteamFriends()->GetFriendRelationship(SteamIdFriend.GetSteamID()));
	}
	return ESIK_FriendRelationship::FriendRelationshipNone;
#else
	return ESIK_FriendRelationship::FriendRelationshipNone;
#endif
}

FString USIK_FriendsLibrary::GetFriendRichPresence(FSIK_SteamId SteamIdFriend, const FString& Key)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		return UTF8_TO_TCHAR(SteamFriends()->GetFriendRichPresence(SteamIdFriend.GetSteamID(), TCHAR_TO_ANSI(*Key)));
	}
	return FString();
#else
	return FString();
#endif
}

FString USIK_FriendsLibrary::GetFriendRichPresenceKeyByIndex(FSIK_SteamId SteamIdFriend, int32 KeyIndex)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		return UTF8_TO_TCHAR(SteamFriends()->GetFriendRichPresenceKeyByIndex(SteamIdFriend.GetSteamID(), KeyIndex));
	}
	return FString();
#else
	return FString();
#endif
}

int32 USIK_FriendsLibrary::GetFriendRichPresenceKeyCount(FSIK_SteamId SteamIdFriend)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		return SteamFriends()->GetFriendRichPresenceKeyCount(SteamIdFriend.GetSteamID());
	}
	return -1;
#else
	return 0;
#endif
}

int32 USIK_FriendsLibrary::GetFriendGroupCount()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		return SteamFriends()->GetFriendsGroupCount();
	}
	return -1;
#else
	return -1;
#endif
}

FSIK_FriendsGroupID USIK_FriendsLibrary::GetFriendGroupIDByIndex(int32 GroupIndex)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		return SteamFriends()->GetFriendsGroupIDByIndex(GroupIndex);
	}
	return FSIK_FriendsGroupID();
#else
	return FSIK_FriendsGroupID();
#endif
}

int32 USIK_FriendsLibrary::GetFriendGroupMembersCount(FSIK_FriendsGroupID FriendsGroupID)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		return SteamFriends()->GetFriendsGroupMembersCount(FriendsGroupID.GetFriendsGroupID());
	}
	return -1;
#else
	return -1;
#endif
}

TArray<FSIK_SteamId> USIK_FriendsLibrary::GetFriendsGroupMembersList(FSIK_FriendsGroupID FriendsGroupID, int32 MembersCount)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
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
#else
	return TArray<FSIK_SteamId>();
#endif
}

FString USIK_FriendsLibrary::GetFriendsGroupName(FSIK_FriendsGroupID FriendsGroupID)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		return SteamFriends()->GetFriendsGroupName(FriendsGroupID.GetFriendsGroupID());
	}
	return FString();
#else
	return FString();
#endif
}

int32 USIK_FriendsLibrary::GetFriendSteamLevel(FSIK_SteamId SteamIdFriend)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		return SteamFriends()->GetFriendSteamLevel(SteamIdFriend.GetSteamID());
	}
	return -1;
#else
	return -1;
#endif
}

UTexture2D* USIK_FriendsLibrary::GetLargeFriendAvatar(FSIK_SteamId SteamIdFriend, int32& Avatar)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamFriends())
	{
		return nullptr;
	}
	Avatar = SteamFriends()->GetLargeFriendAvatar(SteamIdFriend.GetSteamID());
	if(Avatar == -1)
	{
		return nullptr;
	}
	uint8* AvatarData = new uint8[4 * 184 * 184];
	bool bSuccess = SteamUtils()->GetImageRGBA(Avatar, AvatarData, 4 * 184 * 184);
	if(!bSuccess)
	{
		delete[] AvatarData;
		return nullptr;
	}
	UTexture2D* Texture = UTexture2D::CreateTransient(184, 184,PF_R8G8B8A8);
	if(Texture)
	{
		uint8* MipData = static_cast<uint8*>(Texture->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE));
		FMemory::Memcpy(MipData, AvatarData, 4 * 184 * 184);
		Texture->GetPlatformData()->Mips[0].BulkData.Unlock();
		Texture->UpdateResource();
	}
	delete[] AvatarData;
	return Texture;
#else
	return nullptr;
#endif
}

UTexture2D* USIK_FriendsLibrary::GetMediumFriendAvatar(FSIK_SteamId SteamIdFriend, int32& Avatar)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamFriends())
	{
		return nullptr;
	}
	Avatar = SteamFriends()->GetMediumFriendAvatar(SteamIdFriend.GetSteamID());
	if(Avatar == -1)
	{
		return nullptr;
	}
	uint8* AvatarData = new uint8[4 * 64 * 64];
	bool bSuccess = SteamUtils()->GetImageRGBA(Avatar, AvatarData, 4 * 64 * 64);
	if(!bSuccess)
	{
		delete[] AvatarData;
		return nullptr;
	}
	UTexture2D* Texture = UTexture2D::CreateTransient(64, 64,PF_R8G8B8A8);
	if(Texture)
	{
		uint8* MipData = static_cast<uint8*>(Texture->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE));
		FMemory::Memcpy(MipData, AvatarData, 4 * 64 * 64);
		Texture->GetPlatformData()->Mips[0].BulkData.Unlock();
		Texture->UpdateResource();
	}
	delete[] AvatarData;
	return Texture;
#else
	return nullptr;
#endif
}

FString USIK_FriendsLibrary::GetPersonaName()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		return UTF8_TO_TCHAR(SteamFriends()->GetPersonaName());
	}
	return FString();
#else
	return FString();
#endif
}

TEnumAsByte<ESIK_PersonaState> USIK_FriendsLibrary::GetPersonaState()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		return static_cast<ESIK_PersonaState>(SteamFriends()->GetPersonaState());
	}
	return ESIK_PersonaState::PersonaStateOffline;
#else
	return ESIK_PersonaState::PersonaStateOffline;
#endif
}

FString USIK_FriendsLibrary::GetPlayerNickname(FSIK_SteamId SteamIdPlayer)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		return UTF8_TO_TCHAR(SteamFriends()->GetPlayerNickname(SteamIdPlayer.GetSteamID()));
	}
	return FString();
#else
	return FString();
#endif
}

UTexture2D* USIK_FriendsLibrary::GetSmallFriendAvatar(FSIK_SteamId SteamIdFriend, int32& Avatar)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamFriends())
	{
		return nullptr;
	}
	Avatar = SteamFriends()->GetSmallFriendAvatar(SteamIdFriend.GetSteamID());
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
#else
	return nullptr;
#endif
}

int32 USIK_FriendsLibrary::GetUserRestrictions()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		return SteamFriends()->GetUserRestrictions();
	}
	return -1;
#else
	return -1;
#endif
}

bool USIK_FriendsLibrary::HasFriend(FSIK_SteamId SteamIdFriend, TArray<TEnumAsByte<ESIK_FriendFlags>> FriendFlags)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		int iFriendFlags = 0;
		for (int i = 0; i < FriendFlags.Num(); i++)
		{
#if ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 2
			iFriendFlags |= FriendFlags[i].GetIntValue();
#else
			iFriendFlags |= FriendFlags[i].GetValue();
#endif
		}
		return SteamFriends()->HasFriend(SteamIdFriend.GetSteamID(), iFriendFlags);
	}
	return false;
#else
	return false;
#endif
}

bool USIK_FriendsLibrary::InviteUserToGame(FSIK_SteamId SteamIdFriend, const FString& ConnectString)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		return SteamFriends()->InviteUserToGame(SteamIdFriend.GetSteamID(), TCHAR_TO_ANSI(*ConnectString));
	}
	return false;
#else
	return false;
#endif
}

bool USIK_FriendsLibrary::IsClanChatAdmin(FSIK_SteamId SteamIdClanChat, FSIK_SteamId SteamIdUser)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		CSteamID SteamId1 = SteamIdClanChat.GetSteamID();
		CSteamID SteamId2 = SteamIdUser.GetSteamID();
		return SteamFriends()->IsClanChatAdmin(SteamId1, SteamId2);
	}
	return false;
#else
	return false;
#endif
}

bool USIK_FriendsLibrary::IsClanPublic(FSIK_SteamId SteamIdClan)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		CSteamID SteamId = SteamIdClan.GetSteamID();
		return SteamFriends()->IsClanPublic(SteamId);
	}
	return false;
#else
	return false;
#endif
}

bool USIK_FriendsLibrary::IsClanOfficialGameGroup(FSIK_SteamId SteamIdClan)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		CSteamID SteamId = SteamIdClan.GetSteamID();
		return SteamFriends()->IsClanOfficialGameGroup(SteamId);
	}
	return false;
#else
	return false;
#endif
}

bool USIK_FriendsLibrary::IsClanChatWindowOpenInSteam(FSIK_SteamId SteamIdClanChat)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		CSteamID SteamId = SteamIdClanChat.GetSteamID();
		return SteamFriends()->IsClanChatWindowOpenInSteam(SteamId);
	}
	return false;
#else
	return false;
#endif
}

bool USIK_FriendsLibrary::IsFollowing(FSIK_SteamId SteamIdFriend)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		SteamFriends()->IsFollowing(SteamIdFriend.GetSteamID());
		return true;
	}
	return false;
#else
	return false;
#endif
}

bool USIK_FriendsLibrary::IsUserInSource(FSIK_SteamId SteamIdFriend, FSIK_SteamId SteamIdSource)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		return SteamFriends()->IsUserInSource(SteamIdFriend.GetSteamID(), SteamIdSource.GetSteamID());
	}
	return false;
#else
	return false;
#endif
}

bool USIK_FriendsLibrary::LeaveClanChatRoom(FSIK_SteamId SteamIdClanChat)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		CSteamID SteamId = SteamIdClanChat.GetSteamID();
		return SteamFriends()->LeaveClanChatRoom(SteamId);
	}
	return false;
#else
	return false;
#endif
}

bool USIK_FriendsLibrary::ReplyToFriendMessage(FSIK_SteamId SteamIdFriend, const FString& Text)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		return SteamFriends()->ReplyToFriendMessage(SteamIdFriend.GetSteamID(), TCHAR_TO_ANSI(*Text));
	}
	return false;
#else
	return false;
#endif
}

void USIK_FriendsLibrary::RequestFriendRichPresence(FSIK_SteamId SteamIdFriend)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		SteamFriends()->RequestFriendRichPresence(SteamIdFriend.GetSteamID());
	}
#endif
}

bool USIK_FriendsLibrary::RequestUserInfo(FSIK_SteamId SteamIdUser, bool bRequireNameOnly)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		CSteamID SteamId = SteamIdUser.GetSteamID();
		return SteamFriends()->RequestUserInformation(SteamId, bRequireNameOnly);
	}
	return false;
#else
	return false;
#endif
}

bool USIK_FriendsLibrary::SendClanChatMessage(FSIK_SteamId SteamIdClanChat, const FString& Text)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		CSteamID SteamId = SteamIdClanChat.GetSteamID();
		return SteamFriends()->SendClanChatMessage(SteamId, TCHAR_TO_ANSI(*Text));
	}
	return false;
#else
	return false;
#endif
}

void USIK_FriendsLibrary::SetInGameVoiceSpeaking(FSIK_SteamId SteamIdFriend, bool bSpeaking)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		SteamFriends()->SetInGameVoiceSpeaking(SteamIdFriend.GetSteamID(), bSpeaking);
	}
#endif
}

void USIK_FriendsLibrary::SetListenForFriendMessage(bool bInterceptEnabled)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		SteamFriends()->SetListenForFriendsMessages(bInterceptEnabled);
	}
#endif
}

void USIK_FriendsLibrary::SetPlayedWith(FSIK_SteamId SteamIdUser)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		CSteamID SteamId = SteamIdUser.GetSteamID();
		SteamFriends()->SetPlayedWith(SteamId);
	}
#endif
}

bool USIK_FriendsLibrary::SetRichPresence(const FString& Key, const FString& Value)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() != nullptr)
	{
		return SteamFriends()->SetRichPresence(TCHAR_TO_ANSI(*Key), TCHAR_TO_ANSI(*Value));
	}
	return false;
#else
	return false;
#endif
}

bool USIK_FriendsLibrary::BHasEquippedProfileItem(FSIK_SteamId SteamIdUser,
	TEnumAsByte<ESIK_ECommunityProfileItemType> ItemType)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
#if WITH_ENGINE_STEAM
	return false;
#else
	if(SteamFriends() != nullptr)
	{
		return SteamFriends()->BHasEquippedProfileItem(SteamIdUser.GetSteamID(), static_cast<ECommunityProfileItemType>(ItemType.GetValue()));
	}
	return false;
#endif
#else
	return false;
#endif
}

FString USIK_FriendsLibrary::GetProfileItemPropertyString(FSIK_SteamId SteamIdUser,
	TEnumAsByte<ESIK_ECommunityProfileItemType> ItemType, TEnumAsByte<ESIK_ECommunityProfileItemProperty> Property)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
#if WITH_ENGINE_STEAM
	return FString();
#else
	if(SteamFriends() != nullptr)
	{
		return SteamFriends()->GetProfileItemPropertyString(SteamIdUser.GetSteamID(), static_cast<ECommunityProfileItemType>(ItemType.GetValue()), static_cast<ECommunityProfileItemProperty>(Property.GetValue()));
	}
	return FString();
#endif
#else
	return FString();
#endif
}

int32 USIK_FriendsLibrary::GetProfileItemPropertyUint(FSIK_SteamId SteamIdUser,
	TEnumAsByte<ESIK_ECommunityProfileItemType> ItemType, TEnumAsByte<ESIK_ECommunityProfileItemProperty> Property)
{
	
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
#if WITH_ENGINE_STEAM
	return -1;
#else
	if(SteamFriends() != nullptr)
	{
		return SteamFriends()->GetProfileItemPropertyUint(SteamIdUser.GetSteamID(), static_cast<ECommunityProfileItemType>(ItemType.GetValue()), static_cast<ECommunityProfileItemProperty>(Property.GetValue()));
	}
	return -1;
#endif
#else
	return -1;
#endif
}