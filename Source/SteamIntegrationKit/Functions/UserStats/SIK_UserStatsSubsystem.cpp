 // Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_UserStatsSubsystem.h"

#include "Async/Async.h"


 USIK_UserStatsSubsystem::USIK_UserStatsSubsystem()
 {
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
 	m_CallbackGlobalAchievementPercentagesReady.Register(this, &USIK_UserStatsSubsystem::OnGlobalAchievementPercentagesReadyCallbck);
 	m_CallbackGlobalStatsReceived.Register(this, &USIK_UserStatsSubsystem::OnGlobalStatsReceivedCallbck);
 	m_CallbackLeaderboardFindResult.Register(this, &USIK_UserStatsSubsystem::OnLeaderboardFindResultCallbck);
 	m_CallbackLeaderboardScoresDownloaded.Register(this, &USIK_UserStatsSubsystem::OnLeaderboardScoresDownloadedCallbck);
 	m_CallbackLeaderboardScoreUploaded.Register(this, &USIK_UserStatsSubsystem::OnLeaderboardScoreUploadedCallbck);
 	m_CallbackNumberOfCurrentPlayers.Register(this, &USIK_UserStatsSubsystem::OnNumberOfCurrentPlayersCallbck);
 	m_CallbackUserAchievementIconFetched.Register(this, &USIK_UserStatsSubsystem::OnUserAchievementIconFetchedCallbck);
 	m_CallbackUserAchievementStored.Register(this, &USIK_UserStatsSubsystem::OnUserAchievementStoredCallbck);
 	m_CallbackUserStatsReceived.Register(this, &USIK_UserStatsSubsystem::OnUserStatsReceivedCallbck);
 	m_CallbackUserStatsStored.Register(this, &USIK_UserStatsSubsystem::OnUserStatsStoredCallbck);
 	m_CallbackUserStatsUnloaded.Register(this, &USIK_UserStatsSubsystem::OnUserStatsUnloadedCallbck);

 	if(IsRunningDedicatedServer())
 	{
 		m_CallbackGlobalAchievementPercentagesReady.SetGameserverFlag();
 		m_CallbackGlobalStatsReceived.SetGameserverFlag();
 		m_CallbackLeaderboardFindResult.SetGameserverFlag();
 		m_CallbackLeaderboardScoresDownloaded.SetGameserverFlag();
 		m_CallbackLeaderboardScoreUploaded.SetGameserverFlag();
 		m_CallbackNumberOfCurrentPlayers.SetGameserverFlag();
 		m_CallbackUserAchievementIconFetched.SetGameserverFlag();
 		m_CallbackUserAchievementStored.SetGameserverFlag();
 		m_CallbackUserStatsReceived.SetGameserverFlag();
 		m_CallbackUserStatsStored.SetGameserverFlag();
 		m_CallbackUserStatsUnloaded.SetGameserverFlag();
 	}
#endif
 }

 USIK_UserStatsSubsystem::~USIK_UserStatsSubsystem()
 {
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
 	m_CallbackGlobalAchievementPercentagesReady.Unregister();
 	m_CallbackGlobalStatsReceived.Unregister();
 	m_CallbackLeaderboardFindResult.Unregister();
 	m_CallbackLeaderboardScoresDownloaded.Unregister();
 	m_CallbackLeaderboardScoreUploaded.Unregister();
 	m_CallbackNumberOfCurrentPlayers.Unregister();
 	m_CallbackUserAchievementIconFetched.Unregister();
 	m_CallbackUserAchievementStored.Unregister();
 	m_CallbackUserStatsReceived.Unregister();
 	m_CallbackUserStatsStored.Unregister();
 	m_CallbackUserStatsUnloaded.Unregister();
#endif
 }

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
void USIK_UserStatsSubsystem::OnGlobalAchievementPercentagesReadyCallbck(GlobalAchievementPercentagesReady_t* pCallback)
{
	auto Param = *pCallback;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnGlobalAchievementPercentagesReady.Broadcast(static_cast<ESIK_Result>(Param.m_eResult), Param.m_nGameID);
	});
}

void USIK_UserStatsSubsystem::OnGlobalStatsReceivedCallbck(GlobalStatsReceived_t* pCallback)
{
	auto Param = *pCallback;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnGlobalStatsReceived.Broadcast(static_cast<ESIK_Result>(Param.m_eResult), Param.m_nGameID);
	});
}

void USIK_UserStatsSubsystem::OnLeaderboardFindResultCallbck(LeaderboardFindResult_t* pCallback)
{
	auto Param = *pCallback;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnLeaderboardFindResult.Broadcast(Param.m_hSteamLeaderboard, Param.m_bLeaderboardFound == 1);
	});
}

void USIK_UserStatsSubsystem::OnLeaderboardScoresDownloadedCallbck(LeaderboardScoresDownloaded_t* pCallback)
{
	auto Param = *pCallback;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnLeaderboardScoresDownloaded.Broadcast(Param.m_hSteamLeaderboard, Param.m_hSteamLeaderboardEntries, Param.m_cEntryCount);
	});
}

void USIK_UserStatsSubsystem::OnLeaderboardScoreUploadedCallbck(LeaderboardScoreUploaded_t* pCallback)
{
	auto Param = *pCallback;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		bool bSuccess = Param.m_bSuccess == 1;
		OnLeaderboardScoreUploaded.Broadcast(bSuccess, Param.m_hSteamLeaderboard, Param.m_nScore, Param.m_bScoreChanged == 1, Param.m_nGlobalRankNew, Param.m_nGlobalRankPrevious);
	});
}

void USIK_UserStatsSubsystem::OnNumberOfCurrentPlayersCallbck(NumberOfCurrentPlayers_t* pCallback)
{
	auto Param = *pCallback;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnNumberOfCurrentPlayers.Broadcast(Param.m_cPlayers);
	});
}


void USIK_UserStatsSubsystem::OnUserAchievementIconFetchedCallbck(UserAchievementIconFetched_t* pCallback)
{
	auto Param = *pCallback;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnUserAchievementIconFetched.Broadcast(Param.m_nGameID.ToUint64(), Param.m_rgchAchievementName, Param.m_bAchieved, Param.m_nIconHandle);
	});
}

void USIK_UserStatsSubsystem::OnUserAchievementStoredCallbck(UserAchievementStored_t* pCallback)
{
	auto Param = *pCallback;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnUserAchievementStored.Broadcast(Param.m_nGameID, Param.m_bGroupAchievement, Param.m_rgchAchievementName, Param.m_nCurProgress, Param.m_nMaxProgress);
	});
}

void USIK_UserStatsSubsystem::OnUserStatsReceivedCallbck(UserStatsReceived_t* pCallback)
{
	auto Param = *pCallback;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnUserStatsReceived.Broadcast(Param.m_nGameID, static_cast<ESIK_Result>(Param.m_eResult), Param.m_steamIDUser);
	});
}

void USIK_UserStatsSubsystem::OnUserStatsStoredCallbck(UserStatsStored_t* pCallback)
{
	auto Param = *pCallback;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnUserStatsStored.Broadcast(Param.m_nGameID, static_cast<ESIK_Result>(Param.m_eResult));
	});
}

void USIK_UserStatsSubsystem::OnUserStatsUnloadedCallbck(UserStatsUnloaded_t* pCallback)
{
	auto Param = *pCallback;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnUserStatsUnloaded.Broadcast(Param.m_steamIDUser);
	});
}
#endif