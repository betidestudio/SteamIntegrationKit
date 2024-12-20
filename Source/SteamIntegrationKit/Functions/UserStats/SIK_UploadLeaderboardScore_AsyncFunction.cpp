// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_UploadLeaderboardScore_AsyncFunction.h"

#include "Async/Async.h"

USIK_UploadLeaderboardScore_AsyncFunction* USIK_UploadLeaderboardScore_AsyncFunction::UploadLeaderboardScore(
	int32 LeaderboardId, TEnumAsByte<ESIK_LeaderboardUploadScoreMethod> UploadScoreMethod, int32 Score)
{
	USIK_UploadLeaderboardScore_AsyncFunction* Node = NewObject<USIK_UploadLeaderboardScore_AsyncFunction>();
	Node->Var_LeaderboardId = LeaderboardId;
	Node->Var_UploadScoreMethod = UploadScoreMethod;
	Node->Var_Score = Score;
	return Node;
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
void USIK_UploadLeaderboardScore_AsyncFunction::OnUploadLeaderboardScore(
	LeaderboardScoreUploaded_t* LeaderboardScoreUploaded, bool bIOFailure)
{
	auto Param = *LeaderboardScoreUploaded;
	AsyncTask(ENamedThreads::GameThread, [this, Param,bIOFailure]()
	{
		if(bIOFailure)
		{
			OnFailure.Broadcast(FSIK_LeaderboardScoreUploaded());
			SetReadyToDestroy();
			MarkAsGarbage();
			return;
		}
		if(Param.m_bSuccess == 0)
		{
			OnFailure.Broadcast(FSIK_LeaderboardScoreUploaded());
			SetReadyToDestroy();
			MarkAsGarbage();
			return;
		}
		FSIK_LeaderboardScoreUploaded Result;
		Result.LeaderboardId = Param.m_hSteamLeaderboard;
		Result.Score = Param.m_nScore;
		Result.bScoreChanged = Param.m_bScoreChanged != 0;
		Result.GlobalRankNew = Param.m_nGlobalRankNew;
		Result.GlobalRankPrevious = Param.m_nGlobalRankPrevious;
		OnSuccess.Broadcast(Result);
	});
	SetReadyToDestroy();
	MarkAsGarbage();
}
#endif

void USIK_UploadLeaderboardScore_AsyncFunction::Activate()
{
	Super::Activate();
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
	if(!SteamUserStats())
	{
		OnFailure.Broadcast(FSIK_LeaderboardScoreUploaded());
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	ELeaderboardUploadScoreMethod Var_ScoreMethod = static_cast<ELeaderboardUploadScoreMethod>(Var_UploadScoreMethod.GetValue());
	CallbackHandle = SteamUserStats()->UploadLeaderboardScore(Var_LeaderboardId, Var_ScoreMethod, Var_Score, nullptr, 0);
	if(CallbackHandle == k_uAPICallInvalid)
	{
		OnFailure.Broadcast(FSIK_LeaderboardScoreUploaded());
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	OnUploadLeaderboardScoreCallResult.Set(CallbackHandle, this, &USIK_UploadLeaderboardScore_AsyncFunction::OnUploadLeaderboardScore);
#else
	OnFailure.Broadcast(FSIK_LeaderboardScoreUploaded());
	SetReadyToDestroy();
	MarkAsGarbage();
#endif
}
