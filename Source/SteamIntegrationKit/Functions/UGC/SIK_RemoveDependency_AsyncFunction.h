
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
#include <isteamugc.h>
#include <steam_api_common.h>
#endif
THIRD_PARTY_INCLUDES_END
#include "SIK_SharedFile.h"
#include "SIK_RemoveDependency_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnRemoveDependencyComplete, TEnumAsByte<ESIK_Result>, Result, FSIK_PublishedFileId, ParentPublishedFileID, FSIK_PublishedFileId, ChildPublishedFileID);

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_RemoveDependency_AsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category="Steam Integration Kit || SDK Functions || UGC")
    static USIK_RemoveDependency_AsyncFunction* RemoveDependency(FSIK_PublishedFileId ParentPublishedFileID, FSIK_PublishedFileId ChildPublishedFileID);

    UPROPERTY(BlueprintAssignable)
    FOnRemoveDependencyComplete OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FOnRemoveDependencyComplete OnFailure;

private:
    FSIK_PublishedFileId Var_ParentPublishedFileID;
    FSIK_PublishedFileId Var_ChildPublishedFileID;
    void Activate() override;
    void OnComplete(RemoveUGCDependencyResult_t* pResult, bool bIOFailure);
    SteamAPICall_t CallbackHandle;
    CCallResult<USIK_RemoveDependency_AsyncFunction, RemoveUGCDependencyResult_t> CallResult;
};
        