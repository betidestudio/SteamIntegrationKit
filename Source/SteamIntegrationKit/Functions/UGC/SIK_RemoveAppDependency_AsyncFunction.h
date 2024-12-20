
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SIK_SharedFile.h"
#include "SIK_RemoveAppDependency_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnRemoveAppDependencyComplete, TEnumAsByte<ESIK_Result>, Result, FSIK_PublishedFileId, PublishedFileID, FSIK_AppId, AppID);

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_RemoveAppDependency_AsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category="Steam Integration Kit || SDK Functions || UGC")
    static USIK_RemoveAppDependency_AsyncFunction* RemoveAppDependency(FSIK_PublishedFileId PublishedFileID, FSIK_AppId AppID);

    UPROPERTY(BlueprintAssignable)
    FOnRemoveAppDependencyComplete OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FOnRemoveAppDependencyComplete OnFailure;

private:
    FSIK_PublishedFileId Var_PublishedFileID;
    FSIK_AppId Var_AppID;
    void Activate() override;
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
    void OnComplete(RemoveAppDependencyResult_t* CallbackData, bool bIOFailure);
    SteamAPICall_t CallbackHandle;
    CCallResult<USIK_RemoveAppDependency_AsyncFunction, RemoveAppDependencyResult_t> CallResult;
#endif
};
        