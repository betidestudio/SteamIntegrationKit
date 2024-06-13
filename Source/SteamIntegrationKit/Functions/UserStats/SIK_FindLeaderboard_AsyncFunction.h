// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
THIRD_PARTY_INCLUDES_START
#if WITH_ENGINE_STEAM
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
#include "SIK_FindLeaderboard_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFindLeaderboard_Delegate, int32, LeaderboardID);

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_FindLeaderboard_AsyncFunction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, DisplayName="Find Steam Leaderboard",meta = (BlueprintInternalUseOnly = "true"), Category="Steam Integration Kit || SDK Functions || User Stats")
	static USIK_FindLeaderboard_AsyncFunction* FindLeaderboard(const FString& LeaderboardName);
	
	UPROPERTY(BlueprintAssignable)
	FFindLeaderboard_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FFindLeaderboard_Delegate OnFailure;
private:
	virtual void Activate() override;
	SteamAPICall_t CallbackHandle;
	FString Var_LeaderboardName;
	void OnFindLeaderboard(LeaderboardFindResult_t* pResult, bool bIOFailure);
	CCallResult<USIK_FindLeaderboard_AsyncFunction, LeaderboardFindResult_t> OnFindLeaderboardCallResult;
};
