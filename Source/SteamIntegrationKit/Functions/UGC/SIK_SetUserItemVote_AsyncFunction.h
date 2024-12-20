
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SIK_SharedFile.h"
#include "SIK_SetUserItemVote_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnSetUserItemVoteComplete, FSIK_PublishedFileId, PublishedFileID, bool, bVoteUp, TEnumAsByte<ESIK_Result>, Result);

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_SetUserItemVote_AsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category="Steam Integration Kit || SDK Functions || UGC")
    static USIK_SetUserItemVote_AsyncFunction* SetUserItemVote(FSIK_PublishedFileId PublishedFileID, bool bVoteUp);

    UPROPERTY(BlueprintAssignable)
    FOnSetUserItemVoteComplete OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FOnSetUserItemVoteComplete OnFailure;

private:
    FSIK_PublishedFileId Var_PublishedFileID;
    bool Var_bVoteUp;
    virtual void Activate() override;
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
    void OnComplete(SetUserItemVoteResult_t* Callback, bool bIOFailure);
    SteamAPICall_t CallbackHandle;
    CCallResult<USIK_SetUserItemVote_AsyncFunction, SetUserItemVoteResult_t> CallResult;
#endif
};
        