// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_FileShare_AsyncFunction.h"

#include "Async/Async.h"

USIK_FileShare_AsyncFunction* USIK_FileShare_AsyncFunction::FileShareAsync(const FString& FileName)
{
	USIK_FileShare_AsyncFunction* Node = NewObject<USIK_FileShare_AsyncFunction>();
	Node->Var_FileName = FileName;
	return Node;
}

void USIK_FileShare_AsyncFunction::OnFileShare(RemoteStorageFileShareResult_t* RemoteStorageFileShareResult,
                                               bool bIOFailure)
{
	auto Param = *RemoteStorageFileShareResult;
	AsyncTask(ENamedThreads::GameThread, [this, Param, bIOFailure]()
	{
        if(bIOFailure)
        {
            OnFailure.Broadcast(static_cast<ESIK_Result>(-1), TEXT(""), FSIK_UGCHandle());
        }
        else
        {
            TEnumAsByte<ESIK_Result> Result = static_cast<ESIK_Result>(Param.m_eResult);
            FString SharedFile = UTF8_TO_TCHAR(Param.m_rgchFilename);
            FSIK_UGCHandle UGCHandle = FSIK_UGCHandle(Param.m_hFile);
            OnSuccess.Broadcast(Result, SharedFile, UGCHandle);
        }
    });
	SetReadyToDestroy();
	MarkAsGarbage();
}

void USIK_FileShare_AsyncFunction::Activate()
{
	Super::Activate();
	if(!SteamRemoteStorage())
	{
		OnFailure.Broadcast(static_cast<ESIK_Result>(-1), TEXT(""), FSIK_UGCHandle());
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	CallbackHandle = SteamRemoteStorage()->FileShare(TCHAR_TO_UTF8(*Var_FileName));
	if(CallbackHandle == k_uAPICallInvalid)
	{
		OnFailure.Broadcast(static_cast<ESIK_Result>(-1), TEXT(""), FSIK_UGCHandle());
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	OnFileShareCallResult.Set(CallbackHandle, this, &USIK_FileShare_AsyncFunction::OnFileShare);
}
