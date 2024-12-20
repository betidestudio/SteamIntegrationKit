
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SIK_SharedFile.h"
#include "SIK_DeleteItem_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDeleteItemComplete,TEnumAsByte<ESIK_Result>,Result,FSIK_PublishedFileId, PublishedFileId_t);

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_DeleteItem_AsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category="Steam Integration Kit || SDK Functions || UGC")
    static USIK_DeleteItem_AsyncFunction* DeleteItem(FSIK_PublishedFileId PublishedFileId);

    UPROPERTY(BlueprintAssignable)
    FOnDeleteItemComplete OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FOnDeleteItemComplete OnFailure;

private:
    FSIK_PublishedFileId Var_PublishedFileId;
    virtual void Activate() override;
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
    void OnComplete(DeleteItemResult_t* pResult, bool bIOFailure);
    SteamAPICall_t CallbackHandle;
    CCallResult<USIK_DeleteItem_AsyncFunction, DeleteItemResult_t> CallResult;
#endif
};
        