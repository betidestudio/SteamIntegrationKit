// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineAsyncTaskManager.h"
#include "SIK_SharedFile.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SIK_RequestInternetServerList_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRequestInternalServerListDelegate, TEnumAsByte<ESIK_MatchMakingServerResponse>, Response, const TArray<FSIK_FoundServers>&, ServerList);

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_RequestInternetServerList_AsyncFunction : public UBlueprintAsyncActionBase
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	, public ISteamMatchmakingServerListResponse
#endif
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, DisplayName="Request Internet Server List", Category = "Steam Integration Kit || SDK Functions || Matchmaking Servers",meta=(AutoCreateRefTerm="Filters", BlueprintInternalUseOnly = "true"))
	static USIK_RequestInternetServerList_AsyncFunction* RequestInternetServerList(FSIK_AppId AppId, const TMap<FString, FString>& Filters, float TimeOut = 10.0f);

	UPROPERTY(BlueprintAssignable)
	FRequestInternalServerListDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FRequestInternalServerListDelegate OnFailure;
	
private:
	FSIK_AppId VarAppId;
	TMap<FString, FString> Filters;
	virtual void Activate() override;
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	virtual void ServerResponded(HServerListRequest hRequest, int iServer) override;
	virtual void ServerFailedToRespond(HServerListRequest hRequest, int iServer) override;
	virtual void RefreshComplete(HServerListRequest hRequest, EMatchMakingServerResponse response) override;
#endif
	double StartTime;
	float Var_TimeOut = 10.0f;
	
};
