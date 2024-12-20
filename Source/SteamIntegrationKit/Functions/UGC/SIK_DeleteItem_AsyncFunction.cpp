
#include "SIK_DeleteItem_AsyncFunction.h"

#include "Async/Async.h"

USIK_DeleteItem_AsyncFunction* USIK_DeleteItem_AsyncFunction::DeleteItem(FSIK_PublishedFileId PublishedFileId)
{
    USIK_DeleteItem_AsyncFunction* Obj = NewObject<USIK_DeleteItem_AsyncFunction>();
    Obj->Var_PublishedFileId = PublishedFileId;
    return Obj;
}

void USIK_DeleteItem_AsyncFunction::Activate()
{
    Super::Activate();
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
    if(!SteamUGC())
    {
        OnFailure.Broadcast(ESIK_Result::ResultFail,FSIK_PublishedFileId());
        SetReadyToDestroy();
        return;
    }
    CallbackHandle = SteamUGC()->DeleteItem(Var_PublishedFileId.GetPublishedFileId());
    if(CallbackHandle == k_uAPICallInvalid)
    {
        OnFailure.Broadcast(ESIK_Result::ResultFail,FSIK_PublishedFileId());
        SetReadyToDestroy();
        MarkAsGarbage();
        return;
    }
    CallResult.Set(CallbackHandle, this, &USIK_DeleteItem_AsyncFunction::OnComplete);
#else
    OnFailure.Broadcast(ESIK_Result::ResultFail,FSIK_PublishedFileId());
    SetReadyToDestroy();
    MarkAsGarbage();
#endif
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
void USIK_DeleteItem_AsyncFunction::OnComplete(DeleteItemResult_t* pResult, bool bIOFailure)
{
    auto Param = *pResult;
    AsyncTask(ENamedThreads::GameThread, [this, Param, bIOFailure]()
    {
        if(bIOFailure)
        {
            OnFailure.Broadcast(ESIK_Result::ResultFail,FSIK_PublishedFileId());
        }
        else
        {
            ESIK_Result Result = static_cast<ESIK_Result>(Param.m_eResult);
            OnSuccess.Broadcast(Result, FSIK_PublishedFileId(Param.m_nPublishedFileId));
        }
    });
    SetReadyToDestroy();
    MarkAsGarbage();
}
#endif