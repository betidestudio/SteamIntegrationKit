// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_FileReadAsync_AsyncFunction.h"

#include "Async/Async.h"

USIK_FileReadAsync_AsyncFunction* USIK_FileReadAsync_AsyncFunction::FileReadAsync(const FString& FileName,
                                                                                  int32 nOffset, int32 nBytesToRead)
{
	USIK_FileReadAsync_AsyncFunction* Node = NewObject<USIK_FileReadAsync_AsyncFunction>();
	Node->Var_FileName = FileName;
	Node->Var_nOffset = nOffset;
	Node->Var_nBytesToRead = nBytesToRead;
	return Node;
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
void USIK_FileReadAsync_AsyncFunction::OnFileReadAsync(RemoteStorageFileReadAsyncComplete_t* RemoteStorageFileReadAsyncComplete, bool bIOFailure)
{
	auto Param = *RemoteStorageFileReadAsyncComplete;
	AsyncTask(ENamedThreads::GameThread, [this, Param, bIOFailure]()
	{
		if(bIOFailure)
		{
			OnFailure.Broadcast(static_cast<ESIK_Result>(-1), 0, 0, {});
		}
		else
		{
			TEnumAsByte<ESIK_Result> Result = static_cast<ESIK_Result>(Param.m_eResult);
			int32 nOffset = Param.m_nOffset;
			int32 nBytesRead = Param.m_cubRead;
			auto Var_pData = new uint8[nBytesRead];
			if(Result == ESIK_Result::ResultOK)
			{
				SteamRemoteStorage()->FileReadAsyncComplete(Param.m_hFileReadAsync, Var_pData, nBytesRead);
			}
			OnSuccess.Broadcast(Result, nOffset, nBytesRead, {Var_pData, nBytesRead});
		}
	});
	SetReadyToDestroy();
	MarkAsGarbage();
}
#endif

void USIK_FileReadAsync_AsyncFunction::Activate()
{
	Super::Activate();
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
	if(!SteamRemoteStorage())
	{
		OnFailure.Broadcast(static_cast<ESIK_Result>(-1), 0, 0, {});
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	CallbackHandle = SteamRemoteStorage()->FileReadAsync(TCHAR_TO_UTF8(*Var_FileName), Var_nOffset, Var_nBytesToRead);
	if(CallbackHandle == k_uAPICallInvalid)
	{
		OnFailure.Broadcast(static_cast<ESIK_Result>(-1), 0, 0, {});
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	OnFileReadAsyncCallResult.Set(CallbackHandle, this, &USIK_FileReadAsync_AsyncFunction::OnFileReadAsync);
#else
	OnFailure.Broadcast(static_cast<ESIK_Result>(-1), 0, 0, {});
	SetReadyToDestroy();
	MarkAsGarbage();
#endif
}
