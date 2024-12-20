
#include "SIK_RemoveItemFromFavorites_AsyncFunction.h"

#include "Async/Async.h"

USIK_RemoveItemFromFavorites_AsyncFunction* USIK_RemoveItemFromFavorites_AsyncFunction::RemoveItemFromFavorites(FSIK_AppId AppId, FSIK_PublishedFileId PublishedFileId)
{
    USIK_RemoveItemFromFavorites_AsyncFunction* Node = NewObject<USIK_RemoveItemFromFavorites_AsyncFunction>();
    Node->Var_AppId = AppId;
    Node->Var_PublishedFileId = PublishedFileId;
    return Node;
}

void USIK_RemoveItemFromFavorites_AsyncFunction::Activate()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
    if(!SteamUGC())
    {
        OnFailure.Broadcast(FSIK_PublishedFileId(), ESIK_Result::ResultFail, false);
        SetReadyToDestroy();
        return;
    }
    CallbackHandle = SteamUGC()->RemoveItemFromFavorites(Var_AppId.GetAppID(), Var_PublishedFileId.GetPublishedFileId());
    if(CallbackHandle == k_uAPICallInvalid)
    {
        OnFailure.Broadcast(FSIK_PublishedFileId(), ESIK_Result::ResultFail, false);
        SetReadyToDestroy();
        MarkAsGarbage();
        return;
    }
    CallResult.Set(CallbackHandle, this, &USIK_RemoveItemFromFavorites_AsyncFunction::OnComplete);
#else
    OnFailure.Broadcast(FSIK_PublishedFileId(), ESIK_Result::ResultFail, false);
    SetReadyToDestroy();
    MarkAsGarbage();
#endif
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
void USIK_RemoveItemFromFavorites_AsyncFunction::OnComplete(UserFavoriteItemsListChanged_t* pParam, bool bIOFailure)
{
    auto Param = *pParam;
    AsyncTask(ENamedThreads::GameThread, [this, Param, bIOFailure]()
    {
        if(bIOFailure)
        {
            OnFailure.Broadcast(FSIK_PublishedFileId(), ESIK_Result::ResultFail, false);
        }
        else
        {
            ESIK_Result Result = static_cast<ESIK_Result>(Param.m_eResult);
            OnSuccess.Broadcast(FSIK_PublishedFileId(Param.m_nPublishedFileId), Result, Param.m_bWasAddRequest);
        }
    });
    SetReadyToDestroy();
    MarkAsGarbage();
}
#endif