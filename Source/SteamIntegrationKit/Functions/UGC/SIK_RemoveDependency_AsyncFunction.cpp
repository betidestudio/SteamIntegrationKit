
#include "SIK_RemoveDependency_AsyncFunction.h"

#include "Async/Async.h"

USIK_RemoveDependency_AsyncFunction* USIK_RemoveDependency_AsyncFunction::RemoveDependency(FSIK_PublishedFileId ParentPublishedFileID, FSIK_PublishedFileId ChildPublishedFileID)
{
    USIK_RemoveDependency_AsyncFunction* Node = NewObject<USIK_RemoveDependency_AsyncFunction>();
    Node->Var_ParentPublishedFileID = ParentPublishedFileID;
    Node->Var_ChildPublishedFileID = ChildPublishedFileID;
    return Node;
}

void USIK_RemoveDependency_AsyncFunction::Activate()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
    if(!SteamUGC())
    {
        OnFailure.Broadcast(ResultFail, Var_ParentPublishedFileID, Var_ChildPublishedFileID);
        SetReadyToDestroy();
        return;
    }
    CallbackHandle = SteamUGC()->RemoveDependency(Var_ParentPublishedFileID.GetPublishedFileId(), Var_ChildPublishedFileID.GetPublishedFileId());
    if(CallbackHandle == k_uAPICallInvalid)
    {
        OnFailure.Broadcast(ResultFail, Var_ParentPublishedFileID, Var_ChildPublishedFileID);
        SetReadyToDestroy();
        MarkAsGarbage();
        return;
    }
    CallResult.Set(CallbackHandle, this, &USIK_RemoveDependency_AsyncFunction::OnComplete);
#else
    OnFailure.Broadcast(ResultFail, Var_ParentPublishedFileID, Var_ChildPublishedFileID);
    SetReadyToDestroy();
    MarkAsGarbage();
#endif
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
void USIK_RemoveDependency_AsyncFunction::OnComplete(RemoveUGCDependencyResult_t* pResult, bool bIOFailure)
{
    auto Param = *pResult;
    AsyncTask(ENamedThreads::GameThread, [this, Param, bIOFailure]()
    {
        if(bIOFailure)
        {
            OnFailure.Broadcast(ResultFail, Var_ParentPublishedFileID, Var_ChildPublishedFileID);
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