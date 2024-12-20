// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SIK_SharedFile.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SIK_DownloadLeaderboardEntries_AsyncFunction.generated.h"

UENUM(BlueprintType)
enum ESIK_LeaderboardDataRequest
{
	LeaderboardDataRequestGlobal = 0 UMETA(DisplayName = "Global"),
	LeaderboardDataRequestGlobalAroundUser = 1 UMETA(DisplayName = "Global Around User"),
	LeaderboardDataRequestFriends = 2 UMETA(DisplayName = "Friends"),
	LeaderboardDataRequestUsers = 3 UMETA(DisplayName = "Users")
};

USTRUCT(BlueprintType)
struct FDownloadedLeaderboardEntry
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly,Category="Steam Integration Kit || User Stats")
	FSIK_SteamId SteamID;

	UPROPERTY(BlueprintReadOnly,Category="Steam Integration Kit || User Stats")
	int32 GlobalRank = 0;

	UPROPERTY(BlueprintReadOnly,Category="Steam Integration Kit || User Stats")
	int32 Score = 0;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLeaderboardScoresDownloaded, const TArray<FDownloadedLeaderboardEntry>&, LeaderboardEntries);
UCLASS()
class STEAMINTEGRATIONKIT_API USIK_DownloadLeaderboardEntries_AsyncFunction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, DisplayName="Download Steam Leaderboard Entries",meta = (BlueprintInternalUseOnly = "true"), Category="Steam Integration Kit || SDK Functions || User Stats")
	static USIK_DownloadLeaderboardEntries_AsyncFunction* DownloadLeaderboardEntries(int32 LeaderboardId, int32 RangeStart, int32 RangeEnd, TEnumAsByte<ESIK_LeaderboardDataRequest> LeaderboardDataRequest);

	UPROPERTY(BlueprintAssignable)
	FLeaderboardScoresDownloaded OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FLeaderboardScoresDownloaded OnFailure;

private:
	virtual void Activate() override;
	int32 Var_LeaderboardId;
	int32 Var_RangeStart;
	int32 Var_RangeEnd;
	TEnumAsByte<ESIK_LeaderboardDataRequest> Var_LeaderboardDataRequest;
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
	CCallResult<USIK_DownloadLeaderboardEntries_AsyncFunction, LeaderboardScoresDownloaded_t> OnDownloadLeaderboardEntriesCallResult;
	void OnDownloadLeaderboardEntries(LeaderboardScoresDownloaded_t* LeaderboardScoresDownloaded, bool bIOFailure);
	SteamAPICall_t CallbackHandle;
#endif
	
};
