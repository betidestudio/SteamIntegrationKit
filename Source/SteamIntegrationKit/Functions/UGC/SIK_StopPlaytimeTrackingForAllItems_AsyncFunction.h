
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SIK_SharedFile.h"
#include "SIK_StopPlaytimeTrackingForAllItems_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStopPlaytimeTrackingForAllItemsComplete, TEnumAsByte<ESIK_Result>, Result);

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_StopPlaytimeTrackingForAllItems_AsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category="Steam Integration Kit || SDK Functions || UGC")
    static USIK_StopPlaytimeTrackingForAllItems_AsyncFunction* StopPlaytimeTrackingForAllItems();

    UPROPERTY(BlueprintAssignable)
    FOnStopPlaytimeTrackingForAllItemsComplete OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FOnStopPlaytimeTrackingForAllItemsComplete OnFailure;

private:
    virtual void Activate() override;
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
    SteamAPICall_t CallbackHandle;
    void OnComplete(StopPlaytimeTrackingResult_t* pResult, bool bIOFailure);
    CCallResult<USIK_StopPlaytimeTrackingForAllItems_AsyncFunction, StopPlaytimeTrackingResult_t> CallResult;
#endif
};
        