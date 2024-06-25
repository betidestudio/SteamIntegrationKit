
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
    void OnComplete(GetAppDependenciesResult_t* pResult, bool bIOFailure);
    SteamAPICall_t CallbackHandle;
    CCallResult<USIK_GetAppDependencies_AsyncFunction, GetAppDependenciesResult_t> CallResult;
};
        