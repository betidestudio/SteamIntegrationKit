
#include "SIK_AddItemToFavorites_AsyncFunction.h"

#include "Async/Async.h"

USIK_AddItemToFavorites_AsyncFunction* USIK_AddItemToFavorites_AsyncFunction::AddItemToFavorites(FSIK_AppId AppId, FSIK_PublishedFileId PublishedFileId)
{
    USIK_AddItemToFavorites_AsyncFunction* Obj = NewObject<USIK_AddItemToFavorites_AsyncFunction>();
    Obj->Var_AppId = AppId;
    Obj->Var_PublishedFileId = PublishedFileId;
    return Obj;
}

void USIK_AddItemToFavorites_AsyncFunction::Activate()
{
    Super::Activate();
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
    if(!SteamUGC())
    {
        OnFailure.Broadcast(ESIK_Result::ResultFail, Var_PublishedFileId, false);
        SetReadyToDestroy();
        MarkAsGarbage();
        return;
    }
    CallbackHandle = SteamUGC()->AddItemToFavorites(Var_AppId.GetAppID(), Var_PublishedFileId.GetPublishedFileId());
    if(CallbackHandle == k_uAPICallInvalid)
    {
        OnFailure.Broadcast(ESIK_Result::ResultFail, Var_PublishedFileId, false);
        SetReadyToDestroy();
        MarkAsGarbage();
        return;
    }
    CallResult.Set(CallbackHandle, this, &USIK_AddItemToFavorites_AsyncFunction::OnComplete);
#else
    OnFailure.Broadcast(ESIK_Result::ResultFail, Var_PublishedFileId, false);
    SetReadyToDestroy();
    MarkAsGarbage();
#endif
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
void USIK_AddItemToFavorites_AsyncFunction::OnComplete(UserFavoriteItemsListChanged_t* pParam, bool bIOFailure)
{
    auto Param = *pParam;
    AsyncTask(ENamedThreads::GameThread, [this, Param, bIOFailure]()
    {
        if (bIOFailure)
        {
            OnFailure.Broadcast(ESIK_Result::ResultFail, Var_PublishedFileId, true);
        }
        else
        {
            ESIK_Result Result = static_cast<ESIK_Result>(Param.m_eResult);
            OnSuccess.Broadcast(Result, Var_PublishedFileId, Param.m_bWasAddRequest);
        }
    });
    SetReadyToDestroy();
    MarkAsGarbage();
}
#endif