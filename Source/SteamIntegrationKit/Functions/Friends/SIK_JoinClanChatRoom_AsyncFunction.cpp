// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_JoinClanChatRoom_AsyncFunction.h"

#include "Async/Async.h"

USIK_JoinClanChatRoom_AsyncFunction* USIK_JoinClanChatRoom_AsyncFunction::JoinClanChatRoom(FSIK_SteamId ClanId)
{
	USIK_JoinClanChatRoom_AsyncFunction* Node = NewObject<USIK_JoinClanChatRoom_AsyncFunction>();
	Node->m_ClanId = ClanId;
	return Node;
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
void USIK_JoinClanChatRoom_AsyncFunction::OnJoinClanChatRoom(GameConnectedChatJoin_t* GameConnectedChatJoin,
                                                             bool bIOFailure)
{
	auto Param = *GameConnectedChatJoin;
	AsyncTask(ENamedThreads::GameThread, [this, Param, bIOFailure]()
	{
		if(bIOFailure)
		{
			OnFailure.Broadcast();
		}
		else
		{
			OnSuccess.Broadcast();
		}
	});
	SetReadyToDestroy();
	MarkAsGarbage();
}
#endif

void USIK_JoinClanChatRoom_AsyncFunction::Activate()
{
	Super::Activate();
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() == nullptr)
	{
		OnFailure.Broadcast();
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	m_CallbackHandle = SteamFriends()->JoinClanChatRoom(m_ClanId.GetSteamID());
	if(m_CallbackHandle == k_uAPICallInvalid)
	{
		OnFailure.Broadcast();
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	m_Callback.Set(m_CallbackHandle, this, &USIK_JoinClanChatRoom_AsyncFunction::OnJoinClanChatRoom);
#else
	OnFailure.Broadcast();
	SetReadyToDestroy();
	MarkAsGarbage();
#endif	
}
