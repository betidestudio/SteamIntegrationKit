// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_RequestUserStats_AsyncFunction.h"

#include "Async/Async.h"

USIK_RequestUserStats_AsyncFunction* USIK_RequestUserStats_AsyncFunction::RequestUserStats(FSIK_SteamId SteamID)
{
	USIK_RequestUserStats_AsyncFunction* BlueprintNode = NewObject<USIK_RequestUserStats_AsyncFunction>();
	BlueprintNode->m_SteamID = SteamID;
	return BlueprintNode;
}

void USIK_RequestUserStats_AsyncFunction::OnUserStatsReceived(UserStatsReceived_t* UserStatsReceived, bool bIOFailure)
{
	auto Param = *UserStatsReceived;
	AsyncTask(ENamedThreads::GameThread, [this, Param,bIOFailure]()
	{
		if(bIOFailure)
		{
			OnFailure.Broadcast(ESIK_Result::ResultFail);
		}
		else
		{
			TEnumAsByte<ESIK_Result> Result = static_cast<ESIK_Result>(Param.m_eResult);
			if(Result == ESIK_Result::ResultOK)
			{
				OnSuccess.Broadcast(Result);
			}
			else
			{
				OnFailure.Broadcast(Result);
			}
		}
	});
	SetReadyToDestroy();
	MarkAsGarbage();
}

void USIK_RequestUserStats_AsyncFunction::Activate()
{
	Super::Activate();
	if(!SteamUserStats())
	{
		OnFailure.Broadcast(ESIK_Result::ResultFail);
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	m_CallbackHandle = SteamUserStats()->RequestUserStats(m_SteamID.GetSteamID());
	if(m_CallbackHandle == k_uAPICallInvalid)
	{
		OnFailure.Broadcast(ESIK_Result::ResultFail);
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	m_OnUserStatsReceived.Set(m_CallbackHandle, this, &USIK_RequestUserStats_AsyncFunction::OnUserStatsReceived);
}
