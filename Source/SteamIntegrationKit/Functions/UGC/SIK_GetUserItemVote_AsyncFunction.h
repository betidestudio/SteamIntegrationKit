
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SIK_SharedFile.h"
#include "SIK_GetUserItemVote_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnGetUserItemVoteComplete, TEnumAsByte<ESIK_Result>, Result, FSIK_PublishedFileId, PublishedFileId, bool, bVotedUp, bool, bVotedDown, bool, bVoteSkipped);

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_GetUserItemVote_AsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category="Steam Integration Kit || SDK Functions || UGC")
    static USIK_GetUserItemVote_AsyncFunction* GetUserItemVote(FSIK_PublishedFileId PublishedFileID);

    UPROPERTY(BlueprintAssignable)
    FOnGetUserItemVoteComplete OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FOnGetUserItemVoteComplete OnFailure;

private:
    FSIK_PublishedFileId Var_PublishedFileID;
    void Activate() override;
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
    void OnComplete(GetUserItemVoteResult_t* pResult, bool bIOFailure);
    SteamAPICall_t CallbackHandle;
    CCallResult<USIK_GetUserItemVote_AsyncFunction, GetUserItemVoteResult_t> CallResult;
#endif
};
        