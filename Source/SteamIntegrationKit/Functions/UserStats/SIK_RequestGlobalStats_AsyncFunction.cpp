// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_RequestGlobalStats_AsyncFunction.h"

#include "SIK_SharedFile.h"
#include "Async/Async.h"


USIK_RequestGlobalStats_AsyncFunction* USIK_RequestGlobalStats_AsyncFunction::RequestGlobalStats(int32 HistoryDays)
{
	USIK_RequestGlobalStats_AsyncFunction* Node = NewObject<USIK_RequestGlobalStats_AsyncFunction>();
	Node->Var_HistoryDays = HistoryDays;
	return Node;
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
void USIK_RequestGlobalStats_AsyncFunction::OnRequestGlobalStats(GlobalStatsReceived_t* GlobalStatsReceived,
                                                                 bool bIOFailure)
{
	auto Param = *GlobalStatsReceived;
	AsyncTask(ENamedThreads::GameThread, [this, Param,bIOFailure]()
	{
		if(bIOFailure)
		{
			OnFailure.Broadcast(ESIK_Result::ResultFail);
		}
		else
		{
			ESIK_Result Result = static_cast<ESIK_Result>(Param.m_eResult);
			if(Result != ESIK_Result::ResultOK)
			{
				OnFailure.Broadcast(Result);
				return;
			}
			OnSuccess.Broadcast(Result);
		}
	});
	m_OnRequestGlobalStatsCallResult.Cancel();
	SetReadyToDestroy();
	MarkAsGarbage();
}
#endif

void USIK_RequestGlobalStats_AsyncFunction::Activate()
{
	Super::Activate();
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
	if(!SteamUserStats())
	{
		OnFailure.Broadcast(ESIK_Result::ResultFail);
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	m_CallbackHandle = SteamUserStats()->RequestGlobalStats(Var_HistoryDays);
	if(m_CallbackHandle == k_uAPICallInvalid)
	{
		OnFailure.Broadcast(ESIK_Result::ResultFail);
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	m_OnRequestGlobalStatsCallResult.Set(m_CallbackHandle, this, &USIK_RequestGlobalStats_AsyncFunction::OnRequestGlobalStats);
#else
	OnFailure.Broadcast(ESIK_Result::ResultFail);
	SetReadyToDestroy();
	MarkAsGarbage();
#endif
}
