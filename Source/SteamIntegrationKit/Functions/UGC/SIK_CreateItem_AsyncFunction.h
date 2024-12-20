
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SIK_SharedFile.h"
#include "SIK_CreateItem_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCreateItemComplete, TEnumAsByte<ESIK_Result>, Result, FSIK_PublishedFileId, PublishedFileId, bool, bUserNeedsToAcceptWorkshopLegalAgreement);

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_CreateItem_AsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category="Steam Integration Kit || SDK Functions || UGC")
    static USIK_CreateItem_AsyncFunction* CreateItem(FSIK_AppId ConsumerAppId, ESIK_WorkshopFileType FileType);

    UPROPERTY(BlueprintAssignable)
    FOnCreateItemComplete OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FOnCreateItemComplete OnFailure;

private:
    FSIK_AppId Var_ConsumerAppId;
    ESIK_WorkshopFileType Var_FileType;
    virtual void Activate() override;
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
    void OnComplete(CreateItemResult_t* pResult, bool bIOFailure);
    SteamAPICall_t CallbackHandle;
    CCallResult<USIK_CreateItem_AsyncFunction, CreateItemResult_t> CallResult;
#endif
};
        