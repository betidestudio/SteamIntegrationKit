// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_MatchmakingLibrary.h"
#include "Serialization/MemoryReader.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "Containers/StringConv.h"

int32 USIK_MatchmakingLibrary::AddFavoriteGame(FSIK_AppId AppID, FString IP, int32 ConnPort, int32 QueryPort,
                                               TArray<int32> Flags, int32 Time32LastPlayedOnServer)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMatchmaking())
	{
		return -1;
	}
	int Data = 0;
	for (int i = 0; i < Flags.Num(); i++)
	{
		Data |= Flags[i];
	}
	FIPv4Address Var_Address;
	FIPv4Address::Parse(IP, Var_Address);
	return SteamMatchmaking()->AddFavoriteGame(AppID.GetAppID(), Var_Address.Value, ConnPort, QueryPort, Data, Time32LastPlayedOnServer);
#else
	return -1;
#endif
}

void USIK_MatchmakingLibrary::AddRequestLobbyListCompatibleMembersFilter(FSIK_SteamId SteamID)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMatchmaking())
	{
		return;
	}
	SteamMatchmaking()->AddRequestLobbyListCompatibleMembersFilter(SteamID.GetSteamID());
#endif
}

void USIK_MatchmakingLibrary::AddRequestLobbyListDistanceFilter(
	TEnumAsByte<ESIK_LobbyDistanceFilter> LobbyDistanceFilter)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMatchmaking())
	{
		return;
	}
	SteamMatchmaking()->AddRequestLobbyListDistanceFilter(static_cast<ELobbyDistanceFilter>(LobbyDistanceFilter.GetValue()));
#endif
}

void USIK_MatchmakingLibrary::AddRequestLobbyListFilterSlotsAvailable(int32 SlotsAvailable)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMatchmaking())
	{
		return;
	}
	SteamMatchmaking()->AddRequestLobbyListFilterSlotsAvailable(SlotsAvailable);
#endif
}

void USIK_MatchmakingLibrary::AddRequestLobbyListNearValueFilter(FString KeyToMatch, int32 ValueToBeCloseTo)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMatchmaking())
	{
		return;
	}
	SteamMatchmaking()->AddRequestLobbyListNearValueFilter(TCHAR_TO_ANSI(*KeyToMatch), ValueToBeCloseTo);
#endif
}

void USIK_MatchmakingLibrary::AddRequestLobbyListNumericalFilter(FString KeyToMatch, int32 ValueToMatch,
	TEnumAsByte<ESIK_LobbyComparisonType> ComparisonType)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMatchmaking())
	{
		return;
	}
	SteamMatchmaking()->AddRequestLobbyListNumericalFilter(TCHAR_TO_ANSI(*KeyToMatch), ValueToMatch, static_cast<ELobbyComparison>(ComparisonType.GetValue()));
#endif
}

void USIK_MatchmakingLibrary::AddRequestLobbyListResultCountFilter(int32 MaxResults)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMatchmaking())
	{
		return;
	}
	SteamMatchmaking()->AddRequestLobbyListResultCountFilter(MaxResults);
#endif
}

void USIK_MatchmakingLibrary::AddRequestLobbyListStringFilter(FString KeyToMatch, FString ValueToMatch,
	TEnumAsByte<ESIK_LobbyComparisonType> ComparisonType)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMatchmaking())
	{
		return;
	}
	SteamMatchmaking()->AddRequestLobbyListStringFilter(TCHAR_TO_ANSI(*KeyToMatch), TCHAR_TO_ANSI(*ValueToMatch), static_cast<ELobbyComparison>(ComparisonType.GetValue()));
#endif
}

bool USIK_MatchmakingLibrary::DeleteLobbyData(FSIK_SteamId SteamID, FString Key)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMatchmaking())
	{
		return false;
	}
	return SteamMatchmaking()->DeleteLobbyData(SteamID.GetSteamID(), TCHAR_TO_ANSI(*Key));
#else
	return false;
#endif
}

bool USIK_MatchmakingLibrary::GetFavoriteGame(int32 GameIndex, FSIK_AppId& AppID, FString& IP, int32& ConnPort,
	int32& QueryPort, TArray<int32>& Flags, int32& Time32LastPlayedOnServer)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMatchmaking())
	{
		return false;
	}
	uint32 Var_IP;
	int Data = 0;
	AppId_t AppID_t;
	uint16 Var_ConnPort;
	uint16 Var_QueryPort;
	uint32 Var_Time32LastPlayedOnServer;
	uint32 Var_Data;
	bool Result = SteamMatchmaking()->GetFavoriteGame(GameIndex, &AppID_t, &Var_IP, &Var_ConnPort, &Var_QueryPort, &Var_Data, &Var_Time32LastPlayedOnServer);
	AppID = AppID_t;
	IP = FIPv4Address(Var_IP).ToString();
	for (int i = 0; i < 32; i++)
	{
		if(Data & (1 << i))
		{
			Flags.Add(1 << i);
		}
	}
	Time32LastPlayedOnServer = Var_Time32LastPlayedOnServer;
	ConnPort = Var_ConnPort;
	QueryPort = Var_QueryPort;
	return Result;
#else
	return false;
#endif
}

int32 USIK_MatchmakingLibrary::GetFavoriteGameCount()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMatchmaking())
	{
		return -1;
	}
	return SteamMatchmaking()->GetFavoriteGameCount();
#else
	return -1;
#endif
}

FSIK_SteamId USIK_MatchmakingLibrary::GetLobbyByIndex(int32 LobbyIndex)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMatchmaking())
	{
		return FSIK_SteamId(0);
	}
	return SteamMatchmaking()->GetLobbyByIndex(LobbyIndex);
#else
	return FSIK_SteamId(0);
#endif
}

void USIK_MatchmakingLibrary::GetLobbyChatEntry(FSIK_SteamId LobbyID, int32 ChatID, FSIK_SteamId& OutSteamIDUser,
	FString& OutChatEntry, TEnumAsByte<ESIK_LobbyChatEntryType>& OutEntryType)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	// 1) Sanity‑check the Steam interface
	if (!SteamMatchmaking())
	{
		OutSteamIDUser = FSIK_SteamId();
		OutChatEntry   = TEXT("");
		OutEntryType   = static_cast<ESIK_LobbyChatEntryType>(k_EChatEntryTypeInvalid);
		return;
	}

	// 2)  Reject negative indices
	if (ChatID < 0)
	{
		OutSteamIDUser = FSIK_SteamId();
		OutChatEntry   = TEXT("");
		OutEntryType   = static_cast<ESIK_LobbyChatEntryType>(k_EChatEntryTypeInvalid);
		return;
	}

	CSteamID LobbySteamID = LobbyID.GetSteamID();

	// 3) Allocate a fixed 4 KB buffer (Based on steam docs)
	constexpr int32 MaxBuf = 4096;
	TArray<uint8> Buffer;
	Buffer.AddUninitialized(MaxBuf);

	CSteamID        SenderSteamID;
	EChatEntryType  SteamType;

	// 4) Pull the entry
	int32 BytesRead = SteamMatchmaking()->GetLobbyChatEntry(
		LobbySteamID,
		ChatID,
		&SenderSteamID,
		Buffer.GetData(),
		Buffer.Num(),
		&SteamType);

	// 5) Fill required out‑params
	OutSteamIDUser = FSIK_SteamId(SenderSteamID.ConvertToUint64());
	OutEntryType   = static_cast<ESIK_LobbyChatEntryType>(SteamType);

	// 6) Decode UTF‑8 safely
	if (BytesRead > 0)
	{
		const ANSICHAR* Raw = reinterpret_cast<const ANSICHAR*>(Buffer.GetData());
		FUTF8ToTCHAR    Converter(Raw, BytesRead);      // size‑aware conversion
		OutChatEntry = FString(Converter.Length(), Converter.Get());
	}
	else
	{
		OutChatEntry = TEXT("");
	}
#endif
}

FString USIK_MatchmakingLibrary::GetLobbyData(FSIK_SteamId LobbyID, FString Key)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMatchmaking())
	{
		return "";
	}
	return UTF8_TO_TCHAR(SteamMatchmaking()->GetLobbyData(LobbyID.GetSteamID(), TCHAR_TO_ANSI(*Key)));
#else
	return "";
#endif
}

bool USIK_MatchmakingLibrary::GetLobbyDataByIndex(FSIK_SteamId LobbyID, int32 DataIndex, FString& Key, FString& Value)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMatchmaking())
	{
		return false;
	}
	char Var_Key[4096];
	char Var_Value[4096];
	bool Result = SteamMatchmaking()->GetLobbyDataByIndex(LobbyID.GetSteamID(), DataIndex, Var_Key, 4096, Var_Value, 4096);
	Key = FString(Var_Key);
	Value = FString(Var_Value);
	return Result;
#else
	return false;
#endif
}

int32 USIK_MatchmakingLibrary::GetLobbyDataCount(FSIK_SteamId LobbyID)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMatchmaking())
	{
		return -1;
	}
	return SteamMatchmaking()->GetLobbyDataCount(LobbyID.GetSteamID());
#else
	return -1;
#endif
}

bool USIK_MatchmakingLibrary::GetLobbyGameServer(FSIK_SteamId LobbyID, FString& ServerIP, int32& ServerPort,
	FSIK_SteamId& SteamID)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMatchmaking())
	{
		return false;
	}
	uint32 Var_ServerIP;
	uint16 Var_ServerPort;
	CSteamID Var_SteamID;
	bool Result = SteamMatchmaking()->GetLobbyGameServer(LobbyID.GetSteamID(), &Var_ServerIP, &Var_ServerPort, &Var_SteamID);
	ServerIP = FIPv4Address(Var_ServerIP).ToString();
	ServerPort = Var_ServerPort;
	SteamID = Var_SteamID;
	return Result;
#else
	return false;
#endif
}

FSIK_SteamId USIK_MatchmakingLibrary::GetLobbyMemberByIndex(FSIK_SteamId LobbyID, int32 MemberIndex)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMatchmaking())
	{
		return FSIK_SteamId(0);
	}
	return SteamMatchmaking()->GetLobbyMemberByIndex(LobbyID.GetSteamID(), MemberIndex);
#else
	return FSIK_SteamId(0);
#endif
}

FString USIK_MatchmakingLibrary::GetLobbyMemberData(FSIK_SteamId LobbyID, FSIK_SteamId UserID, FString Key)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMatchmaking())
	{
		return "";
	}
	return UTF8_TO_TCHAR(SteamMatchmaking()->GetLobbyMemberData(LobbyID.GetSteamID(), UserID.GetSteamID(), TCHAR_TO_ANSI(*Key)));
#else
	return "";
#endif
}

int32 USIK_MatchmakingLibrary::GetLobbyMemberLimit(FSIK_SteamId LobbyID)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMatchmaking())
	{
		return -1;
	}
	return SteamMatchmaking()->GetLobbyMemberLimit(LobbyID.GetSteamID());
#else
	return -1;
#endif
}

FSIK_SteamId USIK_MatchmakingLibrary::GetLobbyOwner(FSIK_SteamId LobbyID)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMatchmaking())
	{
		return FSIK_SteamId(0);
	}
	return SteamMatchmaking()->GetLobbyOwner(LobbyID.GetSteamID());
#else
	return FSIK_SteamId(0);
#endif
}

int32 USIK_MatchmakingLibrary::GetNumLobbyMembers(FSIK_SteamId LobbyID)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMatchmaking())
	{
		return -1;
	}
	return SteamMatchmaking()->GetNumLobbyMembers(LobbyID.GetSteamID());
#else
	return -1;
#endif
}

bool USIK_MatchmakingLibrary::InviteUserToLobby(FSIK_SteamId LobbyID, FSIK_SteamId SteamID)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMatchmaking())
	{
		return false;
	}
	return SteamMatchmaking()->InviteUserToLobby(LobbyID.GetSteamID(), SteamID.GetSteamID());
#else
	return false;
#endif
}

void USIK_MatchmakingLibrary::LeaveLobby(FSIK_SteamId LobbyID)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMatchmaking())
	{
		return;
	}
	SteamMatchmaking()->LeaveLobby(LobbyID.GetSteamID());
#endif
}

bool USIK_MatchmakingLibrary::RemoveFavoriteGame(FSIK_AppId AppID, FString IP, int32 ConnPort, int32 QueryPort,
	TArray<int32> Flags)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMatchmaking())
	{
		return false;
	}
	int Data = 0;
	for (int i = 0; i < Flags.Num(); i++)
	{
		Data |= Flags[i];
	}
	FIPv4Address Var_Address;
	FIPv4Address::Parse(IP, Var_Address);
	return SteamMatchmaking()->RemoveFavoriteGame(AppID.GetAppID(), Var_Address.Value, ConnPort, QueryPort, Data);
#else
	return false;
#endif
}

bool USIK_MatchmakingLibrary::RequestLobbyData(FSIK_SteamId LobbyID)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMatchmaking())
	{
		return false;
	}
	return SteamMatchmaking()->RequestLobbyData(LobbyID.GetSteamID());
#else
	return false;
#endif
}

bool USIK_MatchmakingLibrary::SendLobbyChatMessage(FSIK_SteamId LobbyID, FString Message)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMatchmaking())
	{
		return false;
	}
	// Convert FString → UTF‑8 (null‑terminated)
	const FTCHARToUTF8 UTF8(*Message);
	const int32 ByteLen = UTF8.Length();
	
	// Steam: include the terminating NUL in cbMsg
	return SteamMatchmaking()->SendLobbyChatMsg(
		LobbyID.GetSteamID(),
		UTF8.Get(),
		ByteLen + 1
	);
#else
	return false;
#endif
}

void USIK_MatchmakingLibrary::SetLinkedLobby(FSIK_SteamId LobbyID, FSIK_SteamId DependentLobbyID)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMatchmaking())
	{
		return;
	}
	SteamMatchmaking()->SetLinkedLobby(LobbyID.GetSteamID(), DependentLobbyID.GetSteamID());
#endif
}

bool USIK_MatchmakingLibrary::SetLobbyData(FSIK_SteamId LobbyID, FString Key, FString Value)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMatchmaking())
	{
		return false;
	}
	return SteamMatchmaking()->SetLobbyData(LobbyID.GetSteamID(), TCHAR_TO_ANSI(*Key), TCHAR_TO_ANSI(*Value));
#else
	return false;
#endif
}

void USIK_MatchmakingLibrary::SetLobbyGameServer(FSIK_SteamId LobbyID, FString ServerIP, int32 ServerPort, FSIK_SteamId SteamID)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMatchmaking())
	{
		return;
	}
	FIPv4Address Var_ServerIP;
	FIPv4Address::Parse(ServerIP, Var_ServerIP);
	SteamMatchmaking()->SetLobbyGameServer(LobbyID.GetSteamID(), Var_ServerIP.Value, ServerPort, SteamID.GetSteamID());
#endif
}

bool USIK_MatchmakingLibrary::SetLobbyJoinable(FSIK_SteamId LobbyID, bool bJoinable)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMatchmaking())
	{
		return false;
	}
	return SteamMatchmaking()->SetLobbyJoinable(LobbyID.GetSteamID(), bJoinable);
#else
	return false;
#endif
}

void USIK_MatchmakingLibrary::SetLobbyMemberData(FSIK_SteamId LobbyID, FString Key, FString Value)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMatchmaking())
	{
		return;
	}
	SteamMatchmaking()->SetLobbyMemberData(LobbyID.GetSteamID(), TCHAR_TO_ANSI(*Key), TCHAR_TO_ANSI(*Value));
#endif
}

void USIK_MatchmakingLibrary::SetLobbyMemberLimit(FSIK_SteamId LobbyID, int32 MemberLimit)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMatchmaking())
	{
		return;
	}
	SteamMatchmaking()->SetLobbyMemberLimit(LobbyID.GetSteamID(), MemberLimit);
#endif
}

void USIK_MatchmakingLibrary::SetLobbyOwner(FSIK_SteamId LobbyID, FSIK_SteamId SteamID)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMatchmaking())
	{
		return;
	}
	SteamMatchmaking()->SetLobbyOwner(LobbyID.GetSteamID(), SteamID.GetSteamID());
#endif
}

bool USIK_MatchmakingLibrary::SetLobbyType(FSIK_SteamId LobbyID, TEnumAsByte<ESIK_LobbyType> LobbyType)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMatchmaking())
	{
		return false;
	}
	return SteamMatchmaking()->SetLobbyType(LobbyID.GetSteamID(), static_cast<ELobbyType>(LobbyType.GetValue()));
#else
	return false;
#endif
}

