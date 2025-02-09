// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineAsyncTaskManager.h"
#include "SIK_SharedFile.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SIK_RequestLANServerList_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRequestLANServerListDelegate, TEnumAsByte<ESIK_MatchMakingServerResponse>, Response, const TArray<FSIK_FoundServers>&, ServerList);

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_RequestLANServerList_AsyncFunction : public UBlueprintAsyncActionBase
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	, public ISteamMatchmakingServerListResponse
#endif
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, DisplayName="Request LAN Server List", Category = "Steam Integration Kit || SDK Functions || Matchmaking Servers",meta=(BlueprintInternalUseOnly = "true"))
	static USIK_RequestLANServerList_AsyncFunction* RequestLANServerList(FSIK_AppId AppId, float TimeOut = 10.0f);

	UPROPERTY(BlueprintAssignable)
	FRequestLANServerListDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FRequestLANServerListDelegate OnFailure;
	
private:
	FSIK_AppId VarAppId;
	virtual void Activate() override;
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	virtual void ServerResponded(HServerListRequest hRequest, int iServer) override;
	virtual void ServerFailedToRespond(HServerListRequest hRequest, int iServer) override;
	virtual void RefreshComplete(HServerListRequest hRequest, EMatchMakingServerResponse response) override;
#endif
	double StartTime;
	float Var_TimeOut = 10.0f;
	
};
