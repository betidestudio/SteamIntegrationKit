// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
THIRD_PARTY_INCLUDES_START
#if WITH_ENGINE_STEAM
#include <steam/steamtypes.h>
#include <steam/isteamuserstats.h>
#include <steam/steam_api_common.h>
#else
#include "steamtypes.h"
#include "isteamuserstats.h"
#include "steam_api_common.h"
#endif
THIRD_PARTY_INCLUDES_END

#include "SIK_SharedFile.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SIK_RequestUserStats_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRequestUserStats_Delegate, TEnumAsByte<ESIK_Result>, Result);
UCLASS()
class STEAMINTEGRATIONKIT_API USIK_RequestUserStats_AsyncFunction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, DisplayName = "Request Steam User Stats", meta = (BlueprintInternalUseOnly = "true"), Category = "Steam Integration Kit || SDK Functions || User Stats")
	static USIK_RequestUserStats_AsyncFunction* RequestUserStats(FSIK_SteamId SteamID);
	
	UPROPERTY(BlueprintAssignable)
	FRequestUserStats_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FRequestUserStats_Delegate OnFailure;

private:
	FSIK_SteamId m_SteamID;
	void OnUserStatsReceived(UserStatsReceived_t* UserStatsReceived, bool bIOFailure);
	virtual void Activate() override;
	SteamAPICall_t m_CallbackHandle;
	CCallResult<USIK_RequestUserStats_AsyncFunction, UserStatsReceived_t> m_OnUserStatsReceived;

};
