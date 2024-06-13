
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
THIRD_PARTY_INCLUDES_START
#if WITH_ENGINE_STEAM
#include <steam/steam_api.h>
#else
#include <steam_api.h>
#endif
THIRD_PARTY_INCLUDES_END
#include "SIK_SharedFile.h"
#include "SIK_StopPlaytimeTracking_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStopPlaytimeTrackingComplete, TEnumAsByte<ESIK_Result>, Result);

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_StopPlaytimeTracking_AsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category="Steam Integration Kit || SDK Functions || UGC")
    static USIK_StopPlaytimeTracking_AsyncFunction* StopPlaytimeTracking(TArray<FSIK_PublishedFileId> PublishedFileID, int32 NumPublishedFileIDs);
    
    UPROPERTY(BlueprintAssignable)
    FOnStopPlaytimeTrackingComplete OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FOnStopPlaytimeTrackingComplete OnFailure;

private:
    TArray<FSIK_PublishedFileId> Var_PublishedFileID;
    int32 Var_NumPublishedFileIDs;
    virtual void Activate() override;
    void OnComplete(StopPlaytimeTrackingResult_t *pCallback, bool bIOFailure);
    SteamAPICall_t CallbackHandle;
    CCallResult<USIK_StopPlaytimeTracking_AsyncFunction, StopPlaytimeTrackingResult_t> CallResult;
};
        