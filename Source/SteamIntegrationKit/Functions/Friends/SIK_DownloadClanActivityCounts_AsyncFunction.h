// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SIK_FriendsLibrary.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SIK_DownloadClanActivityCounts_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDownloadClanActivityCountsComplete);
UCLASS()
class STEAMINTEGRATIONKIT_API USIK_DownloadClanActivityCounts_AsyncFunction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, DisplayName="Download Steam Clan Activity Counts",meta = (BlueprintInternalUseOnly = "true",Keywords="DownloadClanActivityCounts"), Category= "Steam Integration Kit || SDK Functions || Friends")
	static USIK_DownloadClanActivityCounts_AsyncFunction* DownloadClanActivityCounts(const TArray<int64>& ClanIds);


	UPROPERTY(BlueprintAssignable)
	FOnDownloadClanActivityCountsComplete OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnDownloadClanActivityCountsComplete OnFailure;
private:
	TArray<int64> Var_ClanIds;
	virtual void Activate() override;
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	void OnDownloadClanActivityCounts(DownloadClanActivityCountsResult_t* DownloadClanActivityCountsResult, bool bIOFailure);
	SteamAPICall_t CallbackHandle;
	CCallResult<USIK_DownloadClanActivityCounts_AsyncFunction, DownloadClanActivityCountsResult_t> OnDownloadClanActivityCountsCallResult;
#endif
};
