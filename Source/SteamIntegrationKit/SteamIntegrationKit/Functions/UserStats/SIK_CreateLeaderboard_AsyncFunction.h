// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
THIRD_PARTY_INCLUDES_START
#if WITH_ENGINE_STEAM
#include <steam/steam_api.h>
#include <steam/isteamuserstats.h>
#include <steam/steam_api_common.h>
#else
#include <steam_api.h>
#include <isteamuserstats.h>
#include <steam_api_common.h>
#endif
THIRD_PARTY_INCLUDES_END
#include "SIK_CreateLeaderboard_AsyncFunction.generated.h"

UENUM(BlueprintType)
enum ESIK_LeaderboardSortMethod
{
	LeaderboardSortMethodNone = 0 UMETA(DisplayName = "None"),	// no special display rules
	LeaderboardSortMethodAscending = 1 UMETA(DisplayName = "Ascending"),		// top-score is lowest number
	LeaderboardSortMethodDescending = 2 UMETA(DisplayName = "Descending"),	// top-score is highest number
};

UENUM(BlueprintType)
enum ESIK_LeaderboardDisplayType
{
	LeaderboardDisplayTypeNone = 0 UMETA(DisplayName = "None"),	// no special display rules
	LeaderboardDisplayTypeNumeric = 1 UMETA(DisplayName = "Numeric"),		// lower score is better
	LeaderboardDisplayTypeTimeSeconds = 2 UMETA(DisplayName = "TimeSeconds"),	// the duration is in seconds, the lower the value the better
	LeaderboardDisplayTypeTimeMilliSeconds = 3 UMETA(DisplayName = "TimeMilliSeconds"),	// the duration is in milliseconds, the lower the value the better,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCreateorFindLeaderboard_Delegate, int32, LeaderboardID);

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_CreateLeaderboard_AsyncFunction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, DisplayName="Create or Find Steam Leaderboard",meta = (BlueprintInternalUseOnly = "true"), Category="Steam Integration Kit || SDK Functions || User Stats")
	static USIK_CreateLeaderboard_AsyncFunction* CreateLeaderboard(const FString& LeaderboardName,TEnumAsByte<ESIK_LeaderboardSortMethod> SortMethod, TEnumAsByte<ESIK_LeaderboardDisplayType> DisplayType);

	UPROPERTY(BlueprintAssignable)
	FCreateorFindLeaderboard_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FCreateorFindLeaderboard_Delegate OnFailure;

	
private:
	CCallResult<USIK_CreateLeaderboard_AsyncFunction, LeaderboardFindResult_t> OnFindLeaderboardCallResult;
	FString Var_LeaderboardName;
	TEnumAsByte<ESIK_LeaderboardSortMethod> Var_SortMethod;
	TEnumAsByte<ESIK_LeaderboardDisplayType> Var_DisplayType;
	SteamAPICall_t CallbackHandle;
	void OnFindLeaderboard( LeaderboardFindResult_t *pResult, bool bIOFailure);
	virtual void Activate() override;
};
