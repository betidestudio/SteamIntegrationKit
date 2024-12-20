// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_RequestLobbyList_AsyncFunction.h"

#include "Async/Async.h"

USIK_RequestLobbyList_AsyncFunction* USIK_RequestLobbyList_AsyncFunction::RequestLobbyList()
{
	USIK_RequestLobbyList_AsyncFunction* Node = NewObject<USIK_RequestLobbyList_AsyncFunction>();
	return Node;
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
void USIK_RequestLobbyList_AsyncFunction::OnLobbyListReceived(LobbyMatchList_t* LobbyMatches, bool bIOFailure)
{
	auto Param = *LobbyMatches;
	AsyncTask(ENamedThreads::GameThread, [this, Param,bIOFailure]()
	{
		if(bIOFailure)
		{
			OnFailure.Broadcast(-1);
		}
		else
		{
			OnSuccess.Broadcast(Param.m_nLobbiesMatching);
		}
	});
	SetReadyToDestroy();
	MarkAsGarbage();
}
#endif

void USIK_RequestLobbyList_AsyncFunction::Activate()
{
	Super::Activate();
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMatchmaking())
	{
		OnFailure.Broadcast(-1);
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	CallbackHandle = SteamMatchmaking()->RequestLobbyList();
	if(CallbackHandle == k_uAPICallInvalid)
	{
		OnFailure.Broadcast(-1);
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	CallResult.Set(CallbackHandle, this, &USIK_RequestLobbyList_AsyncFunction::OnLobbyListReceived);
#else
	OnFailure.Broadcast(-1);
	SetReadyToDestroy();
	MarkAsGarbage();
#endif
}
