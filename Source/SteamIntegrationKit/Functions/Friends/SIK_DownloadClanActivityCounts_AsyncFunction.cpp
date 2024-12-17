// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_DownloadClanActivityCounts_AsyncFunction.h"

#include "Async/Async.h"


USIK_DownloadClanActivityCounts_AsyncFunction* USIK_DownloadClanActivityCounts_AsyncFunction::
DownloadClanActivityCounts(const TArray<int64>& ClanIds)
{
	USIK_DownloadClanActivityCounts_AsyncFunction* Node = NewObject<USIK_DownloadClanActivityCounts_AsyncFunction>();
	Node->Var_ClanIds = ClanIds;
	return Node;
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
void USIK_DownloadClanActivityCounts_AsyncFunction::OnDownloadClanActivityCounts(
	DownloadClanActivityCountsResult_t* DownloadClanActivityCountsResult, bool bIOFailure)
{
	auto Param = *DownloadClanActivityCountsResult;
	AsyncTask(ENamedThreads::GameThread, [this, Param, bIOFailure]()
	{
		if(bIOFailure && !Param.m_bSuccess)
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

void USIK_DownloadClanActivityCounts_AsyncFunction::Activate()
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
	if(Var_ClanIds.Num() == 0)
	{
		OnFailure.Broadcast();
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	CSteamID ClanIds[50];
	for(int i = 0; i < Var_ClanIds.Num(); i++)
	{
		ClanIds[i].SetFromUint64(Var_ClanIds[i]);
	}
	CallbackHandle = SteamFriends()->DownloadClanActivityCounts(ClanIds, Var_ClanIds.Num());
	if(CallbackHandle == k_uAPICallInvalid)
	{
		OnFailure.Broadcast();
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	OnDownloadClanActivityCountsCallResult.Set( CallbackHandle, this, &USIK_DownloadClanActivityCounts_AsyncFunction::OnDownloadClanActivityCounts );
#else
	OnFailure.Broadcast();
	SetReadyToDestroy();
	MarkAsGarbage();
#endif
}
