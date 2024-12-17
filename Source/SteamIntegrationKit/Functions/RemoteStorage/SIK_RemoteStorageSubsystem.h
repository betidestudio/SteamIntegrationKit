// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SIK_SharedFile.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Async/Async.h"
#include "SIK_RemoteStorageSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnRemoteStorageDownloadUGCResult, TEnumAsByte<ESIK_Result>, Result, FSIK_UGCHandle, UGCHandle, int32, AppID, FString, FileName, int32, Size, FSIK_SteamId, SteamIDOwner);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnRemoteStorageFileShareResult, TEnumAsByte<ESIK_Result>, Result, FSIK_UGCHandle, FileHandle, FString, FileName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRemoteStorageFileWriteAsyncComplete, TEnumAsByte<ESIK_Result>, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRemoteStorageLocalFileChange);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRemoteStoragePublishedFileSubscribedComplete, FSIK_PublishedFileId, PublishedFileId, FSIK_AppId, AppID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRemoteStoragePublishedFileUnsubscribedComplete, FSIK_PublishedFileId, PublishedFileId, FSIK_AppId, AppID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRemoteStorageSubscribePublishedFileResult, FSIK_PublishedFileId, PublishedFileId, TEnumAsByte<ESIK_Result>, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRemoteStorageUnsubscribePublishedFileResult, FSIK_PublishedFileId, PublishedFileId, TEnumAsByte<ESIK_Result>, Result);
UCLASS(meta=(DisplayName="Remote Storage"))
class STEAMINTEGRATIONKIT_API USIK_RemoteStorageSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	USIK_RemoteStorageSubsystem();
	~USIK_RemoteStorageSubsystem();
	// Associated Functions: UGCDownload, UGCDownloadToLocation
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || Remote Storage")
	FOnRemoteStorageDownloadUGCResult OnRemoteStorageDownloadUGCResult;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || Remote Storage")
	FOnRemoteStorageFileShareResult OnRemoteStorageFileShareResult;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || Remote Storage")
	FOnRemoteStorageFileWriteAsyncComplete OnRemoteStorageFileWriteAsyncComplete;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || Remote Storage")
	FOnRemoteStoragePublishedFileSubscribedComplete OnRemoteStoragePublishedFileSubscribedComplete;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || Remote Storage")
	FOnRemoteStoragePublishedFileUnsubscribedComplete OnRemoteStoragePublishedFileUnsubscribedComplete;

	//Called when the user has subscribed to a piece of UGC. Result from ISteamUGC::SubscribeItem.
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || Remote Storage")
	FOnRemoteStorageSubscribePublishedFileResult OnRemoteStorageSubscribePublishedFileResult;

	//Called when the user has unsubscribed from a piece of UGC. Result from ISteamUGC::UnsubscribeItem.
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || Remote Storage")
	FOnRemoteStorageUnsubscribePublishedFileResult OnRemoteStorageUnsubscribePublishedFileResult;
	
	/*
	*If a Steam app is flagged for supporting dynamic Steam Cloud sync, and a sync occurs, this callback will be posted to the app if any local files changed.
	*
	*Associated Functions: GetLocalFileChangeCount, GetLocalFileChange
	*/
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || Remote Storage")
	FOnRemoteStorageLocalFileChange OnRemoteStorageLocalFileChange;

private:
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	STEAM_CALLBACK_MANUAL(USIK_RemoteStorageSubsystem, RemoteStorageDownloadUGCResutCallbck, RemoteStorageDownloadUGCResult_t, m_CallbackUGCDownloadResult);
	STEAM_CALLBACK_MANUAL(USIK_RemoteStorageSubsystem, RemoteStorageFileShareResultCallback, RemoteStorageFileShareResult_t, m_CallbackFileShareResult);
	STEAM_CALLBACK_MANUAL(USIK_RemoteStorageSubsystem, RemoteStorageFileWriteAsyncCompleteCallback, RemoteStorageFileWriteAsyncComplete_t, m_CallbackFileWriteAsyncComplete);
	STEAM_CALLBACK_MANUAL(USIK_RemoteStorageSubsystem, RemoteStorageLocalFileChangeCallback, RemoteStorageLocalFileChange_t, m_CallbackLocalFileChange);
	STEAM_CALLBACK_MANUAL(USIK_RemoteStorageSubsystem, RemoteStoragePublishedFileSubscribedCompleteCallback, RemoteStoragePublishedFileSubscribed_t, m_CallbackPublishedFileSubscribedComplete);
	STEAM_CALLBACK_MANUAL(USIK_RemoteStorageSubsystem, RemoteStoragePublishedFileUnsubscribedCompleteCallback, RemoteStoragePublishedFileUnsubscribed_t, m_CallbackPublishedFileUnsubscribedComplete);
	STEAM_CALLBACK_MANUAL(USIK_RemoteStorageSubsystem, RemoteStorageSubscribePublishedFileResultCallback, RemoteStorageSubscribePublishedFileResult_t, m_CallbackSubscribePublishedFileResult);
	STEAM_CALLBACK_MANUAL(USIK_RemoteStorageSubsystem, RemoteStorageUnsubscribePublishedFileResultCallback, RemoteStorageUnsubscribePublishedFileResult_t, m_CallbackUnsubscribePublishedFileResult);
#endif
};