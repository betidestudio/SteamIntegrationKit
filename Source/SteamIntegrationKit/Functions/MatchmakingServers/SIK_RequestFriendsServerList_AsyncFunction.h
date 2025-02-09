// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SIK_SharedFile.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SIK_RequestFriendsServerList_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRequestFriendsServerListDelegate, TEnumAsByte<ESIK_MatchMakingServerResponse>, Response, const TArray<FSIK_FoundServers>&, ServerList);

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_RequestFriendsServerList_AsyncFunction : public UBlueprintAsyncActionBase
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	, public ISteamMatchmakingServerListResponse
#endif
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, DisplayName="Request Friends Server List", Category = "Steam Integration Kit || SDK Functions || Matchmaking Servers", meta=(AutoCreateRefTerm="Filters", BlueprintInternalUseOnly = "true"))
	static USIK_RequestFriendsServerList_AsyncFunction* RequestFriendsServerList(FSIK_AppId AppId, const TMap<FString, FString>& Filters, float TimeOut = 10.0f);

	UPROPERTY(BlueprintAssignable)
	FRequestFriendsServerListDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FRequestFriendsServerListDelegate OnFailure;
	
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
