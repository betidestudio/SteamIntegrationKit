// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
THIRD_PARTY_INCLUDES_START
#if WITH_ENGINE_STEAM
#include <steam/steam_api.h>
#include <steam/isteamuserstats.h>
#include <steam/steam_api_common.h>
#else
#include <steamtypes.h>
#include <isteamuserstats.h>
#include <steam_api_common.h>
#endif
THIRD_PARTY_INCLUDES_END
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SIK_SharedFile.h"
#include "SIK_RequestGlobalStats_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSIK_RequestGlobalStatsDel, TEnumAsByte<ESIK_Result>, Result);

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_RequestGlobalStats_AsyncFunction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, DisplayName = "Request Steam Global Stats", meta = (BlueprintInternalUseOnly = "true"), Category = "Steam Integration Kit || SDK Functions || User Stats")
	static USIK_RequestGlobalStats_AsyncFunction* RequestGlobalStats(int32 HistoryDays);
	
	UPROPERTY(BlueprintAssignable)
	FSIK_RequestGlobalStatsDel OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FSIK_RequestGlobalStatsDel OnFailure;
private:
	int32 Var_HistoryDays;
	void OnRequestGlobalStats(GlobalStatsReceived_t* GlobalStatsReceived, bool bIOFailure);
	virtual void Activate() override;
	SteamAPICall_t m_CallbackHandle;
	CCallResult<USIK_RequestGlobalStats_AsyncFunction, GlobalStatsReceived_t> m_OnRequestGlobalStatsCallResult;
	
};
