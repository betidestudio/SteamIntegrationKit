// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_MatchmakingLibrary.h"

#include "Interfaces/IPv4/IPv4Address.h"

int32 USIK_MatchmakingLibrary::AddFavoriteGame(FSIK_AppId AppID, FString IP, int32 ConnPort, int32 QueryPort,
                                               TArray<int32> Flags, int32 Time32LastPlayedOnServer)
{
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
}

void USIK_MatchmakingLibrary::AddRequestLobbyListCompatibleMembersFilter(FSIK_SteamId SteamID)
{
	if(!SteamMatchmaking())
	{
		return;
	}
	SteamMatchmaking()->AddRequestLobbyListCompatibleMembersFilter(SteamID.GetSteamID());
}

void USIK_MatchmakingLibrary::AddRequestLobbyListDistanceFilter(
	TEnumAsByte<ESIK_LobbyDistanceFilter> LobbyDistanceFilter)
{
	if(!SteamMatchmaking())
	{
		return;
	}
	SteamMatchmaking()->AddRequestLobbyListDistanceFilter(static_cast<ELobbyDistanceFilter>(LobbyDistanceFilter.GetValue()));
}

void USIK_MatchmakingLibrary::AddRequestLobbyListFilterSlotsAvailable(int32 SlotsAvailable)
{
	if(!SteamMatchmaking())
	{
		return;
	}
	SteamMatchmaking()->AddRequestLobbyListFilterSlotsAvailable(SlotsAvailable);
}

void USIK_MatchmakingLibrary::AddRequestLobbyListNearValueFilter(FString KeyToMatch, int32 ValueToBeCloseTo)
{
	if(!SteamMatchmaking())
	{
		return;
	}
	SteamMatchmaking()->AddRequestLobbyListNearValueFilter(TCHAR_TO_ANSI(*KeyToMatch), ValueToBeCloseTo);
}

void USIK_MatchmakingLibrary::AddRequestLobbyListNumericalFilter(FString KeyToMatch, int32 ValueToMatch,
	TEnumAsByte<ESIK_LobbyComparisonType> ComparisonType)
{
	if(!SteamMatchmaking())
	{
		return;
	}
	SteamMatchmaking()->AddRequestLobbyListNumericalFilter(TCHAR_TO_ANSI(*KeyToMatch), ValueToMatch, static_cast<ELobbyComparison>(ComparisonType.GetValue()));
}

void USIK_MatchmakingLibrary::AddRequestLobbyListResultCountFilter(int32 MaxResults)
{
	if(!SteamMatchmaking())
	{
		return;
	}
	SteamMatchmaking()->AddRequestLobbyListResultCountFilter(MaxResults);
}

void USIK_MatchmakingLibrary::AddRequestLobbyListStringFilter(FString KeyToMatch, FString ValueToMatch,
	TEnumAsByte<ESIK_LobbyComparisonType> ComparisonType)
{
	if(!SteamMatchmaking())
	{
		return;
	}
	SteamMatchmaking()->AddRequestLobbyListStringFilter(TCHAR_TO_ANSI(*KeyToMatch), TCHAR_TO_ANSI(*ValueToMatch), static_cast<ELobbyComparison>(ComparisonType.GetValue()));
}

bool USIK_MatchmakingLibrary::DeleteLobbyData(FSIK_SteamId SteamID, FString Key)
{
	if(!SteamMatchmaking())
	{
		return false;
	}
	return SteamMatchmaking()->DeleteLobbyData(SteamID.GetSteamID(), TCHAR_TO_ANSI(*Key));
}

bool USIK_MatchmakingLibrary::GetFavoriteGame(int32 GameIndex, FSIK_AppId& AppID, FString& IP, int32& ConnPort,
	int32& QueryPort, TArray<int32>& Flags, int32& Time32LastPlayedOnServer)
{
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
}

int32 USIK_MatchmakingLibrary::GetFavoriteGameCount()
{
	if(!SteamMatchmaking())
	{
		return -1;
	}
	return SteamMatchmaking()->GetFavoriteGameCount();
}

FSIK_SteamId USIK_MatchmakingLibrary::GetLobbyByIndex(int32 LobbyIndex)
{
	if(!SteamMatchmaking())
	{
		return FSIK_SteamId(0);
	}
	return SteamMatchmaking()->GetLobbyByIndex(LobbyIndex);
}

void USIK_MatchmakingLibrary::GetLobbyChatEntry(FSIK_SteamId SteamID, int32 ChatID, FSIK_SteamId& SteamIDUser,
	FString& ChatEntry, TEnumAsByte<ESIK_LobbyChatEntryType>& ChatEntryType)
{
	if(!SteamMatchmaking())
	{
		return;
	}
	CSteamID Var_SteamIDUser;
	EChatEntryType Var_ChatEntryType;
	char Var_ChatEntry[4096];
	SteamMatchmaking()->GetLobbyChatEntry(SteamID.GetSteamID(), ChatID, &Var_SteamIDUser, Var_ChatEntry, 4096, &Var_ChatEntryType);
	SteamIDUser = Var_SteamIDUser;
	ChatEntry = FString(Var_ChatEntry);
	ChatEntryType = static_cast<ESIK_LobbyChatEntryType>(Var_ChatEntryType);
}

FString USIK_MatchmakingLibrary::GetLobbyData(FSIK_SteamId LobbyID, FString Key)
{
	if(!SteamMatchmaking())
	{
		return "";
	}
	return FString(SteamMatchmaking()->GetLobbyData(LobbyID.GetSteamID(), TCHAR_TO_ANSI(*Key)));
}

bool USIK_MatchmakingLibrary::GetLobbyDataByIndex(FSIK_SteamId LobbyID, int32 DataIndex, FString& Key, FString& Value)
{
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
}

int32 USIK_MatchmakingLibrary::GetLobbyDataCount(FSIK_SteamId LobbyID)
{
	if(!SteamMatchmaking())
	{
		return -1;
	}
	return SteamMatchmaking()->GetLobbyDataCount(LobbyID.GetSteamID());
}

bool USIK_MatchmakingLibrary::GetLobbyGameServer(FSIK_SteamId LobbyID, FString& ServerIP, int32& ServerPort,
	FSIK_SteamId& SteamID)
{
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
}

FSIK_SteamId USIK_MatchmakingLibrary::GetLobbyMemberByIndex(FSIK_SteamId LobbyID, int32 MemberIndex)
{
	if(!SteamMatchmaking())
	{
		return FSIK_SteamId(0);
	}
	return SteamMatchmaking()->GetLobbyMemberByIndex(LobbyID.GetSteamID(), MemberIndex);
}

FString USIK_MatchmakingLibrary::GetLobbyMemberData(FSIK_SteamId LobbyID, FSIK_SteamId UserID, FString Key)
{
	if(!SteamMatchmaking())
	{
		return "";
	}
	return FString(SteamMatchmaking()->GetLobbyMemberData(LobbyID.GetSteamID(), UserID.GetSteamID(), TCHAR_TO_ANSI(*Key)));
}

int32 USIK_MatchmakingLibrary::GetLobbyMemberLimit(FSIK_SteamId LobbyID)
{
	if(!SteamMatchmaking())
	{
		return -1;
	}
	return SteamMatchmaking()->GetLobbyMemberLimit(LobbyID.GetSteamID());
}

FSIK_SteamId USIK_MatchmakingLibrary::GetLobbyOwner(FSIK_SteamId LobbyID)
{
	if(!SteamMatchmaking())
	{
		return FSIK_SteamId(0);
	}
	return SteamMatchmaking()->GetLobbyOwner(LobbyID.GetSteamID());
}

int32 USIK_MatchmakingLibrary::GetNumLobbyMembers(FSIK_SteamId LobbyID)
{
	if(!SteamMatchmaking())
	{
		return -1;
	}
	return SteamMatchmaking()->GetNumLobbyMembers(LobbyID.GetSteamID());
}

bool USIK_MatchmakingLibrary::InviteUserToLobby(FSIK_SteamId LobbyID, FSIK_SteamId SteamID)
{
	if(!SteamMatchmaking())
	{
		return false;
	}
	return SteamMatchmaking()->InviteUserToLobby(LobbyID.GetSteamID(), SteamID.GetSteamID());
}

void USIK_MatchmakingLibrary::LeaveLobby(FSIK_SteamId LobbyID)
{
	if(!SteamMatchmaking())
	{
		return;
	}
	SteamMatchmaking()->LeaveLobby(LobbyID.GetSteamID());
}

bool USIK_MatchmakingLibrary::RemoveFavoriteGame(FSIK_AppId AppID, FString IP, int32 ConnPort, int32 QueryPort,
	TArray<int32> Flags)
{
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
}

bool USIK_MatchmakingLibrary::RequestLobbyData(FSIK_SteamId LobbyID)
{
	if(!SteamMatchmaking())
	{
		return false;
	}
	return SteamMatchmaking()->RequestLobbyData(LobbyID.GetSteamID());
}

bool USIK_MatchmakingLibrary::SendLobbyChatMessage(FSIK_SteamId LobbyID, FString Message)
{
	if(!SteamMatchmaking())
	{
		return false;
	}
	return SteamMatchmaking()->SendLobbyChatMsg(LobbyID.GetSteamID(), TCHAR_TO_ANSI(*Message), Message.Len());
}

void USIK_MatchmakingLibrary::SetLinkedLobby(FSIK_SteamId LobbyID, FSIK_SteamId DependentLobbyID)
{
	if(!SteamMatchmaking())
	{
		return;
	}
	SteamMatchmaking()->SetLinkedLobby(LobbyID.GetSteamID(), DependentLobbyID.GetSteamID());
}

bool USIK_MatchmakingLibrary::SetLobbyData(FSIK_SteamId LobbyID, FString Key, FString Value)
{
	if(!SteamMatchmaking())
	{
		return false;
	}
	return SteamMatchmaking()->SetLobbyData(LobbyID.GetSteamID(), TCHAR_TO_ANSI(*Key), TCHAR_TO_ANSI(*Value));
}

void USIK_MatchmakingLibrary::SetLobbyGameServer(FSIK_SteamId LobbyID, FString ServerIP, int32 ServerPort, FSIK_SteamId SteamID)
{
	if(!SteamMatchmaking())
	{
		return;
	}
	FIPv4Address Var_ServerIP;
	FIPv4Address::Parse(ServerIP, Var_ServerIP);
	SteamMatchmaking()->SetLobbyGameServer(LobbyID.GetSteamID(), Var_ServerIP.Value, ServerPort, SteamID.GetSteamID());
}

bool USIK_MatchmakingLibrary::SetLobbyJoinable(FSIK_SteamId LobbyID, bool bJoinable)
{
	if(!SteamMatchmaking())
	{
		return false;
	}
	return SteamMatchmaking()->SetLobbyJoinable(LobbyID.GetSteamID(), bJoinable);
}

void USIK_MatchmakingLibrary::SetLobbyMemberData(FSIK_SteamId LobbyID, FString Key, FString Value)
{
	if(!SteamMatchmaking())
	{
		return;
	}
	SteamMatchmaking()->SetLobbyMemberData(LobbyID.GetSteamID(), TCHAR_TO_ANSI(*Key), TCHAR_TO_ANSI(*Value));
}

void USIK_MatchmakingLibrary::SetLobbyMemberLimit(FSIK_SteamId LobbyID, int32 MemberLimit)
{
	if(!SteamMatchmaking())
	{
		return;
	}
	SteamMatchmaking()->SetLobbyMemberLimit(LobbyID.GetSteamID(), MemberLimit);
}

void USIK_MatchmakingLibrary::SetLobbyOwner(FSIK_SteamId LobbyID, FSIK_SteamId SteamID)
{
	if(!SteamMatchmaking())
	{
		return;
	}
	SteamMatchmaking()->SetLobbyOwner(LobbyID.GetSteamID(), SteamID.GetSteamID());
}

bool USIK_MatchmakingLibrary::SetLobbyType(FSIK_SteamId LobbyID, TEnumAsByte<ESIK_LobbyType> LobbyType)
{
	if(!SteamMatchmaking())
	{
		return false;
	}
	return SteamMatchmaking()->SetLobbyType(LobbyID.GetSteamID(), static_cast<ELobbyType>(LobbyType.GetValue()));
}

