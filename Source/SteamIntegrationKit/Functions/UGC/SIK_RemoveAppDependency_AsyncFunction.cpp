
#include "SIK_RemoveAppDependency_AsyncFunction.h"

#include "Async/Async.h"

USIK_RemoveAppDependency_AsyncFunction* USIK_RemoveAppDependency_AsyncFunction::RemoveAppDependency(FSIK_PublishedFileId PublishedFileID, FSIK_AppId AppID)
{
    USIK_RemoveAppDependency_AsyncFunction* Node = NewObject<USIK_RemoveAppDependency_AsyncFunction>();
    Node->Var_PublishedFileID = PublishedFileID;
    Node->Var_AppID = AppID;
    return Node;
}

void USIK_RemoveAppDependency_AsyncFunction::Activate()
{
    Super::Activate();
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
    if(!SteamUGC())
    {
        OnFailure.Broadcast(ResultFail, FSIK_PublishedFileId(0), FSIK_AppId(0));
        SetReadyToDestroy();
        return;
    }
    CallbackHandle = SteamUGC()->RemoveAppDependency(Var_PublishedFileID.GetPublishedFileId(), Var_AppID.GetAppID());
    if(CallbackHandle == k_uAPICallInvalid)
    {
        OnFailure.Broadcast(ResultFail, FSIK_PublishedFileId(0), FSIK_AppId(0));
        SetReadyToDestroy();
        MarkAsGarbage();
        return;
    }
    CallResult.Set(CallbackHandle, this, &USIK_RemoveAppDependency_AsyncFunction::OnComplete);
#else
    OnFailure.Broadcast(ResultFail, FSIK_PublishedFileId(), FSIK_AppId(0));
    SetReadyToDestroy();
    MarkAsGarbage();
#endif
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
void USIK_RemoveAppDependency_AsyncFunction::OnComplete(RemoveAppDependencyResult_t* CallbackData, bool bIOFailure)
{
    auto Param = *CallbackData;
    AsyncTask(ENamedThreads::GameThread, [this, Param, bIOFailure]()
    {
        if(bIOFailure)
        {
            OnFailure.Broadcast(ResultFail, FSIK_PublishedFileId(0), FSIK_AppId(0));
        }
        else
        {
            ESIK_Result Result = static_cast<ESIK_Result>(Param.m_eResult);
            OnSuccess.Broadcast(Result, FSIK_PublishedFileId(Param.m_nPublishedFileId), FSIK_AppId(Param.m_nAppID));
        }
    });
    SetReadyToDestroy();
    MarkAsGarbage();
}
#endif