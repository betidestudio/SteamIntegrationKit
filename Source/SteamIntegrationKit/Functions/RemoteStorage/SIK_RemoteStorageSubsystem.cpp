// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#include "SIK_RemoteStorageSubsystem.h"


USIK_RemoteStorageSubsystem::USIK_RemoteStorageSubsystem()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	m_CallbackUGCDownloadResult.Register(this, &USIK_RemoteStorageSubsystem::RemoteStorageDownloadUGCResutCallbck);
	m_CallbackFileShareResult.Register(this, &USIK_RemoteStorageSubsystem::RemoteStorageFileShareResultCallback);
	m_CallbackFileWriteAsyncComplete.Register(this, &USIK_RemoteStorageSubsystem::RemoteStorageFileWriteAsyncCompleteCallback);
	m_CallbackLocalFileChange.Register(this, &USIK_RemoteStorageSubsystem::RemoteStorageLocalFileChangeCallback);
	m_CallbackPublishedFileSubscribedComplete.Register(this, &USIK_RemoteStorageSubsystem::RemoteStoragePublishedFileSubscribedCompleteCallback);
	m_CallbackPublishedFileUnsubscribedComplete.Register(this, &USIK_RemoteStorageSubsystem::RemoteStoragePublishedFileUnsubscribedCompleteCallback);

 	if(IsRunningDedicatedServer())
 	{
	m_CallbackUGCDownloadResult.SetGameserverFlag();
	m_CallbackFileShareResult.SetGameserverFlag();
	m_CallbackFileWriteAsyncComplete.SetGameserverFlag();
	m_CallbackLocalFileChange.SetGameserverFlag();
	m_CallbackPublishedFileSubscribedComplete.SetGameserverFlag();
	m_CallbackPublishedFileUnsubscribedComplete.SetGameserverFlag();
}
#endif

}

USIK_RemoteStorageSubsystem::~USIK_RemoteStorageSubsystem()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	m_CallbackUGCDownloadResult.Unregister();
	m_CallbackFileShareResult.Unregister();
	m_CallbackFileWriteAsyncComplete.Unregister();
	m_CallbackLocalFileChange.Unregister();
	m_CallbackPublishedFileSubscribedComplete.Unregister();
	m_CallbackPublishedFileUnsubscribedComplete.Unregister();
#endif
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
void USIK_RemoteStorageSubsystem::RemoteStorageDownloadUGCResutCallbck(RemoteStorageDownloadUGCResult_t* Callback)
{
	
	auto Param = *Callback;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnRemoteStorageDownloadUGCResult.Broadcast(static_cast<ESIK_Result>(Param.m_eResult), Param.m_hFile, Param.m_nAppID, FString(Param.m_pchFileName), Param.m_nSizeInBytes, Param.m_ulSteamIDOwner);
	});
}


void USIK_RemoteStorageSubsystem::RemoteStorageFileShareResultCallback(RemoteStorageFileShareResult_t* Callback)
{
	auto Param = *Callback;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnRemoteStorageFileShareResult.Broadcast(static_cast<ESIK_Result>(Param.m_eResult), Param.m_hFile, FString(Param.m_rgchFilename));
	});
}

void USIK_RemoteStorageSubsystem::RemoteStorageFileWriteAsyncCompleteCallback(RemoteStorageFileWriteAsyncComplete_t* Callback)
{
	auto Param = *Callback;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnRemoteStorageFileWriteAsyncComplete.Broadcast(static_cast<ESIK_Result>(Param.m_eResult));
	});
}

void USIK_RemoteStorageSubsystem::RemoteStorageLocalFileChangeCallback(RemoteStorageLocalFileChange_t* Callback)
{
	auto Param = *Callback;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnRemoteStorageLocalFileChange.Broadcast();
	});
}

void USIK_RemoteStorageSubsystem::RemoteStoragePublishedFileSubscribedCompleteCallback(RemoteStoragePublishedFileSubscribed_t* Callback)
{
	auto Param = *Callback;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnRemoteStoragePublishedFileSubscribedComplete.Broadcast(FSIK_PublishedFileId(Param.m_nPublishedFileId), FSIK_AppId(Param.m_nAppID));
	});
}

void USIK_RemoteStorageSubsystem::RemoteStoragePublishedFileUnsubscribedCompleteCallback(RemoteStoragePublishedFileUnsubscribed_t* Callback)
{
	auto Param = *Callback;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnRemoteStoragePublishedFileUnsubscribedComplete.Broadcast(FSIK_PublishedFileId(Param.m_nPublishedFileId), FSIK_AppId(Param.m_nAppID));
	});
}

void USIK_RemoteStorageSubsystem::RemoteStorageSubscribePublishedFileResultCallback(RemoteStorageSubscribePublishedFileResult_t* Callback)
{
	auto Param = *Callback;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnRemoteStorageSubscribePublishedFileResult.Broadcast(FSIK_PublishedFileId(Param.m_nPublishedFileId), static_cast<ESIK_Result>(Param.m_eResult));
	});
}

void USIK_RemoteStorageSubsystem::RemoteStorageUnsubscribePublishedFileResultCallback(RemoteStorageUnsubscribePublishedFileResult_t* Callback)
{
	auto Param = *Callback;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnRemoteStorageUnsubscribePublishedFileResult.Broadcast(FSIK_PublishedFileId(Param.m_nPublishedFileId), static_cast<ESIK_Result>(Param.m_eResult));
	});
}
#endif