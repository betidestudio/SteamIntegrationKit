// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_UGCDownloadToLocation_AsyncFunction.h"

#include "Async/Async.h"

USIK_UGCDownloadToLocation_AsyncFunction* USIK_UGCDownloadToLocation_AsyncFunction::UGCDownloadToLocation(FSIK_UGCHandle UGCHandle, const FString& Location, int32 Priority)
{
	USIK_UGCDownloadToLocation_AsyncFunction* Node = NewObject<USIK_UGCDownloadToLocation_AsyncFunction>();
	Node->Var_UGCHandle = UGCHandle;
	Node->Var_Location = Location;
	Node->Var_Priority = Priority;
	return Node;
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
void USIK_UGCDownloadToLocation_AsyncFunction::OnUGCDownloadToLocation(RemoteStorageDownloadUGCResult_t* RemoteStorageDownloadUGCResult, bool bIOFailure)
{
	auto Param = *RemoteStorageDownloadUGCResult;
	AsyncTask(ENamedThreads::GameThread, [this, Param, bIOFailure]()
	{
		if(bIOFailure)
		{
			OnFailure.Broadcast(static_cast<ESIK_Result>(-1), FSIK_UGCHandle(), 0, FString(), 0, FSIK_SteamId());
		}
		else
		{
			TEnumAsByte<ESIK_Result> Result = static_cast<ESIK_Result>(Param.m_eResult);
			FSIK_UGCHandle UGCHandle = FSIK_UGCHandle(Param.m_hFile);
			int32 AppID = Param.m_nAppID;
			FString FileName = UTF8_TO_TCHAR(Param.m_pchFileName);
			int32 Size = Param.m_nSizeInBytes;
			FSIK_SteamId SteamIDOwner = FSIK_SteamId(Param.m_ulSteamIDOwner);
			
			if(Result == ESIK_Result::ResultOK)
			{
				OnSuccess.Broadcast(Result, UGCHandle, AppID, FileName, Size, SteamIDOwner);
			}
			else
			{
				OnFailure.Broadcast(Result, UGCHandle, AppID, FileName, Size, SteamIDOwner);
			}
		}
	});
	SetReadyToDestroy();
	MarkAsGarbage();
}
#endif

void USIK_UGCDownloadToLocation_AsyncFunction::Activate()
{
	Super::Activate();
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
	if(!SteamRemoteStorage())
	{
		OnFailure.Broadcast(static_cast<ESIK_Result>(-1), FSIK_UGCHandle(), 0, FString(), 0, FSIK_SteamId());
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	CallbackHandle = SteamRemoteStorage()->UGCDownloadToLocation(Var_UGCHandle.GetUGCHandle(), TCHAR_TO_UTF8(*Var_Location), Var_Priority);
	if(CallbackHandle == k_uAPICallInvalid)
	{
		OnFailure.Broadcast(static_cast<ESIK_Result>(-1), FSIK_UGCHandle(), 0, FString(), 0, FSIK_SteamId());
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	OnUGCDownloadToLocationCallResult.Set(CallbackHandle, this, &USIK_UGCDownloadToLocation_AsyncFunction::OnUGCDownloadToLocation);
#else
	OnFailure.Broadcast(static_cast<ESIK_Result>(-1), FSIK_UGCHandle(), 0, FString(), 0, FSIK_SteamId());
	SetReadyToDestroy();
	MarkAsGarbage();
#endif
}