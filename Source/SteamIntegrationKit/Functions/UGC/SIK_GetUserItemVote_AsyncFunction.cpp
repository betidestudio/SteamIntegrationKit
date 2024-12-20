
#include "SIK_GetUserItemVote_AsyncFunction.h"

#include "Async/Async.h"

USIK_GetUserItemVote_AsyncFunction* USIK_GetUserItemVote_AsyncFunction::GetUserItemVote(FSIK_PublishedFileId PublishedFileID)
{
    USIK_GetUserItemVote_AsyncFunction* Obj = NewObject<USIK_GetUserItemVote_AsyncFunction>();
    Obj->Var_PublishedFileID = PublishedFileID;
    return Obj;
}

void USIK_GetUserItemVote_AsyncFunction::Activate()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
    if(!SteamUGC())
    {
        OnFailure.Broadcast(ESIK_Result::ResultFail, FSIK_PublishedFileId(), false, false, false);
        SetReadyToDestroy();
        MarkAsGarbage();
        return;
    }
    CallbackHandle = SteamUGC()->GetUserItemVote(Var_PublishedFileID.GetPublishedFileId());
    if(CallbackHandle == k_uAPICallInvalid)
    {
        OnFailure.Broadcast(ESIK_Result::ResultFail, FSIK_PublishedFileId(), false, false, false);
        SetReadyToDestroy();
        MarkAsGarbage();
        return;
    }
    CallResult.Set(CallbackHandle, this, &USIK_GetUserItemVote_AsyncFunction::OnComplete);
#else
    OnFailure.Broadcast(ESIK_Result::ResultFail, FSIK_PublishedFileId(), false, false, false);
    SetReadyToDestroy();
    MarkAsGarbage();
#endif
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
void USIK_GetUserItemVote_AsyncFunction::OnComplete(GetUserItemVoteResult_t* pResult, bool bIOFailure)
{
    auto Param = *pResult;
    AsyncTask(ENamedThreads::GameThread, [this, Param, bIOFailure]()
    {
        if(bIOFailure)
        {
            OnFailure.Broadcast(ESIK_Result::ResultFail, FSIK_PublishedFileId(), false, false, false);
            SetReadyToDestroy();
            MarkAsGarbage();
            return;
        }
        TEnumAsByte<ESIK_Result> Result = static_cast<ESIK_Result>(Param.m_eResult);
        OnSuccess.Broadcast(Result, FSIK_PublishedFileId(Param.m_nPublishedFileId), Param.m_bVotedUp, Param.m_bVotedDown, Param.m_bVoteSkipped);
    });
    SetReadyToDestroy();
    MarkAsGarbage();
}
#endif