
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
THIRD_PARTY_INCLUDES_START
#if WITH_ENGINE_STEAM
#include <steam/steam_api.h>
#include <steam/isteamugc.h>
#include <steam/steam_api_common.h>
#else
#include <steam_api.h>
#include <steam_api_common.h>
#endif
THIRD_PARTY_INCLUDES_END
#include "SIK_SharedFile.h"
#include "SIK_SubscribeItem_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSubscribeItemComplete, TEnumAsByte<ESIK_Result>, Result, FSIK_PublishedFileId, PublishedFileID);

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_SubscribeItem_AsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category="Steam Integration Kit || SDK Functions || UGC")
    static USIK_SubscribeItem_AsyncFunction* SubscribeItem(FSIK_PublishedFileId PublishedFileID);

    UPROPERTY(BlueprintAssignable)
    FOnSubscribeItemComplete OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FOnSubscribeItemComplete OnFailure;

private:
    FSIK_PublishedFileId Var_PublishedFileID;
    virtual void Activate() override;
    void OnComplete(RemoteStorageSubscribePublishedFileResult_t* pResult, bool bIOFailure);
    SteamAPICall_t CallbackHandle;
    CCallResult<USIK_SubscribeItem_AsyncFunction, RemoteStorageSubscribePublishedFileResult_t> CallResult;
};
        