
#include "SIK_GetAppDependencies_AsyncFunction.h"

#include "Async/Async.h"

USIK_GetAppDependencies_AsyncFunction* USIK_GetAppDependencies_AsyncFunction::GetAppDependencies(FSIK_PublishedFileId PublishedFileID)
{
    USIK_GetAppDependencies_AsyncFunction* Obj = NewObject<USIK_GetAppDependencies_AsyncFunction>();
    Obj->Var_PublishedFileID = PublishedFileID;
    return Obj;
}

void USIK_GetAppDependencies_AsyncFunction::Activate()
{
    Super::Activate();
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
    if(!SteamUGC())
    {
        OnFailure.Broadcast(ESIK_Result::ResultFail, Var_PublishedFileID, TArray<FSIK_AppId>(), 0, 0);
        SetReadyToDestroy();
        MarkAsGarbage();
        return;
    }
    CallbackHandle = SteamUGC()->GetAppDependencies(Var_PublishedFileID.GetPublishedFileId());
    if(CallbackHandle == k_uAPICallInvalid)
    {
        OnFailure.Broadcast(ESIK_Result::ResultFail, Var_PublishedFileID, TArray<FSIK_AppId>(), 0, 0);
        SetReadyToDestroy();
        MarkAsGarbage();
        return;
    }
    CallResult.Set(CallbackHandle, this, &USIK_GetAppDependencies_AsyncFunction::OnComplete);
#else
    OnFailure.Broadcast(ESIK_Result::ResultFail, Var_PublishedFileID, TArray<FSIK_AppId>(), 0, 0);
    SetReadyToDestroy();
    MarkAsGarbage();
#endif
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
void USIK_GetAppDependencies_AsyncFunction::OnComplete(GetAppDependenciesResult_t* pResult, bool bIOFailure)
{
    auto Param = *pResult;
    AsyncTask(ENamedThreads::GameThread, [this, Param, bIOFailure]()
    {
        if(bIOFailure)
        {
            OnFailure.Broadcast(ESIK_Result::ResultFail, Var_PublishedFileID, TArray<FSIK_AppId>(), 0, 0);
        }
        else
        {
            ESIK_Result Result = static_cast<ESIK_Result>(Param.m_eResult);
            TArray<FSIK_AppId> AppIDs;
            for(int32 i = 0; i < int32(Param.m_nNumAppDependencies); i++)
            {
                AppIDs.Add(FSIK_AppId(Param.m_rgAppIDs[i]));
            }
            OnSuccess.Broadcast(Result, Param.m_nPublishedFileId, AppIDs, Param.m_nNumAppDependencies, Param.m_nTotalNumAppDependencies);
        }
    });
    
    SetReadyToDestroy();
    MarkAsGarbage();
}
#endif