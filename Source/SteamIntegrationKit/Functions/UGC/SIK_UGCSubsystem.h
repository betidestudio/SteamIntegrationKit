// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SIK_SharedFile.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SIK_UGCSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAddAppDependencyResult, TEnumAsByte<ESIK_Result>, Result, FSIK_PublishedFileId, PublishedFileId, FSIK_AppId, AppId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAddUGCDependencyResult, TEnumAsByte<ESIK_Result>, Result, FSIK_PublishedFileId, PublishedFileId, FSIK_PublishedFileId, ChildPublishedFileId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCreateItemResult, TEnumAsByte<ESIK_Result>, Result, FSIK_PublishedFileId, PublishedFileId, bool, UserNeedsToAcceptWorkshopLegalAgreement);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnDownloadItemResult, TEnumAsByte<ESIK_Result>, Result, FSIK_PublishedFileId, PublishedFileId, FSIK_AppId, AppId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnGetAppDependenciesResult, TEnumAsByte<ESIK_Result>, Result, FSIK_PublishedFileId, PublishedFileId, TArray<FSIK_AppId>, AppDependencies, int32, NumAppDependencies, int32, TotalNumAppDependencies);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDeleteItemResult, TEnumAsByte<ESIK_Result>, Result, FSIK_PublishedFileId, PublishedFileId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnGetUserItemVoteResult, TEnumAsByte<ESIK_Result>, Result, FSIK_PublishedFileId, PublishedFileId, bool, VotedUp, bool, VotedDown, bool, VotedSkipper);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemInstalled, FSIK_PublishedFileId, PublishedFileId, FSIK_AppId, AppId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnRemoveAppDependencyResult, TEnumAsByte<ESIK_Result>, Result, FSIK_PublishedFileId, PublishedFileId, FSIK_AppId, AppId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnRemoveUGCDependencyResult, TEnumAsByte<ESIK_Result>, Result, FSIK_PublishedFileId, PublishedFileId, FSIK_PublishedFileId, ChildPublishedFileId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnSetUserItemVoteResult, TEnumAsByte<ESIK_Result>, Result, FSIK_PublishedFileId, PublishedFileId, bool, VotedUp);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStartPlaytimeTrackingResult, TEnumAsByte<ESIK_Result>, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnSteamUGCQueryCompleted, TEnumAsByte<ESIK_Result>, Result, FSIK_UGCQueryHandle, UGCQueryHandle, int32, NumResultsReturned, int32, TotalMatchingResults, bool, bCachedData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStopPlaytimeTrackingResult, TEnumAsByte<ESIK_Result>, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnSubmitItemUpdateResult, TEnumAsByte<ESIK_Result>, Result, FSIK_PublishedFileId, PublishedFileId, bool, bUserNeedsToAcceptWorkshopLegalAgreement);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnUserFavoriteItemsListChanged, FSIK_PublishedFileId, PublishedFileId, bool, bWasAddRequest, TEnumAsByte<ESIK_Result>, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUserSubscribedItemsListChanged, FSIK_AppId, AppId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnWorkshopEULAStatus, TEnumAsByte<ESIK_Result>, Result, FSIK_AppId, AppId, int32, Version, int32, ActionTime, bool, bAccepted, bool, bNeedsToAccept);


UCLASS()
class STEAMINTEGRATIONKIT_API USIK_UGCSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	USIK_UGCSubsystem();
	~USIK_UGCSubsystem();
	
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || UGC")
	FOnAddAppDependencyResult OnAddAppDependencyResult;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || UGC")
	FOnAddUGCDependencyResult OnAddUGCDependencyResult;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || UGC")
	FOnCreateItemResult OnCreateItemResult;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || UGC")
	FOnDownloadItemResult OnDownloadItemResult;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || UGC")
	FOnGetAppDependenciesResult OnGetAppDependenciesResult;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || UGC")
	FOnDeleteItemResult OnDeleteItemResult;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || UGC")
	FOnGetUserItemVoteResult OnGetUserItemVoteResult;
	
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || UGC")
	FOnItemInstalled OnItemInstalled;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || UGC")
	FOnRemoveAppDependencyResult OnRemoveAppDependencyResult;
	
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || UGC")
	FOnRemoveUGCDependencyResult OnRemoveUGCDependencyResult;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || UGC")
	FOnSetUserItemVoteResult OnSetUserItemVoteResult;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || UGC")
	FOnStartPlaytimeTrackingResult OnStartPlaytimeTrackingResult;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || UGC")
	FOnSteamUGCQueryCompleted OnSteamUGCQueryCompleted;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || UGC")
	FOnStopPlaytimeTrackingResult OnStopPlaytimeTrackingResult;
	
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || UGC")
	FOnSubmitItemUpdateResult OnSubmitItemUpdateResult;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || UGC")
	FOnUserFavoriteItemsListChanged OnUserFavoriteItemsListChanged;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || UGC")
	FOnUserSubscribedItemsListChanged OnUserSubscribedItemsListChanged;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || UGC")
	FOnWorkshopEULAStatus OnWorkshopEULAStatus;
private:
	
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	STEAM_CALLBACK_MANUAL(USIK_UGCSubsystem, OnAddAppDependencyResultCallback, AddAppDependencyResult_t, m_CallbackAddAppDependencyResult);
	STEAM_CALLBACK_MANUAL(USIK_UGCSubsystem, OnAddUGCDependencyResultCallback, AddUGCDependencyResult_t, m_CallbackAddUGCDependencyResult);
	STEAM_CALLBACK_MANUAL(USIK_UGCSubsystem, OnCreateItemResultCallback, CreateItemResult_t, m_CallbackCreateItemResult);
	STEAM_CALLBACK_MANUAL(USIK_UGCSubsystem, OnDownloadItemResultCallback, DownloadItemResult_t, m_CallbackDownloadItemResult);
	STEAM_CALLBACK_MANUAL(USIK_UGCSubsystem, OnGetAppDependenciesResultCallback, GetAppDependenciesResult_t, m_CallbackGetAppDependenciesResult);
	STEAM_CALLBACK_MANUAL(USIK_UGCSubsystem, OnDeleteItemResultCallback, DeleteItemResult_t, m_CallbackDeleteItemResult);
	STEAM_CALLBACK_MANUAL(USIK_UGCSubsystem, OnGetUserItemVoteResultCallback, GetUserItemVoteResult_t, m_CallbackGetUserItemVoteResult);
	STEAM_CALLBACK_MANUAL(USIK_UGCSubsystem, OnItemInstalledCallback, ItemInstalled_t, m_CallbackItemInstalled);
	STEAM_CALLBACK_MANUAL(USIK_UGCSubsystem, OnRemoveAppDependencyResultCallback, RemoveAppDependencyResult_t, m_CallbackRemoveAppDependencyResult);
	STEAM_CALLBACK_MANUAL(USIK_UGCSubsystem, OnRemoveUGCDependencyResultCallback, RemoveUGCDependencyResult_t, m_CallbackRemoveUGCDependencyResult);
	STEAM_CALLBACK_MANUAL(USIK_UGCSubsystem, OnSetUserItemVoteResultCallback, SetUserItemVoteResult_t, m_CallbackSetUserItemVoteResult);
	STEAM_CALLBACK_MANUAL(USIK_UGCSubsystem, OnStartPlaytimeTrackingResultCallback, StartPlaytimeTrackingResult_t, m_CallbackStartPlaytimeTrackingResult);
	STEAM_CALLBACK_MANUAL(USIK_UGCSubsystem, OnSteamUGCQueryCompletedCallback, SteamUGCQueryCompleted_t, m_CallbackSteamUGCQueryCompleted);
	STEAM_CALLBACK_MANUAL(USIK_UGCSubsystem, OnStopPlaytimeTrackingResultCallback, StopPlaytimeTrackingResult_t, m_CallbackStopPlaytimeTrackingResult);
	STEAM_CALLBACK_MANUAL(USIK_UGCSubsystem, OnSubmitItemUpdateResultCallback, SubmitItemUpdateResult_t, m_CallbackSubmitItemUpdateResult);
	STEAM_CALLBACK_MANUAL(USIK_UGCSubsystem, OnUserFavoriteItemsListChangedCallback, UserFavoriteItemsListChanged_t, m_CallbackUserFavoriteItemsListChanged);
	STEAM_CALLBACK_MANUAL(USIK_UGCSubsystem, OnUserSubscribedItemsListChangedCallback, UserSubscribedItemsListChanged_t, m_CallbackUserSubscribedItemsListChanged);
	STEAM_CALLBACK_MANUAL(USIK_UGCSubsystem, OnWorkshopEULAStatusCallback, WorkshopEULAStatus_t, m_CallbackWorkshopEULAStatus);
#endif
};
