
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SIK_SharedFile.h"
#include "SIK_SubmitItemUpdate_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSubmitItemUpdateComplete, TEnumAsByte<ESIK_Result>, Result, bool, bUserNeedsToAcceptWorkshopLegalAgreement);

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_SubmitItemUpdate_AsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category="Steam Integration Kit || SDK Functions || UGC")
    static USIK_SubmitItemUpdate_AsyncFunction* SubmitItemUpdate(FSIK_UGCUpdateHandle UgcUpdateHandle, const FString& ChangeNote);

    UPROPERTY(BlueprintAssignable)
    FOnSubmitItemUpdateComplete OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FOnSubmitItemUpdateComplete OnFailure;

private:
    FSIK_UGCUpdateHandle Var_UgcUpdateHandle;
    FString Var_ChangeNote;
    virtual void Activate() override;
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
    void OnComplete(SubmitItemUpdateResult_t* pResult, bool bIOFailure);
    SteamAPICall_t CallbackHandle;
    CCallResult<USIK_SubmitItemUpdate_AsyncFunction, SubmitItemUpdateResult_t> CallResult;
#endif
};
        