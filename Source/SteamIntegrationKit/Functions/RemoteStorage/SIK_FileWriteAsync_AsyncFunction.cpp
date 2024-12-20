// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_FileWriteAsync_AsyncFunction.h"

#include "Async/Async.h"

USIK_FileWriteAsync_AsyncFunction* USIK_FileWriteAsync_AsyncFunction::FileWriteAsync(const FString& FileName,
                                                                                     const TArray<uint8>& FileData)
{
	USIK_FileWriteAsync_AsyncFunction* Node = NewObject<USIK_FileWriteAsync_AsyncFunction>();
	Node->Var_FileName = FileName;
	Node->Var_FileData = FileData;
	return Node;
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
void USIK_FileWriteAsync_AsyncFunction::OnFileWriteAsyncComplete(RemoteStorageFileWriteAsyncComplete_t* RemoteStorageFileWriteAsyncComplete, bool bIOFailure)
{
	auto Param = *RemoteStorageFileWriteAsyncComplete;
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

void USIK_FileWriteAsync_AsyncFunction::Activate()
{
	Super::Activate();
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
	if(!SteamRemoteStorage() || Var_FileName.IsEmpty() || Var_FileData.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("File Write Async Invalid Parameters"));
		OnFailure.Broadcast(ESIK_Result::ResultFail);
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	UE_LOG(LogTemp, Log, TEXT("File Write Async Start with %s"), *Var_FileName);
	UE_LOG(LogTemp, Log, TEXT("File Write Async Start with %d"), Var_FileData.Num());
	CallbackHandle = SteamRemoteStorage()->FileWriteAsync(TCHAR_TO_UTF8(*Var_FileName), Var_FileData.GetData(), Var_FileData.Num());
	if(CallbackHandle == k_uAPICallInvalid)
	{
		UE_LOG(LogTemp, Error, TEXT("File Write Async Invalid Call Handle"));
		OnFailure.Broadcast(ESIK_Result::ResultFail);
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	OnFileWriteAsyncCallResult.Set(CallbackHandle, this, &USIK_FileWriteAsync_AsyncFunction::OnFileWriteAsyncComplete);
#else
	OnFailure.Broadcast(ESIK_Result::ResultFail);
	SetReadyToDestroy();
	MarkAsGarbage();
#endif
}
