
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SIK_SharedFile.h"
#include "SIK_AddAppDependency_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAddAppDependencyComplete, TEnumAsByte<ESIK_Result>, Result, FSIK_PublishedFileId, PublishedFileID, FSIK_AppId, AppID);

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_AddAppDependency_AsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category="Steam Integration Kit || SDK Functions || UGC")
    static USIK_AddAppDependency_AsyncFunction* AddAppDependency(FSIK_PublishedFileId PublishedFileID, FSIK_AppId AppID);

    UPROPERTY(BlueprintAssignable)
    FOnAddAppDependencyComplete OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FOnAddAppDependencyComplete OnFailure;

private:
    FSIK_PublishedFileId Var_PublishedFileID;
    FSIK_AppId Var_AppID;
    virtual void Activate() override;
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
    void OnComplete(AddAppDependencyResult_t* pResult, bool bIOFailure);
    SteamAPICall_t CallbackHandle;
    CCallResult<USIK_AddAppDependency_AsyncFunction, AddAppDependencyResult_t> CallResult;
#endif
};
        