// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_GetFileDetails_AsyncFunction.h"

#include "Async/Async.h"

USIK_GetFileDetails_AsyncFunction* USIK_GetFileDetails_AsyncFunction::GetFileDetails(const FString& FileName)
{
	USIK_GetFileDetails_AsyncFunction* Node = NewObject<USIK_GetFileDetails_AsyncFunction>();
	Node->m_FileName = FileName;
	return Node;
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
void USIK_GetFileDetails_AsyncFunction::OnGetFileDetails(FileDetailsResult_t* FileDetailsResult, bool bIOFailure)
{
	auto Param = *FileDetailsResult;
	AsyncTask(ENamedThreads::GameThread, [this, Param, bIOFailure]()
	{
		TEnumAsByte<ESIK_Result> Result = static_cast<ESIK_Result>(Param.m_eResult);
		if (bIOFailure)
		{
			OnFailure.Broadcast(Result, 0, TArray<int32>(), 0);
		}
		else
		{
			TArray<int32> FileHash;
			for (int i = 0; i < 20; i++)
			{
				FileHash.Add(Param.m_FileSHA[i]);
			}
			OnSuccess.Broadcast(Result, Param.m_ulFileSize, FileHash, Param.m_unFlags);
		}
	});
	SetReadyToDestroy();
	MarkAsGarbage();
}
#endif

void USIK_GetFileDetails_AsyncFunction::Activate()
{
	Super::Activate();
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if (!SteamApps())
	{
		OnFailure.Broadcast(ESIK_Result::ResultFail, 0, TArray<int32>(), 0);
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	m_CallbackHandle = SteamApps()->GetFileDetails(TCHAR_TO_UTF8(*m_FileName));
	if(m_CallbackHandle == k_uAPICallInvalid)
	{
		OnFailure.Broadcast(ESIK_Result::ResultFail, 0, TArray<int32>(), 0);
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	m_Callback.Set(m_CallbackHandle, this, &USIK_GetFileDetails_AsyncFunction::OnGetFileDetails);
#endif
}
