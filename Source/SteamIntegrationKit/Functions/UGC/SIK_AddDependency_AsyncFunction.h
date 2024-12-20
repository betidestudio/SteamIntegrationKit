
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SIK_SharedFile.h"
#include "SIK_AddDependency_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAddDependencyComplete, TEnumAsByte<ESIK_Result>, Result, FSIK_PublishedFileId, ParentPublishedFileID, FSIK_PublishedFileId, ChildPublishedFileID);

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_AddDependency_AsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category="Steam Integration Kit || SDK Functions || UGC")
    static USIK_AddDependency_AsyncFunction* AddDependency(FSIK_PublishedFileId ParentPublishedFileID, FSIK_PublishedFileId ChildPublishedFileID);

    UPROPERTY(BlueprintAssignable)
    FOnAddDependencyComplete OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FOnAddDependencyComplete OnFailure;

private:
    FSIK_PublishedFileId Var_ParentPublishedFileID;
    FSIK_PublishedFileId Var_ChildPublishedFileID;
    void Activate() override;
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
    void OnComplete(AddUGCDependencyResult_t* pResult, bool bIOFailure);
    SteamAPICall_t CallbackHandle;
    CCallResult<USIK_AddDependency_AsyncFunction, AddUGCDependencyResult_t> CallResult;
#endif
};
        