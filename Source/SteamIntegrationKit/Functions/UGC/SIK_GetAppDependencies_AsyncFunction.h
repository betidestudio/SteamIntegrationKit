
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SIK_SharedFile.h"
#include "SIK_GetAppDependencies_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnGetAppDependenciesComplete, TEnumAsByte<ESIK_Result>, Result, FSIK_PublishedFileId, PublishedFileID, TArray<FSIK_AppId>, AppIDs, int32, NumAppIDs, int32, TotalNumAppIDs);

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_GetAppDependencies_AsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category="Steam Integration Kit || SDK Functions || UGC")
    static USIK_GetAppDependencies_AsyncFunction* GetAppDependencies(FSIK_PublishedFileId PublishedFileID);

    UPROPERTY(BlueprintAssignable)
    FOnGetAppDependenciesComplete OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FOnGetAppDependenciesComplete OnFailure;

private:
    FSIK_PublishedFileId Var_PublishedFileID;
    virtual void Activate() override;
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
    void OnComplete(GetAppDependenciesResult_t* pResult, bool bIOFailure);
    SteamAPICall_t CallbackHandle;
    CCallResult<USIK_GetAppDependencies_AsyncFunction, GetAppDependenciesResult_t> CallResult;
#endif
};
        