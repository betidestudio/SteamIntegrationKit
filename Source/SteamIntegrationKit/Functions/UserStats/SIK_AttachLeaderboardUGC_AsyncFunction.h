// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SIK_SharedFile.h"
#include "SIK_AttachLeaderboardUGC_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAttachLeaderboardUGC_Delegate);

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_AttachLeaderboardUGC_AsyncFunction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, DisplayName="Attach UGC To Steam Leaderboard",meta = (BlueprintInternalUseOnly = "true"), Category="Steam Integration Kit || SDK Functions || User Stats")
	static USIK_AttachLeaderboardUGC_AsyncFunction* AttachLeaderboardUGC(int32 LeaderboardId, int64 UGCHandle);
	
	UPROPERTY(BlueprintAssignable)
	FAttachLeaderboardUGC_Delegate OnSuccess;
	
	UPROPERTY(BlueprintAssignable)
	FAttachLeaderboardUGC_Delegate OnFailure;
	
private:
	int32 Var_LeaderboardId;
	int64 Var_UGCHandle;
	
	virtual void Activate() override;
	
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	void OnAttachLeaderboardUGC(LeaderboardUGCSet_t* LeaderboardUGCSet, bool bIOFailure);
	SteamAPICall_t CallbackHandle;
	CCallResult<USIK_AttachLeaderboardUGC_AsyncFunction, LeaderboardUGCSet_t> OnAttachLeaderboardUGCCallResult;
#endif
};