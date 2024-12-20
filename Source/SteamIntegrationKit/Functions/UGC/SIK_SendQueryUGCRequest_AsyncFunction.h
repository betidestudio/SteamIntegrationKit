
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SIK_SharedFile.h"
#include "SIK_SendQueryUGCRequest_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnSendQueryUGCRequestComplete, FSIK_UGCQueryHandle, QueryHandle, TEnumAsByte<ESIK_Result>, Result, int32, NumResultsReturned, int32, TotalMatchingResults, bool, bCachedData);

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_SendQueryUGCRequest_AsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category="Steam Integration Kit || SDK Functions || UGC")
    static USIK_SendQueryUGCRequest_AsyncFunction* SendQueryUGCRequest(FSIK_UGCQueryHandle QueryHandle);

    UPROPERTY(BlueprintAssignable)
    FOnSendQueryUGCRequestComplete OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FOnSendQueryUGCRequestComplete OnFailure;

private:
    FSIK_UGCQueryHandle Var_QueryHandle;
    virtual void Activate() override;
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
    void OnComplete(SteamUGCQueryCompleted_t* pCallback, bool bIOFailure);
    SteamAPICall_t CallbackHandle;
    CCallResult<USIK_SendQueryUGCRequest_AsyncFunction, SteamUGCQueryCompleted_t> CallResult;
#endif
};
        