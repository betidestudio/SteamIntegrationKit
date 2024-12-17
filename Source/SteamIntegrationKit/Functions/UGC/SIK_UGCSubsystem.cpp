// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_UGCSubsystem.h"

#include "Async/Async.h"


USIK_UGCSubsystem::USIK_UGCSubsystem()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	m_CallbackAddAppDependencyResult.Register(this, &USIK_UGCSubsystem::OnAddAppDependencyResultCallback);
	m_CallbackAddUGCDependencyResult.Register(this, &USIK_UGCSubsystem::OnAddUGCDependencyResultCallback);
	m_CallbackCreateItemResult.Register(this, &USIK_UGCSubsystem::OnCreateItemResultCallback);
	m_CallbackDownloadItemResult.Register(this, &USIK_UGCSubsystem::OnDownloadItemResultCallback);
	m_CallbackGetAppDependenciesResult.Register(this, &USIK_UGCSubsystem::OnGetAppDependenciesResultCallback);
	m_CallbackDeleteItemResult.Register(this, &USIK_UGCSubsystem::OnDeleteItemResultCallback);
	m_CallbackGetUserItemVoteResult.Register(this, &USIK_UGCSubsystem::OnGetUserItemVoteResultCallback);
	m_CallbackItemInstalled.Register(this, &USIK_UGCSubsystem::OnItemInstalledCallback);
	m_CallbackRemoveAppDependencyResult.Register(this, &USIK_UGCSubsystem::OnRemoveAppDependencyResultCallback);
	m_CallbackRemoveUGCDependencyResult.Register(this, &USIK_UGCSubsystem::OnRemoveUGCDependencyResultCallback);
	m_CallbackSetUserItemVoteResult.Register(this, &USIK_UGCSubsystem::OnSetUserItemVoteResultCallback);
	m_CallbackStartPlaytimeTrackingResult.Register(this, &USIK_UGCSubsystem::OnStartPlaytimeTrackingResultCallback);
	m_CallbackStopPlaytimeTrackingResult.Register(this, &USIK_UGCSubsystem::OnStopPlaytimeTrackingResultCallback);
	m_CallbackSteamUGCQueryCompleted.Register(this, &USIK_UGCSubsystem::OnSteamUGCQueryCompletedCallback);
	m_CallbackSubmitItemUpdateResult.Register(this, &USIK_UGCSubsystem::OnSubmitItemUpdateResultCallback);
	m_CallbackUserFavoriteItemsListChanged.Register(this, &USIK_UGCSubsystem::OnUserFavoriteItemsListChangedCallback);
	m_CallbackUserSubscribedItemsListChanged.Register(this, &USIK_UGCSubsystem::OnUserSubscribedItemsListChangedCallback);
	m_CallbackWorkshopEULAStatus.Register(this, &USIK_UGCSubsystem::OnWorkshopEULAStatusCallback);

 	if(IsRunningDedicatedServer())
 	{
	m_CallbackAddAppDependencyResult.SetGameserverFlag();
	m_CallbackAddUGCDependencyResult.SetGameserverFlag();
	m_CallbackCreateItemResult.SetGameserverFlag();
	m_CallbackDownloadItemResult.SetGameserverFlag();
	m_CallbackGetAppDependenciesResult.SetGameserverFlag();
	m_CallbackDeleteItemResult.SetGameserverFlag();
	m_CallbackGetUserItemVoteResult.SetGameserverFlag();
	m_CallbackItemInstalled.SetGameserverFlag();
	m_CallbackRemoveAppDependencyResult.SetGameserverFlag();
	m_CallbackRemoveUGCDependencyResult.SetGameserverFlag();
	m_CallbackSetUserItemVoteResult.SetGameserverFlag();
	m_CallbackStartPlaytimeTrackingResult.SetGameserverFlag();
	m_CallbackStopPlaytimeTrackingResult.SetGameserverFlag();
	m_CallbackSteamUGCQueryCompleted.SetGameserverFlag();
	m_CallbackSubmitItemUpdateResult.SetGameserverFlag();
	m_CallbackUserFavoriteItemsListChanged.SetGameserverFlag();
	m_CallbackUserSubscribedItemsListChanged.SetGameserverFlag();
	m_CallbackWorkshopEULAStatus.SetGameserverFlag();
}
#endif
}

USIK_UGCSubsystem::~USIK_UGCSubsystem()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	m_CallbackAddAppDependencyResult.Unregister();
	m_CallbackAddUGCDependencyResult.Unregister();
	m_CallbackCreateItemResult.Unregister();
	m_CallbackDownloadItemResult.Unregister();
	m_CallbackGetAppDependenciesResult.Unregister();
	m_CallbackDeleteItemResult.Unregister();
	m_CallbackGetUserItemVoteResult.Unregister();
	m_CallbackItemInstalled.Unregister();
	m_CallbackRemoveAppDependencyResult.Unregister();
	m_CallbackRemoveUGCDependencyResult.Unregister();
	m_CallbackSetUserItemVoteResult.Unregister();
	m_CallbackStartPlaytimeTrackingResult.Unregister();
	m_CallbackStopPlaytimeTrackingResult.Unregister();
	m_CallbackSteamUGCQueryCompleted.Unregister();
	m_CallbackSubmitItemUpdateResult.Unregister();
	m_CallbackUserFavoriteItemsListChanged.Unregister();
	m_CallbackUserSubscribedItemsListChanged.Unregister();
	m_CallbackWorkshopEULAStatus.Unregister();
#endif
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
void USIK_UGCSubsystem::OnAddAppDependencyResultCallback(AddAppDependencyResult_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnAddAppDependencyResult.Broadcast(static_cast<ESIK_Result>(Param.m_eResult), Param.m_nPublishedFileId, Param.m_nAppID);
	});
}

void USIK_UGCSubsystem::OnAddUGCDependencyResultCallback(AddUGCDependencyResult_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnAddUGCDependencyResult.Broadcast(static_cast<ESIK_Result>(Param.m_eResult), Param.m_nPublishedFileId, Param.m_nChildPublishedFileId);
	});
}

void USIK_UGCSubsystem::OnCreateItemResultCallback(CreateItemResult_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnCreateItemResult.Broadcast(static_cast<ESIK_Result>(Param.m_eResult), Param.m_nPublishedFileId, Param.m_bUserNeedsToAcceptWorkshopLegalAgreement);
	});
}

void USIK_UGCSubsystem::OnDownloadItemResultCallback(DownloadItemResult_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnDownloadItemResult.Broadcast(static_cast<ESIK_Result>(Param.m_eResult), Param.m_nPublishedFileId, Param.m_unAppID);
	});
}

void USIK_UGCSubsystem::OnGetAppDependenciesResultCallback(GetAppDependenciesResult_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		TArray<FSIK_AppId> AppDependencies;
		for (int32 i = 0; i < int32(Param.m_nNumAppDependencies); i++)
		{
			AppDependencies.Add(Param.m_rgAppIDs[i]);
		}

		OnGetAppDependenciesResult.Broadcast(static_cast<ESIK_Result>(Param.m_eResult), Param.m_nPublishedFileId, AppDependencies, Param.m_nNumAppDependencies, Param.m_nTotalNumAppDependencies);
	});
}

void USIK_UGCSubsystem::OnDeleteItemResultCallback(DeleteItemResult_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnDeleteItemResult.Broadcast(static_cast<ESIK_Result>(Param.m_eResult), Param.m_nPublishedFileId);
	});
}

void USIK_UGCSubsystem::OnGetUserItemVoteResultCallback(GetUserItemVoteResult_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnGetUserItemVoteResult.Broadcast(static_cast<ESIK_Result>(Param.m_eResult), Param.m_nPublishedFileId, Param.m_bVotedUp, Param.m_bVotedDown, Param.m_bVoteSkipped);
	});
}

void USIK_UGCSubsystem::OnItemInstalledCallback(ItemInstalled_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnItemInstalled.Broadcast(Param.m_unAppID, Param.m_nPublishedFileId);
	});
}

void USIK_UGCSubsystem::OnRemoveAppDependencyResultCallback(RemoveAppDependencyResult_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnRemoveAppDependencyResult.Broadcast(static_cast<ESIK_Result>(Param.m_eResult), Param.m_nPublishedFileId, Param.m_nAppID);
	});
}

void USIK_UGCSubsystem::OnRemoveUGCDependencyResultCallback(RemoveUGCDependencyResult_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnRemoveUGCDependencyResult.Broadcast(static_cast<ESIK_Result>(Param.m_eResult), Param.m_nPublishedFileId, Param.m_nChildPublishedFileId);
	});
}

void USIK_UGCSubsystem::OnSetUserItemVoteResultCallback(SetUserItemVoteResult_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnSetUserItemVoteResult.Broadcast(static_cast<ESIK_Result>(Param.m_eResult), Param.m_nPublishedFileId, Param.m_bVoteUp);
	});
}

void USIK_UGCSubsystem::OnStartPlaytimeTrackingResultCallback(StartPlaytimeTrackingResult_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnStartPlaytimeTrackingResult.Broadcast(static_cast<ESIK_Result>(Param.m_eResult));
	});
}

void USIK_UGCSubsystem::OnStopPlaytimeTrackingResultCallback(StopPlaytimeTrackingResult_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnStopPlaytimeTrackingResult.Broadcast(static_cast<ESIK_Result>(Param.m_eResult));
	});
}

void USIK_UGCSubsystem::OnSteamUGCQueryCompletedCallback(SteamUGCQueryCompleted_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnSteamUGCQueryCompleted.Broadcast(static_cast<ESIK_Result>(Param.m_eResult), Param.m_handle, Param.m_unNumResultsReturned, Param.m_unTotalMatchingResults, Param.m_bCachedData);
	});
}

void USIK_UGCSubsystem::OnSubmitItemUpdateResultCallback(SubmitItemUpdateResult_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnSubmitItemUpdateResult.Broadcast(static_cast<ESIK_Result>(Param.m_eResult), Param.m_nPublishedFileId, Param.m_bUserNeedsToAcceptWorkshopLegalAgreement);
	});
}

void USIK_UGCSubsystem::OnUserFavoriteItemsListChangedCallback(UserFavoriteItemsListChanged_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnUserFavoriteItemsListChanged.Broadcast(Param.m_nPublishedFileId, Param.m_bWasAddRequest, static_cast<ESIK_Result>(Param.m_eResult));
	});
}

void USIK_UGCSubsystem::OnUserSubscribedItemsListChangedCallback(UserSubscribedItemsListChanged_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnUserSubscribedItemsListChanged.Broadcast(Param.m_nAppID);
	});
}

void USIK_UGCSubsystem::OnWorkshopEULAStatusCallback(WorkshopEULAStatus_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnWorkshopEULAStatus.Broadcast(static_cast<ESIK_Result>(Param.m_eResult), Param.m_nAppID, Param.m_unVersion, Param.m_rtAction, Param.m_bAccepted, Param.m_bNeedsAction);
	});
}
#endif