
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
#include "SIK_UnsubscribeItem_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUnsubscribeItemComplete, TEnumAsByte<ESIK_Result>, Result, FSIK_PublishedFileId, PublishedFileID);

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_UnsubscribeItem_AsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category="Steam Integration Kit || SDK Functions || UGC")
    static USIK_UnsubscribeItem_AsyncFunction* UnsubscribeItem(FSIK_PublishedFileId PublishedFileID);

    UPROPERTY(BlueprintAssignable)
    FOnUnsubscribeItemComplete OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FOnUnsubscribeItemComplete OnFailure;

private:
    FSIK_PublishedFileId Var_PublishedFileID;
    virtual void Activate() override;
    void OnComplete(RemoteStorageUnsubscribePublishedFileResult_t* pResult, bool bIOFailure);
    SteamAPICall_t CallbackHandle;
    CCallResult<USIK_UnsubscribeItem_AsyncFunction, RemoteStorageUnsubscribePublishedFileResult_t> CallResult;
};
        