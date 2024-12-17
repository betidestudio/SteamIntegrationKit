// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_RequestClanOfficerList_AsyncFunction.h"

#include "Async/Async.h"

USIK_RequestClanOfficerList_AsyncFunction* USIK_RequestClanOfficerList_AsyncFunction::RequestClanOfficerList(
	const FSIK_SteamId& ClanId)
{
	USIK_RequestClanOfficerList_AsyncFunction* BlueprintNode = NewObject<USIK_RequestClanOfficerList_AsyncFunction>();
	BlueprintNode->m_ClanId = ClanId;
	return BlueprintNode;
}

void USIK_RequestClanOfficerList_AsyncFunction::Activate()
{
	Super::Activate();
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() == nullptr)
	{
		OnFailure.Broadcast(-1);
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	m_CallbackHandle = SteamFriends()->RequestClanOfficerList(m_ClanId.GetSteamID());
	if(m_CallbackHandle == k_uAPICallInvalid)
	{
		OnFailure.Broadcast(-1);
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	m_Callback.Set(m_CallbackHandle, this, &USIK_RequestClanOfficerList_AsyncFunction::OnRequestClanOfficerList);
#else
	OnFailure.Broadcast(-1);
	SetReadyToDestroy();
	MarkAsGarbage();
#endif
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
void USIK_RequestClanOfficerList_AsyncFunction::OnRequestClanOfficerList(ClanOfficerListResponse_t* ClanOfficerListResponse, bool bIOFailure)
{
	auto Param = *ClanOfficerListResponse;
	AsyncTask(ENamedThreads::GameThread, [this, Param, bIOFailure]()
	{
		if(bIOFailure)
		{
			OnFailure.Broadcast(-1);
		}
		else
		{
			if(Param.m_bSuccess)
			{
				OnSuccess.Broadcast(Param.m_cOfficers);
			}
			else
			{
				OnFailure.Broadcast(-1);
			}
		}
	});
	SetReadyToDestroy();
	MarkAsGarbage();
}
#endif