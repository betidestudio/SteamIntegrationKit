
#include "SIK_UnsubscribeItem_AsyncFunction.h"

#include "Async/Async.h"

USIK_UnsubscribeItem_AsyncFunction* USIK_UnsubscribeItem_AsyncFunction::UnsubscribeItem(FSIK_PublishedFileId PublishedFileID)
{
    USIK_UnsubscribeItem_AsyncFunction* Node = NewObject<USIK_UnsubscribeItem_AsyncFunction>();
    Node->Var_PublishedFileID = PublishedFileID;
    return Node;
}

void USIK_UnsubscribeItem_AsyncFunction::Activate()
{
    if(!SteamUGC())
    {
        OnFailure.Broadcast(ESIK_Result::ResultFail, Var_PublishedFileID);
        SetReadyToDestroy();
        MarkAsGarbage();
        return;
    }
    CallbackHandle = SteamUGC()->UnsubscribeItem(Var_PublishedFileID.GetPublishedFileId());
    CallResult.Set(CallbackHandle, this, &USIK_UnsubscribeItem_AsyncFunction::OnComplete);
}

void USIK_UnsubscribeItem_AsyncFunction::OnComplete(RemoteStorageUnsubscribePublishedFileResult_t* pResult, bool bIOFailure)
{
    auto Param = *pResult;
    AsyncTask(ENamedThreads::GameThread, [this, Param, bIOFailure]()
    {
        if(bIOFailure)
        {
            OnFailure.Broadcast(ESIK_Result::ResultFail, Var_PublishedFileID);
        }
        else
        {
            OnSuccess.Broadcast(static_cast<ESIK_Result>(Param.m_eResult), Var_PublishedFileID);
        }
    });
    SetReadyToDestroy();
    MarkAsGarbage();
}