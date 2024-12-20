
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
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
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
    void OnComplete(RemoteStorageSubscribePublishedFileResult_t* pResult, bool bIOFailure);
    SteamAPICall_t CallbackHandle;
    CCallResult<USIK_SubscribeItem_AsyncFunction, RemoteStorageSubscribePublishedFileResult_t> CallResult;
#endif
};
        