
#include "SIK_AddDependency_AsyncFunction.h"

#include "Async/Async.h"

USIK_AddDependency_AsyncFunction* USIK_AddDependency_AsyncFunction::AddDependency(FSIK_PublishedFileId ParentPublishedFileID, FSIK_PublishedFileId ChildPublishedFileID)
{
    USIK_AddDependency_AsyncFunction* Obj = NewObject<USIK_AddDependency_AsyncFunction>();
    Obj->Var_ParentPublishedFileID = ParentPublishedFileID;
    Obj->Var_ChildPublishedFileID = ChildPublishedFileID;
    return Obj;
}

void USIK_AddDependency_AsyncFunction::Activate()
{
    Super::Activate();
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
    if(!SteamUGC())
    {
        OnFailure.Broadcast(ESIK_Result::ResultFail, Var_ParentPublishedFileID, Var_ChildPublishedFileID);
        SetReadyToDestroy();
        MarkAsGarbage();
        return;
    }
    CallbackHandle = SteamUGC()->AddDependency(Var_ParentPublishedFileID.GetPublishedFileId(), Var_ChildPublishedFileID.GetPublishedFileId());
    if(CallbackHandle == k_uAPICallInvalid)
    {
        OnFailure.Broadcast(ESIK_Result::ResultFail, Var_ParentPublishedFileID, Var_ChildPublishedFileID);
        SetReadyToDestroy();
        MarkAsGarbage();
        return;
    }
    CallResult.Set(CallbackHandle, this, &USIK_AddDependency_AsyncFunction::OnComplete);
#else
    OnFailure.Broadcast(ESIK_Result::ResultFail, Var_ParentPublishedFileID, Var_ChildPublishedFileID);
    SetReadyToDestroy();
    MarkAsGarbage();
#endif
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
void USIK_AddDependency_AsyncFunction::OnComplete(AddUGCDependencyResult_t* pResult, bool bIOFailure)
{
    auto Param = *pResult;
    AsyncTask(ENamedThreads::GameThread, [this, Param, bIOFailure]()
    {
        if (bIOFailure)
        {
            OnFailure.Broadcast(ESIK_Result::ResultFail, Var_ParentPublishedFileID, Var_ChildPublishedFileID);
        }
        else
        {
            ESIK_Result Result = static_cast<ESIK_Result>(Param.m_eResult);
            OnSuccess.Broadcast(Result, Var_ParentPublishedFileID, Var_ChildPublishedFileID);
        }
    });
    SetReadyToDestroy();
    MarkAsGarbage();
}
#endif