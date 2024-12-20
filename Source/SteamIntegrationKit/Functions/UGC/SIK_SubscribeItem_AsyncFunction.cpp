
#include "SIK_SubscribeItem_AsyncFunction.h"

#include "Async/Async.h"

USIK_SubscribeItem_AsyncFunction* USIK_SubscribeItem_AsyncFunction::SubscribeItem(FSIK_PublishedFileId PublishedFileID)
{
    USIK_SubscribeItem_AsyncFunction* Node = NewObject<USIK_SubscribeItem_AsyncFunction>();
    Node->Var_PublishedFileID = PublishedFileID;
    return Node;
}

void USIK_SubscribeItem_AsyncFunction::Activate()
{
    Super::Activate();
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
    if(!SteamUGC())
    {
        OnFailure.Broadcast(ESIK_Result::ResultFail, Var_PublishedFileID);
        SetReadyToDestroy();
        return;
    }
    CallbackHandle = SteamUGC()->SubscribeItem(Var_PublishedFileID.GetPublishedFileId());
    if(CallbackHandle == k_uAPICallInvalid)
    {
        OnFailure.Broadcast(ESIK_Result::ResultFail, Var_PublishedFileID);
        SetReadyToDestroy();
        MarkAsGarbage();
        return;
    }
    CallResult.Set(CallbackHandle, this, &USIK_SubscribeItem_AsyncFunction::OnComplete);
#else
    OnFailure.Broadcast(ESIK_Result::ResultFail, Var_PublishedFileID);
    SetReadyToDestroy();
    MarkAsGarbage();
#endif
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
void USIK_SubscribeItem_AsyncFunction::OnComplete(RemoteStorageSubscribePublishedFileResult_t* pResult, bool bIOFailure)
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
            OnSuccess.Broadcast(static_cast<ESIK_Result>(Param.m_eResult), Param.m_nPublishedFileId);
        }
    });
    SetReadyToDestroy();
    MarkAsGarbage();
}
#endif