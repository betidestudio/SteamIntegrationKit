
#include "SIK_CreateItem_AsyncFunction.h"

#include "Async/Async.h"

USIK_CreateItem_AsyncFunction* USIK_CreateItem_AsyncFunction::CreateItem(FSIK_AppId ConsumerAppId, ESIK_WorkshopFileType FileType)
{
    USIK_CreateItem_AsyncFunction* Obj = NewObject<USIK_CreateItem_AsyncFunction>();
    Obj->Var_ConsumerAppId = ConsumerAppId;
    Obj->Var_FileType = FileType;
    return Obj;
}

void USIK_CreateItem_AsyncFunction::Activate()
{
    Super::Activate();
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
    if(!SteamUGC())
    {
        OnFailure.Broadcast(ESIK_Result::ResultFail, FSIK_PublishedFileId(), false);
        SetReadyToDestroy();
        return;
    }
    CallbackHandle = SteamUGC()->CreateItem(Var_ConsumerAppId.GetAppID(), static_cast<EWorkshopFileType>(Var_FileType));
    if(CallbackHandle == k_uAPICallInvalid)
    {
        OnFailure.Broadcast(ESIK_Result::ResultFail, FSIK_PublishedFileId(), false);
        SetReadyToDestroy();
        MarkAsGarbage();
        return;
    }
    CallResult.Set(CallbackHandle, this, &USIK_CreateItem_AsyncFunction::OnComplete);
#else
    OnFailure.Broadcast(ESIK_Result::ResultFail, FSIK_PublishedFileId(), false);
    SetReadyToDestroy();
    MarkAsGarbage();
#endif
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
void USIK_CreateItem_AsyncFunction::OnComplete(CreateItemResult_t* pResult, bool bIOFailure)
{
    auto Param = *pResult;
    AsyncTask(ENamedThreads::GameThread, [this, Param, bIOFailure]()
    {
        if (bIOFailure)
        {
            OnFailure.Broadcast(ESIK_Result::ResultFail, FSIK_PublishedFileId(), false);
        }
        else
        {
            ESIK_Result Result = static_cast<ESIK_Result>(Param.m_eResult);
            OnSuccess.Broadcast(Result, Param.m_nPublishedFileId, Param.m_bUserNeedsToAcceptWorkshopLegalAgreement);
        }
    });
    SetReadyToDestroy();
    MarkAsGarbage();
}
#endif