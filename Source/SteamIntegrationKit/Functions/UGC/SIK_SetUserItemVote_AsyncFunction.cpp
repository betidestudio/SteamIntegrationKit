
#include "SIK_SetUserItemVote_AsyncFunction.h"

#include "Async/Async.h"

USIK_SetUserItemVote_AsyncFunction* USIK_SetUserItemVote_AsyncFunction::SetUserItemVote(FSIK_PublishedFileId nPublishedFileID, bool bVoteUp)
{
    USIK_SetUserItemVote_AsyncFunction* Node = NewObject<USIK_SetUserItemVote_AsyncFunction>();
    Node->Var_PublishedFileID = nPublishedFileID;
    Node->Var_bVoteUp = bVoteUp;
    return Node;
}

void USIK_SetUserItemVote_AsyncFunction::Activate()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
    if(!SteamUGC())
    {
        OnFailure.Broadcast(FSIK_PublishedFileId(), false, ESIK_Result::ResultFail);
        SetReadyToDestroy();
        MarkAsGarbage();
        return;
    }
    CallbackHandle = SteamUGC()->SetUserItemVote(Var_PublishedFileID.GetPublishedFileId(), Var_bVoteUp);
    if(CallbackHandle == k_uAPICallInvalid)
    {
        OnFailure.Broadcast(FSIK_PublishedFileId(), false, ESIK_Result::ResultFail);
        SetReadyToDestroy();
        MarkAsGarbage();
        return;
    }
    CallResult.Set(CallbackHandle, this, &USIK_SetUserItemVote_AsyncFunction::OnComplete);
#else
    OnFailure.Broadcast(FSIK_PublishedFileId(), false, ESIK_Result::ResultFail);
    SetReadyToDestroy();
    MarkAsGarbage();
#endif
}


#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
void USIK_SetUserItemVote_AsyncFunction::OnComplete(SetUserItemVoteResult_t* Callback, bool bIOFailure)
{
    auto Param = *Callback;
    AsyncTask(ENamedThreads::GameThread, [this, Param, bIOFailure]()
    {
        if(bIOFailure)
        {
            OnFailure.Broadcast(FSIK_PublishedFileId(), false, ESIK_Result::ResultFail);
        }
        else
        {
            OnSuccess.Broadcast(FSIK_PublishedFileId(Param.m_nPublishedFileId), Param.m_bVoteUp, static_cast<ESIK_Result>(Param.m_eResult));
        }
    });
    SetReadyToDestroy();
    MarkAsGarbage();
}
#endif