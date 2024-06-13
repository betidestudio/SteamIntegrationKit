// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
THIRD_PARTY_INCLUDES_START
#if WITH_ENGINE_STEAM
#include <steam/steam_api.h>
#include <steam/isteammatchmaking.h>
#else
#include "isteammatchmaking.h"
#endif
THIRD_PARTY_INCLUDES_END
#include "OnlineAsyncTaskManager.h"
#include "SIK_SharedFile.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SIK_RequestHistoryServerList_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRequestHistoryServerListDelegate, TEnumAsByte<ESIK_MatchMakingServerResponse>, Response, const TArray<FSIK_FoundServers>&, ServerList);

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_RequestHistoryServerList_AsyncFunction : public UBlueprintAsyncActionBase, public ISteamMatchmakingServerListResponse
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, DisplayName="Request History Server List", Category = "Steam Integration Kit || SDK Functions || Matchmaking Servers")
	static USIK_RequestHistoryServerList_AsyncFunction* RequestHistoryServerList(FSIK_AppId AppId, const TMap<FString, FString>& Filters, float TimeOut = 10.0f);

	UPROPERTY(BlueprintAssignable)
	FRequestHistoryServerListDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FRequestHistoryServerListDelegate OnFailure;
	
private:
	FSIK_AppId VarAppId;
	TMap<FString, FString> Filters;
	virtual void Activate() override;
	virtual void ServerResponded(HServerListRequest hRequest, int iServer) override;
	virtual void ServerFailedToRespond(HServerListRequest hRequest, int iServer) override;
	virtual void RefreshComplete(HServerListRequest hRequest, EMatchMakingServerResponse response) override;
	double StartTime;
	float Var_TimeOut = 10.0f;
	
};
