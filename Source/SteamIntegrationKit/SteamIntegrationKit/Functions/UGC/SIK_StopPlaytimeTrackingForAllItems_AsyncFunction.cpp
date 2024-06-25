
#include "SIK_StopPlaytimeTrackingForAllItems_AsyncFunction.h"

#include "Async/Async.h"

USIK_StopPlaytimeTrackingForAllItems_AsyncFunction* USIK_StopPlaytimeTrackingForAllItems_AsyncFunction::StopPlaytimeTrackingForAllItems()
{
    USIK_StopPlaytimeTrackingForAllItems_AsyncFunction* Obj = NewObject<USIK_StopPlaytimeTrackingForAllItems_AsyncFunction>();
    return Obj;
}

void USIK_StopPlaytimeTrackingForAllItems_AsyncFunction::Activate()
{
    if(!SteamUGC())
    {
        OnFailure.Broadcast(ESIK_Result::ResultFail);
        SetReadyToDestroy();
        return;
    }
    CallbackHandle = SteamUGC()->StopPlaytimeTrackingForAllItems();
    if(CallbackHandle == k_uAPICallInvalid)
    {
        OnFailure.Broadcast(ESIK_Result::ResultFail);
        SetReadyToDestroy();
        MarkAsGarbage();
        return;
    }
    CallResult.Set(CallbackHandle, this, &USIK_StopPlaytimeTrackingForAllItems_AsyncFunction::OnComplete);
}

void USIK_StopPlaytimeTrackingForAllItems_AsyncFunction::OnComplete(StopPlaytimeTrackingResult_t* CallbackData, bool bIOFailure)
{
    auto Param = *CallbackData;
    AsyncTask(ENamedThreads::GameThread, [this, Param, bIOFailure]()
    {
        if(bIOFailure)
        {
            OnFailure.Broadcast(ESIK_Result::ResultFail);
        }
        else
        {
            OnSuccess.Broadcast(static_cast<ESIK_Result>(Param.m_eResult));
        }
    });
    SetReadyToDestroy();
    MarkAsGarbage();
}
        