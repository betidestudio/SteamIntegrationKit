
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
#include "SIK_StartPlaytimeTracking_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStartPlaytimeTrackingComplete, TEnumAsByte<ESIK_Result>, Result);

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_StartPlaytimeTracking_AsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category="Steam Integration Kit || SDK Functions || UGC")
    static USIK_StartPlaytimeTracking_AsyncFunction* StartPlaytimeTracking(TArray<FSIK_PublishedFileId> PublishedFileID, int32 NumPublishedFileIDs);
    
    UPROPERTY(BlueprintAssignable)
    FOnStartPlaytimeTrackingComplete OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FOnStartPlaytimeTrackingComplete OnFailure;

private:
    TArray<FSIK_PublishedFileId> Var_PublishedFileID;
    int32 Var_NumPublishedFileIDs;
    virtual void Activate() override;
    void OnComplete(StartPlaytimeTrackingResult_t* CallbackData, bool bIOFailure);
    SteamAPICall_t CallbackHandle;
    CCallResult<USIK_StartPlaytimeTracking_AsyncFunction, StartPlaytimeTrackingResult_t> CallResult;
};
        