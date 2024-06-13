// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_FindLeaderboard_AsyncFunction.h"

#include "Async/Async.h"


USIK_FindLeaderboard_AsyncFunction* USIK_FindLeaderboard_AsyncFunction::FindLeaderboard(const FString& LeaderboardName)
{
	USIK_FindLeaderboard_AsyncFunction* BlueprintNode = NewObject<USIK_FindLeaderboard_AsyncFunction>();
	BlueprintNode->Var_LeaderboardName = LeaderboardName;
	return BlueprintNode;
}

void USIK_FindLeaderboard_AsyncFunction::Activate()
{
	Super::Activate();
	if(!SteamUserStats())
	{
		OnFailure.Broadcast(-1);
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	CallbackHandle = SteamUserStats()->FindLeaderboard(TCHAR_TO_UTF8(*Var_LeaderboardName));
	if(CallbackHandle == k_uAPICallInvalid)
	{
		OnFailure.Broadcast(-1);
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	OnFindLeaderboardCallResult.Set( CallbackHandle, this, &USIK_FindLeaderboard_AsyncFunction::OnFindLeaderboard );
}

void USIK_FindLeaderboard_AsyncFunction::OnFindLeaderboard(LeaderboardFindResult_t* pResult, bool bIOFailure)
{
	auto Param = *pResult;
	AsyncTask(ENamedThreads::GameThread, [this, Param,bIOFailure]()
	{
		if(bIOFailure)
		{
			OnFailure.Broadcast(-1);
			SetReadyToDestroy();
			MarkAsGarbage();
			return;
		}
		if(Param.m_bLeaderboardFound)
		{
			OnSuccess.Broadcast(Param.m_hSteamLeaderboard);
		}
		else
		{
			OnFailure.Broadcast(-1);
		}
	});
	SetReadyToDestroy();
	MarkAsGarbage();
}
