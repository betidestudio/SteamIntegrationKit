
#include "SIK_StartPlaytimeTracking_AsyncFunction.h"

#include "Async/Async.h"

USIK_StartPlaytimeTracking_AsyncFunction* USIK_StartPlaytimeTracking_AsyncFunction::StartPlaytimeTracking(TArray<FSIK_PublishedFileId> PublishedFileID, int32 NumPublishedFileIDs)
{
    USIK_StartPlaytimeTracking_AsyncFunction* Node = NewObject<USIK_StartPlaytimeTracking_AsyncFunction>();
    Node->Var_PublishedFileID = PublishedFileID;
    Node->Var_NumPublishedFileIDs = NumPublishedFileIDs;
    return Node;
}

void USIK_StartPlaytimeTracking_AsyncFunction::Activate()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
    if(!SteamUGC())
    {
        OnFailure.Broadcast(ESIK_Result::ResultFail);
        SetReadyToDestroy();
        MarkAsGarbage();
        return;
    }
    PublishedFileId_t *PublishedFileID = new PublishedFileId_t[Var_PublishedFileID.Num()];
    for(int i = 0; i < Var_PublishedFileID.Num(); i++)
    {
        PublishedFileID[i] = Var_PublishedFileID[i].GetPublishedFileId();
    }
    CallbackHandle = SteamUGC()->StartPlaytimeTracking(PublishedFileID, Var_NumPublishedFileIDs);
    if(CallbackHandle == k_uAPICallInvalid)
    {
        OnFailure.Broadcast(ESIK_Result::ResultFail);
        SetReadyToDestroy();
        MarkAsGarbage();
        return;
    }
    CallResult.Set(CallbackHandle, this, &USIK_StartPlaytimeTracking_AsyncFunction::OnComplete);
#else
    OnFailure.Broadcast(ESIK_Result::ResultFail);
    SetReadyToDestroy();
    MarkAsGarbage();
#endif
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
void USIK_StartPlaytimeTracking_AsyncFunction::OnComplete(StartPlaytimeTrackingResult_t* CallbackData, bool bIOFailure)
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
#endif