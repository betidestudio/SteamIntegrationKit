
#include "SIK_SubmitItemUpdate_AsyncFunction.h"

#include "Async/Async.h"


USIK_SubmitItemUpdate_AsyncFunction* USIK_SubmitItemUpdate_AsyncFunction::SubmitItemUpdate(
    FSIK_UGCUpdateHandle UgcUpdateHandle, const FString& ChangeNote)
{
    USIK_SubmitItemUpdate_AsyncFunction* Obj = NewObject<USIK_SubmitItemUpdate_AsyncFunction>();
    Obj->Var_UgcUpdateHandle = UgcUpdateHandle;
    Obj->Var_ChangeNote = ChangeNote;
    return Obj;
}

void USIK_SubmitItemUpdate_AsyncFunction::Activate()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
    if(!SteamUGC())
    {
        OnFailure.Broadcast(ESIK_Result::ResultFail, false);
        SetReadyToDestroy();
        MarkAsGarbage();
        return;
    }
    CallbackHandle = SteamUGC()->SubmitItemUpdate(Var_UgcUpdateHandle.GetUGCUpdateHandle(), TCHAR_TO_ANSI(*Var_ChangeNote));
    if(CallbackHandle == k_uAPICallInvalid)
    {
        OnFailure.Broadcast(ESIK_Result::ResultFail, false);
        SetReadyToDestroy();
        MarkAsGarbage();
        return;
    }
    CallResult.Set(CallbackHandle, this, &USIK_SubmitItemUpdate_AsyncFunction::OnComplete);
#else
    OnFailure.Broadcast(ESIK_Result::ResultFail, false);
    SetReadyToDestroy();
    MarkAsGarbage();
#endif
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
void USIK_SubmitItemUpdate_AsyncFunction::OnComplete(SubmitItemUpdateResult_t* CallbackData, bool bIOFailure)
{
    auto Param = *CallbackData;
    AsyncTask(ENamedThreads::GameThread, [this, Param, bIOFailure]()
    {
        if(bIOFailure)
        {
            OnFailure.Broadcast(ESIK_Result::ResultFail, false);
        }
        else
        {
            OnSuccess.Broadcast(static_cast<ESIK_Result>(Param.m_eResult), Param.m_bUserNeedsToAcceptWorkshopLegalAgreement);
        }
    });
    SetReadyToDestroy();
    MarkAsGarbage();
}
#endif