// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_EnumerateFollowingList_AsyncFunction.h"

#include "Async/Async.h"

USIK_EnumerateFollowingList_AsyncFunction* USIK_EnumerateFollowingList_AsyncFunction::EnumerateFollowingList(
	int32 StartIndex)
{
	USIK_EnumerateFollowingList_AsyncFunction* Node = NewObject<USIK_EnumerateFollowingList_AsyncFunction>();
	Node->m_StartIndex = StartIndex;
	return Node;
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
void USIK_EnumerateFollowingList_AsyncFunction::OnEnumerateFollowingList(
	FriendsEnumerateFollowingList_t* FriendsEnumerateFollowings, bool bIOFailure)
{
	auto Param = *FriendsEnumerateFollowings;
	AsyncTask(ENamedThreads::GameThread, [this, Param, bIOFailure]()
	{
		if(bIOFailure)
		{
			OnFailure.Broadcast(TArray<FSIK_SteamId>(), 0, 0);
		}
		else
		{
			TArray<FSIK_SteamId> FollowingList;
			if(Param.m_eResult == k_EResultOK)
			{
				for(int32 i = 0; i < Param.m_nResultsReturned; i++)
				{
					FollowingList.Add(Param.m_rgSteamID[i]);
				}
				OnSuccess.Broadcast(FollowingList, Param.m_nResultsReturned, Param.m_nTotalResultCount);
			}
			else
			{
				OnFailure.Broadcast(FollowingList, Param.m_nResultsReturned, Param.m_nTotalResultCount);
			}
		}
	});
	SetReadyToDestroy();
	MarkAsGarbage();
}
#endif

void USIK_EnumerateFollowingList_AsyncFunction::Activate()
{
	Super::Activate();
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() == nullptr)
	{
		OnFailure.Broadcast(TArray<FSIK_SteamId>(), 0, 0);
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	m_CallbackHandle = SteamFriends()->EnumerateFollowingList(m_StartIndex);
	if(m_CallbackHandle == k_uAPICallInvalid)
	{
		OnFailure.Broadcast(TArray<FSIK_SteamId>(), 0, 0);
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	m_Callback.Set(m_CallbackHandle, this, &USIK_EnumerateFollowingList_AsyncFunction::OnEnumerateFollowingList);
#else
	OnFailure.Broadcast(TArray<FSIK_SteamId>(), 0, 0);
	SetReadyToDestroy();
	MarkAsGarbage();
#endif
}