// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SIK_SharedFile.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SIK_UserStatsSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGlobalAchievementPercentagesReady, TEnumAsByte<ESIK_Result>, Result, int64, GameID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGlobalStatsReceived, TEnumAsByte<ESIK_Result>, Result, int64, GameID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLeaderboardFindResult, FSIK_SteamLeaderboard, Leaderboard, bool, bLeaderboardFound);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnLeaderboardScoresDownloaded, FSIK_SteamLeaderboard, Leaderboard, FSIK_SteamLeaderboardEntries, Entries, int32, EntryCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnLeaderboardScoreUploaded, bool, bSuccess, FSIK_SteamLeaderboard, Leaderboard, int32, Score, bool, bScoreChanged, int32, GlobalRank, int32, PreviousGlobalRank);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNumberOfCurrentPlayers, int32, NumberOfPlayers);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnUserAchievementIconFetched, int32, Gameid, FString, AchievementName, bool, bIconFound, int32, IconHandle);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnUserAchievementStored, int64, GameID, bool, bGroupAchievement, FString, AchievementName, int32, CurProgress, int32, MaxProgress);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnUserStatsReceived, int64, GameID, TEnumAsByte<ESIK_Result>, Result, FSIK_SteamId, steamIDUser);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUserStatsStored, int64, GameID, TEnumAsByte<ESIK_Result>, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUserStatsUnloaded, FSIK_SteamId, steamIDUser);



UCLASS()
class STEAMINTEGRATIONKIT_API USIK_UserStatsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	USIK_UserStatsSubsystem();
	~USIK_UserStatsSubsystem();

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | User Stats")
	FOnGlobalAchievementPercentagesReady OnGlobalAchievementPercentagesReady;
	
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | User Stats")
	FOnGlobalStatsReceived OnGlobalStatsReceived;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | User Stats")
	FOnLeaderboardFindResult OnLeaderboardFindResult;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | User Stats")
	FOnLeaderboardScoresDownloaded OnLeaderboardScoresDownloaded;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | User Stats")
	FOnLeaderboardScoreUploaded OnLeaderboardScoreUploaded;
	

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | User Stats")
	FOnNumberOfCurrentPlayers OnNumberOfCurrentPlayers;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | User Stats")
	FOnUserAchievementIconFetched OnUserAchievementIconFetched;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | User Stats")
	FOnUserAchievementStored OnUserAchievementStored;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | User Stats")
	FOnUserStatsReceived OnUserStatsReceived;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | User Stats")
	FOnUserStatsStored OnUserStatsStored;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | User Stats")
	FOnUserStatsUnloaded OnUserStatsUnloaded;
	
private:
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	//GlobalAchievementPercentagesReady_t
	STEAM_CALLBACK_MANUAL(USIK_UserStatsSubsystem, OnGlobalAchievementPercentagesReadyCallbck, GlobalAchievementPercentagesReady_t, m_CallbackGlobalAchievementPercentagesReady);
	//GlobalStatsReceived_t
	STEAM_CALLBACK_MANUAL(USIK_UserStatsSubsystem, OnGlobalStatsReceivedCallbck, GlobalStatsReceived_t, m_CallbackGlobalStatsReceived);
	//LeaderboardFindResult_t
	STEAM_CALLBACK_MANUAL(USIK_UserStatsSubsystem, OnLeaderboardFindResultCallbck, LeaderboardFindResult_t, m_CallbackLeaderboardFindResult);
	//LeaderboardScoresDownloaded_t
	STEAM_CALLBACK_MANUAL(USIK_UserStatsSubsystem, OnLeaderboardScoresDownloadedCallbck, LeaderboardScoresDownloaded_t, m_CallbackLeaderboardScoresDownloaded);
	//LeaderboardScoreUploaded_t
	STEAM_CALLBACK_MANUAL(USIK_UserStatsSubsystem, OnLeaderboardScoreUploadedCallbck, LeaderboardScoreUploaded_t, m_CallbackLeaderboardScoreUploaded);
	//NumberOfCurrentPlayers_t
	STEAM_CALLBACK_MANUAL(USIK_UserStatsSubsystem, OnNumberOfCurrentPlayersCallbck, NumberOfCurrentPlayers_t, m_CallbackNumberOfCurrentPlayers);
	//UserAchievementIconFetched_t
	STEAM_CALLBACK_MANUAL(USIK_UserStatsSubsystem, OnUserAchievementIconFetchedCallbck, UserAchievementIconFetched_t, m_CallbackUserAchievementIconFetched);
	//UserAchievementStored_t
	STEAM_CALLBACK_MANUAL(USIK_UserStatsSubsystem, OnUserAchievementStoredCallbck, UserAchievementStored_t, m_CallbackUserAchievementStored);
	//UserStatsReceived_t
	STEAM_CALLBACK_MANUAL(USIK_UserStatsSubsystem, OnUserStatsReceivedCallbck, UserStatsReceived_t, m_CallbackUserStatsReceived);
	//UserStatsStored_t
	STEAM_CALLBACK_MANUAL(USIK_UserStatsSubsystem, OnUserStatsStoredCallbck, UserStatsStored_t, m_CallbackUserStatsStored);
	//UserStatsUnloaded_t
	STEAM_CALLBACK_MANUAL(USIK_UserStatsSubsystem, OnUserStatsUnloadedCallbck, UserStatsUnloaded_t, m_CallbackUserStatsUnloaded);
#endif
};
