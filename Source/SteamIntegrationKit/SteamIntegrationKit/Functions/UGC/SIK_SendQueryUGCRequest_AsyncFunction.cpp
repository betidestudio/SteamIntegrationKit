
#include "SIK_SendQueryUGCRequest_AsyncFunction.h"

#include "Async/Async.h"

USIK_SendQueryUGCRequest_AsyncFunction* USIK_SendQueryUGCRequest_AsyncFunction::SendQueryUGCRequest(FSIK_UGCQueryHandle QueryHandle)
{
    USIK_SendQueryUGCRequest_AsyncFunction* BlueprintNode = NewObject<USIK_SendQueryUGCRequest_AsyncFunction>();
    BlueprintNode->Var_QueryHandle = QueryHandle;
    return BlueprintNode;
}

void USIK_SendQueryUGCRequest_AsyncFunction::Activate()
{
    if(!SteamUGC())
    {
        OnFailure.Broadcast(FSIK_UGCQueryHandle(), ESIK_Result::ResultFail, 0, 0, false);
        SetReadyToDestroy();
        return;
    }
    CallbackHandle = SteamUGC()->SendQueryUGCRequest(Var_QueryHandle.GetUGCQueryHandle());
    if(CallbackHandle == k_uAPICallInvalid)
    {
        OnFailure.Broadcast(FSIK_UGCQueryHandle(), ESIK_Result::ResultFail, 0, 0, false);
        SetReadyToDestroy();
        return;
    }
    CallResult.Set(CallbackHandle, this, &USIK_SendQueryUGCRequest_AsyncFunction::OnComplete);
}

void USIK_SendQueryUGCRequest_AsyncFunction::OnComplete(SteamUGCQueryCompleted_t* pCallback, bool bIOFailure)
{
    auto Param = *pCallback;
    AsyncTask(ENamedThreads::GameThread, [this, Param, bIOFailure]()
    {
        if(bIOFailure)
        {
            OnFailure.Broadcast(FSIK_UGCQueryHandle(), ESIK_Result::ResultFail, 0, 0, false);
        }
        else
        {
            OnSuccess.Broadcast(Param.m_handle, static_cast<ESIK_Result>(Param.m_eResult), Param.m_unNumResultsReturned, Param.m_unTotalMatchingResults, Param.m_bCachedData);
        }
    });
    SetReadyToDestroy();
    MarkAsGarbage();
}