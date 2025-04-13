// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#include "SIK_AttachLeaderboardUGC_AsyncFunction.h"
#include "Async/Async.h"

USIK_AttachLeaderboardUGC_AsyncFunction* USIK_AttachLeaderboardUGC_AsyncFunction::AttachLeaderboardUGC(int32 LeaderboardId, int64 UGCHandle)
{
	USIK_AttachLeaderboardUGC_AsyncFunction* BlueprintNode = NewObject<USIK_AttachLeaderboardUGC_AsyncFunction>();
	BlueprintNode->Var_LeaderboardId = LeaderboardId;
	BlueprintNode->Var_UGCHandle = UGCHandle;
	return BlueprintNode;
}

void USIK_AttachLeaderboardUGC_AsyncFunction::Activate()
{
	Super::Activate();
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUserStats())
	{
		OnFailure.Broadcast();
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	
	CallbackHandle = SteamUserStats()->AttachLeaderboardUGC(Var_LeaderboardId, Var_UGCHandle);
	
	if(CallbackHandle == k_uAPICallInvalid)
	{
		OnFailure.Broadcast();
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	
	OnAttachLeaderboardUGCCallResult.Set(CallbackHandle, this, &USIK_AttachLeaderboardUGC_AsyncFunction::OnAttachLeaderboardUGC);
#else
	OnFailure.Broadcast();
	SetReadyToDestroy();
	MarkAsGarbage();
#endif
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
void USIK_AttachLeaderboardUGC_AsyncFunction::OnAttachLeaderboardUGC(LeaderboardUGCSet_t* LeaderboardUGCSet, bool bIOFailure)
{
	auto Param = *LeaderboardUGCSet;
	AsyncTask(ENamedThreads::GameThread, [this, Param, bIOFailure]()
	{
		if(bIOFailure || Param.m_eResult != k_EResultOK)
		{
			OnFailure.Broadcast();
			SetReadyToDestroy();
			MarkAsGarbage();
			return;
		}
		
		OnSuccess.Broadcast();
	});
	
	SetReadyToDestroy();
	MarkAsGarbage();
}
#endif