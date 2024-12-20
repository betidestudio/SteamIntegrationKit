
#include "SIK_AddAppDependency_AsyncFunction.h"

#include "Async/Async.h"

USIK_AddAppDependency_AsyncFunction* USIK_AddAppDependency_AsyncFunction::AddAppDependency(FSIK_PublishedFileId PublishedFileID, FSIK_AppId AppID)
{
    USIK_AddAppDependency_AsyncFunction* Obj = NewObject<USIK_AddAppDependency_AsyncFunction>();
    Obj->Var_PublishedFileID = PublishedFileID;
    Obj->Var_AppID = AppID;
    return Obj;
}

void USIK_AddAppDependency_AsyncFunction::Activate()
{
    Super::Activate();
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
    if(!SteamUGC())
    {
        OnFailure.Broadcast(ESIK_Result::ResultFail, Var_PublishedFileID, Var_AppID);
        SetReadyToDestroy();
        MarkAsGarbage();
        return;
    }
    CallbackHandle = SteamUGC()->AddAppDependency(Var_PublishedFileID.GetPublishedFileId(), Var_AppID.GetAppID());
    if(CallbackHandle == k_uAPICallInvalid)
    {
        OnFailure.Broadcast(ESIK_Result::ResultFail, Var_PublishedFileID, Var_AppID);
        SetReadyToDestroy();
        MarkAsGarbage();
        return;
    }
    CallResult.Set(CallbackHandle, this, &USIK_AddAppDependency_AsyncFunction::OnComplete);
#else
    OnFailure.Broadcast(ESIK_Result::ResultFail, Var_PublishedFileID, Var_AppID);
    SetReadyToDestroy();
    MarkAsGarbage();
#endif
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
void USIK_AddAppDependency_AsyncFunction::OnComplete(AddAppDependencyResult_t* pResult, bool bIOFailure)
{
    auto Param = *pResult;
    AsyncTask(ENamedThreads::GameThread, [this, Param, bIOFailure]()
    {
        if (bIOFailure)
        {
            OnFailure.Broadcast(ESIK_Result::ResultFail, Var_PublishedFileID, Var_AppID);
        }
        else
        {
            ESIK_Result Result = static_cast<ESIK_Result>(Param.m_eResult);
            OnSuccess.Broadcast(Result, Var_PublishedFileID, Var_AppID);
        }
    });
    SetReadyToDestroy();
    MarkAsGarbage();
}
#endif