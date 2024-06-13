// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
THIRD_PARTY_INCLUDES_START
#if WITH_ENGINE_STEAM
#include <steam/steam_api.h>
#include <steam/steamtypes.h>
#include <steam/isteamuserstats.h>
#include <steam/steam_api_common.h>
#else
#include <steamtypes.h>
#include <isteamuserstats.h>
#include <steam_api_common.h>
#endif
THIRD_PARTY_INCLUDES_END
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
	FString SteamID = "Empty";

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
	void OnDownloadLeaderboardEntries(LeaderboardScoresDownloaded_t* LeaderboardScoresDownloaded, bool bIOFailure);
	virtual void Activate() override;
	SteamAPICall_t CallbackHandle;
	int32 Var_LeaderboardId;
	int32 Var_RangeStart;
	int32 Var_RangeEnd;
	TEnumAsByte<ESIK_LeaderboardDataRequest> Var_LeaderboardDataRequest;
	CCallResult<USIK_DownloadLeaderboardEntries_AsyncFunction, LeaderboardScoresDownloaded_t> OnDownloadLeaderboardEntriesCallResult;
	
};
