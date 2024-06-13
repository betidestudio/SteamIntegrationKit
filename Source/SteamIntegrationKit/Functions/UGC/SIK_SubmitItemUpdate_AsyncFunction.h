
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
    void OnComplete(SubmitItemUpdateResult_t* pResult, bool bIOFailure);
    SteamAPICall_t CallbackHandle;
    CCallResult<USIK_SubmitItemUpdate_AsyncFunction, SubmitItemUpdateResult_t> CallResult;
};
        