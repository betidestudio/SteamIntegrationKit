// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_PlayerDetails_AsyncFunction.h"

#include "Async/Async.h"
#include "Interfaces/IPv4/IPv4Address.h"

USIK_PlayerDetails_AsyncFunction* USIK_PlayerDetails_AsyncFunction::RequestPlayerDetails(const FString& ServerIP,
	int32 ServerPort)
{
	USIK_PlayerDetails_AsyncFunction* BlueprintNode = NewObject<USIK_PlayerDetails_AsyncFunction>();
	BlueprintNode->Var_ServerIP = ServerIP;
	BlueprintNode->Var_ServerPort = ServerPort;
	return BlueprintNode;
}

void USIK_PlayerDetails_AsyncFunction::Activate()
{
	Super::Activate();
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if (!SteamMatchmakingServers())
	{
		return;
	}
	FIPv4Address Var_Address;
	FIPv4Address::Parse(Var_ServerIP, Var_Address);
	ServerQueryHandle = SteamMatchmakingServers()->PlayerDetails(Var_Address.Value, Var_ServerPort, this);
#else
	OnPlayersFailedToRespond.Broadcast();
	SetReadyToDestroy();
	MarkAsGarbage();
#endif
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
void USIK_PlayerDetails_AsyncFunction::AddPlayerToList(const char* pchName, int nScore, float flTimePlayed)
{
	FString PlayerName = UTF8_TO_TCHAR(pchName);
	OnAddPlayerToList.Broadcast(PlayerName, nScore, flTimePlayed);
}

void USIK_PlayerDetails_AsyncFunction::PlayersFailedToRespond()
{
	OnPlayersFailedToRespond.Broadcast();
	SteamMatchmakingServers()->CancelServerQuery(ServerQueryHandle);
	SetReadyToDestroy();
	MarkAsGarbage();
}

void USIK_PlayerDetails_AsyncFunction::PlayersRefreshComplete()
{
	AsyncTask(ENamedThreads::GameThread, [this]()
	{
		OnPlayersRefreshComplete.Broadcast();
	});
	SteamMatchmakingServers()->CancelServerQuery(ServerQueryHandle);
	SetReadyToDestroy();
	MarkAsGarbage();
}
#endif