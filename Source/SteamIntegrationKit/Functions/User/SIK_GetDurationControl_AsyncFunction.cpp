// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_GetDurationControl_AsyncFunction.h"

#include "Async/Async.h"

USIK_GetDurationControl_AsyncFunction* USIK_GetDurationControl_AsyncFunction::GetDurationControl()
{
	USIK_GetDurationControl_AsyncFunction* BlueprintNode = NewObject<USIK_GetDurationControl_AsyncFunction>();
	return BlueprintNode;
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
void USIK_GetDurationControl_AsyncFunction::OnDurationControl(DurationControl_t* DurationControl, bool bIOFailure)
{
	auto Param = *DurationControl;
	AsyncTask(ENamedThreads::GameThread, [this, Param, bIOFailure]()
	{
		if(bIOFailure)
		{
			OnFailure.Broadcast(ESIK_Result::ResultFail,ESIK_DurationControlNotification::DurationControlNotification_None,ESIK_DurationControlProgress::DurationControlProgress_Full,0,false,0);
		}
		else
		{
			TEnumAsByte<ESIK_DurationControlNotification> Notification = static_cast<ESIK_DurationControlNotification>(Param.m_notification);
			TEnumAsByte<ESIK_DurationControlProgress> Progress = static_cast<ESIK_DurationControlProgress>(Param.m_progress);
			TEnumAsByte<ESIK_Result> Result = static_cast<ESIK_Result>(Param.m_eResult);
			OnSuccess.Broadcast(Result,Notification,Progress,Param.m_csecsLast5h,Param.m_bApplicable,Param.m_appid);
		}
	});
	SetReadyToDestroy();
	MarkAsGarbage();
}
#endif

void USIK_GetDurationControl_AsyncFunction::Activate()
{
	Super::Activate();
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
	if(!SteamUser())
	{
		OnFailure.Broadcast(ESIK_Result::ResultBusy,ESIK_DurationControlNotification::DurationControlNotification_None,ESIK_DurationControlProgress::DurationControlProgress_Full,0,false,0);
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	m_SteamAPICall = SteamUser()->GetDurationControl();
	m_Callback.Set(m_SteamAPICall, this, &USIK_GetDurationControl_AsyncFunction::OnDurationControl);
#else
	OnFailure.Broadcast(ESIK_Result::ResultFail,ESIK_DurationControlNotification::DurationControlNotification_None,ESIK_DurationControlProgress::DurationControlProgress_Full,0,false,0);
	SetReadyToDestroy();
	MarkAsGarbage();
#endif
}
