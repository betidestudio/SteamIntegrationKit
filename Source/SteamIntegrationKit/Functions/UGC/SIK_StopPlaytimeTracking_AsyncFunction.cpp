
#include "SIK_StopPlaytimeTracking_AsyncFunction.h"

#include "Async/Async.h"


USIK_StopPlaytimeTracking_AsyncFunction* USIK_StopPlaytimeTracking_AsyncFunction::StopPlaytimeTracking(
    TArray<FSIK_PublishedFileId> PublishedFileID, int32 NumPublishedFileIDs)
{
    USIK_StopPlaytimeTracking_AsyncFunction* Obj = NewObject<USIK_StopPlaytimeTracking_AsyncFunction>();
    Obj->Var_PublishedFileID = PublishedFileID;
    Obj->Var_NumPublishedFileIDs = NumPublishedFileIDs;
    return Obj;
}

void USIK_StopPlaytimeTracking_AsyncFunction::Activate()
{
    Super::Activate();
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
    if(!SteamUGC())
    {
        OnFailure.Broadcast(ESIK_Result::ResultFail);
        SetReadyToDestroy();
        MarkAsGarbage();
        return;
    }
    PublishedFileId_t *pvecPublishedFileID = new PublishedFileId_t[Var_NumPublishedFileIDs];
    for (int32 i = 0; i < Var_NumPublishedFileIDs; i++)
    {
        pvecPublishedFileID[i] = Var_PublishedFileID[i].GetPublishedFileId();
    }
    CallbackHandle = SteamUGC()->StopPlaytimeTracking(pvecPublishedFileID, Var_NumPublishedFileIDs);
    if (CallbackHandle == k_uAPICallInvalid)
    {
        OnFailure.Broadcast(ESIK_Result::ResultFail);
        SetReadyToDestroy();
        MarkAsGarbage();
        return;
    }
    CallResult.Set(CallbackHandle, this, &USIK_StopPlaytimeTracking_AsyncFunction::OnComplete);
#else
    OnFailure.Broadcast(ESIK_Result::ResultFail);
    SetReadyToDestroy();
    MarkAsGarbage();
#endif
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
void USIK_StopPlaytimeTracking_AsyncFunction::OnComplete(StopPlaytimeTrackingResult_t *CallbackData, bool bIOFailure)
{
    auto Param = *CallbackData;
    AsyncTask(ENamedThreads::GameThread, [this, Param, bIOFailure]()
    {
        if (bIOFailure)
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
#endif