// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_GetFollowerCount_AsyncFunction.h"

#include "Async/Async.h"

USIK_GetFollowerCount_AsyncFunction* USIK_GetFollowerCount_AsyncFunction::GetFollowerCount(const FSIK_SteamId& SteamId)
{
	USIK_GetFollowerCount_AsyncFunction* Node = NewObject<USIK_GetFollowerCount_AsyncFunction>();
	Node->m_SteamId = SteamId;
	return Node;
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
void USIK_GetFollowerCount_AsyncFunction::OnGetFollowerCount(FriendsGetFollowerCount_t* FriendsGetFollowerCount, bool bIOFailure)
{
	auto Param = *FriendsGetFollowerCount;
	AsyncTask(ENamedThreads::GameThread, [this, Param, bIOFailure]()
	{
		if(bIOFailure)
		{
			OnFailure.Broadcast(-1, FSIK_SteamId());
		}
		else
		{
			if(Param.m_eResult == k_EResultOK)
			{
				OnSuccess.Broadcast(Param.m_nCount, m_SteamId);
			}
			else
			{
				OnFailure.Broadcast(-1, FSIK_SteamId());
			}
		}
	});
	SetReadyToDestroy();
	MarkAsGarbage();
}
#endif

void USIK_GetFollowerCount_AsyncFunction::Activate()
{
	Super::Activate();
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() == nullptr)
	{
		OnFailure.Broadcast(0, FSIK_SteamId());
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	m_CallbackHandle = SteamFriends()->GetFollowerCount(m_SteamId.GetSteamID());
	if(m_CallbackHandle == k_uAPICallInvalid)
	{
		OnFailure.Broadcast(0, FSIK_SteamId());
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	m_Callback.Set(m_CallbackHandle, this, &USIK_GetFollowerCount_AsyncFunction::OnGetFollowerCount);
#else
	OnFailure.Broadcast(0, FSIK_SteamId());
	SetReadyToDestroy();
	MarkAsGarbage();
#endif
}
