
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
THIRD_PARTY_INCLUDES_START
#if WITH_ENGINE_STEAM
#include <steam/steam_api.h>
#include <steam/isteamuserstats.h>
#include <steam/steam_api_common.h>
#else
#include <steam_api.h>
#include <isteamuserstats.h>
#include <steam_api_common.h>
#endif
THIRD_PARTY_INCLUDES_END
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
    void OnComplete(StopPlaytimeTrackingResult_t* pResult, bool bIOFailure);
    SteamAPICall_t CallbackHandle;
    CCallResult<USIK_StopPlaytimeTrackingForAllItems_AsyncFunction, StopPlaytimeTrackingResult_t> CallResult;
};
        