// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#include "SIK_DownloadLeaderboardEntries_AsyncFunction.h"
#include "Async/Async.h"

void USIK_DownloadLeaderboardEntries_AsyncFunction::Activate()
{
	Super::Activate();
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
	if(!SteamUserStats())
	{
		OnFailure.Broadcast(TArray<FDownloadedLeaderboardEntry>());
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	const ELeaderboardDataRequest RequestType = static_cast<ELeaderboardDataRequest>(Var_LeaderboardDataRequest.GetValue());
	CallbackHandle = SteamUserStats()->DownloadLeaderboardEntries(Var_LeaderboardId, RequestType, Var_RangeStart, Var_RangeEnd);
	if(CallbackHandle == k_uAPICallInvalid)
	{
		OnFailure.Broadcast(TArray<FDownloadedLeaderboardEntry>());
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	OnDownloadLeaderboardEntriesCallResult.Set( CallbackHandle, this, &USIK_DownloadLeaderboardEntries_AsyncFunction::OnDownloadLeaderboardEntries );
#else
	OnFailure.Broadcast(TArray<FDownloadedLeaderboardEntry>());
	SetReadyToDestroy();
	MarkAsGarbage();
#endif
}

USIK_DownloadLeaderboardEntries_AsyncFunction* USIK_DownloadLeaderboardEntries_AsyncFunction::
DownloadLeaderboardEntries(int32 LeaderboardId, int32 RangeStart, int32 RangeEnd,
	TEnumAsByte<ESIK_LeaderboardDataRequest> LeaderboardDataRequest)
{
	USIK_DownloadLeaderboardEntries_AsyncFunction* BlueprintNode = NewObject<USIK_DownloadLeaderboardEntries_AsyncFunction>();
	BlueprintNode->Var_LeaderboardId = LeaderboardId;
	BlueprintNode->Var_RangeStart = RangeStart;
	BlueprintNode->Var_RangeEnd = RangeEnd;
	BlueprintNode->Var_LeaderboardDataRequest = LeaderboardDataRequest;
	return BlueprintNode;
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
void USIK_DownloadLeaderboardEntries_AsyncFunction::OnDownloadLeaderboardEntries(LeaderboardScoresDownloaded_t* LeaderboardScoresDownloaded, bool bIOFailure)
{
	auto Param = *LeaderboardScoresDownloaded;
	AsyncTask(ENamedThreads::GameThread, [this, Param,bIOFailure]()
	{
		if(bIOFailure)
		{
			OnFailure.Broadcast(TArray<FDownloadedLeaderboardEntry>());
			SetReadyToDestroy();
			MarkAsGarbage();
			return;
		}
		TArray<FDownloadedLeaderboardEntry> LeaderboardEntries;
		for (int index = 0; index < Param.m_cEntryCount; index++)
		{
			const int32 MAX_DETAILS = 32;
			int32 scoreDetails[MAX_DETAILS] = {0};
			LeaderboardEntry_t leaderboardEntry;
			if(SteamUserStats()->GetDownloadedLeaderboardEntry(Param.m_hSteamLeaderboardEntries, index, &leaderboardEntry, scoreDetails, MAX_DETAILS))
			{
				FDownloadedLeaderboardEntry Entry;
				Entry.GlobalRank = leaderboardEntry.m_nGlobalRank;
				Entry.Score = leaderboardEntry.m_nScore;
				Entry.SteamID = leaderboardEntry.m_steamIDUser;
				Entry.UGCHandle = leaderboardEntry.m_hUGC;
				
				// Convert score details to array
				if (leaderboardEntry.m_cDetails > 0)
				{
					Entry.ScoreDetails.SetNum(leaderboardEntry.m_cDetails);
					for (int32 i = 0; i < leaderboardEntry.m_cDetails; i++)
					{
						Entry.ScoreDetails[i] = scoreDetails[i];
					}
				}
				
				LeaderboardEntries.Add(Entry);
			}
		}
		OnSuccess.Broadcast(LeaderboardEntries);
	});
	SetReadyToDestroy();
	MarkAsGarbage();
}
#endif