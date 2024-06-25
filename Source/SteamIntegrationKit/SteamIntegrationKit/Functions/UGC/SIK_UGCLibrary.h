// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SIK_SharedFile.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SIK_UGCLibrary.generated.h"

/**
 * 
 */
UCLASS()
class STEAMINTEGRATIONKIT_API USIK_UGCLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool AddExcludedTag(FSIK_UGCQueryHandle QueryHandle, const FString& TagName);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool AddItemKeyValueTag(FSIK_UGCUpdateHandle UpdateHandle, const FString& Key, const FString& Value);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool AddItemPreviewFile(FSIK_UGCUpdateHandle UpdateHandle, const FString& PreviewFile, TEnumAsByte<ESIK_ItemPreviewType> FileType);
	
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool AddItemPreviewVideo(FSIK_UGCUpdateHandle UpdateHandle, const FString& VideoID);
	
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool AddRequiredKeyValueTag(FSIK_UGCUpdateHandle UpdateHandle, const FString& Key, const FString& Value);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool AddRequiredTag(FSIK_UGCQueryHandle QueryHandle, const FString& TagName);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool AddRequiredTagGroup(FSIK_UGCQueryHandle QueryHandle, const TArray<FString>& TagNames);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool BInitWorkshopForGameServer(FSIK_DepotId DepotId, const FString& Folder);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static FSIK_UGCQueryHandle CreateQueryAllUGCRequest(TEnumAsByte<ESIK_UGCQuery> QueryType, TEnumAsByte<ESIK_UGCMatchingUGCType> MatchingType, FSIK_AppId CreatorAppID, FSIK_AppId ConsumerAppID, int32 Page);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static FSIK_UGCQueryHandle CreateQueryUGCDetailsRequest(TArray<FSIK_PublishedFileId> PublishedFileIDs);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static FSIK_UGCQueryHandle CreateQueryUserUGCRequest(FSIK_AccountID AccountID, TEnumAsByte<ESIK_UserUGCList> ListType, TEnumAsByte<ESIK_UGCMatchingUGCType> MatchingType, TEnumAsByte<ESIK_UserUGCListSortOrder> SortOrder, FSIK_AppId CreatorAppID, FSIK_AppId ConsumerAppID, int32 Page);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool DownloadItem(FSIK_PublishedFileId PublishedFileId, bool bHighPriority);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool GetAppDependencies(FSIK_PublishedFileId PublishedFileId);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool GetItemDownloadInfo(FSIK_PublishedFileId PublishedFileId, int64& BytesDownloaded, int64& BytesTotal);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool GetItemInstallInfo(FSIK_PublishedFileId PublishedFileId, int64 &SizeOnDisk, FString &Folder, int32 &TimeStamp);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static int32 GetItemState(FSIK_PublishedFileId PublishedFileId);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static TEnumAsByte<ESIK_ItemUpdateStatus> GetItemUpdateProgress(FSIK_UGCUpdateHandle UpdateHandle, int64& BytesProcessed, int64& BytesTotal);
	
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static int32 GetNumSubscribedItems();

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool GetQueryUGCAdditionalPreview(FSIK_UGCQueryHandle QueryHandle,int32 Index, int32 PreviewIndex, FString& PreviewURL, FString& OriginalFileName, TEnumAsByte<ESIK_ItemPreviewType>& FileType);
	
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool GetQueryUGCChildren(FSIK_UGCQueryHandle QueryHandle, int32 Index, TArray<FSIK_PublishedFileId>& PublishedFileIDs, int32 MaxEntries);
	
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static int32 GetQueryUGCNumTags(FSIK_UGCQueryHandle QueryHandle, int32 Index);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool GetQueryUGCTag(FSIK_UGCQueryHandle QueryHandle, int32 Index, int32 TagIndex, FString& TagName);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool GetQueryUGCTagDisplayName(FSIK_UGCQueryHandle QueryHandle, int32 Index, int32 TagIndex, FString& TagName);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool GetQueryUGCKeyValueTag(FSIK_UGCQueryHandle QueryHandle, int32 Index, const FString& Key, FString& Value);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static int32 GetQueryUGCContentDescriptors(FSIK_UGCQueryHandle QueryHandle, int32 Index, TArray<TEnumAsByte<ESIK_UGCContentDescriptorID>>& ContentDescriptors, int32 MaxEntries);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool GetQueryUGCMetadata(FSIK_UGCQueryHandle QueryHandle, int32 Index, FString& Metadata);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static int32 GetQueryUGCNumAdditionalPreviews(FSIK_UGCQueryHandle QueryHandle, int32 Index);
	
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static int32 GetQueryUGCNumKeyValueTags(FSIK_UGCQueryHandle QueryHandle, int32 Index);
	
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool GetQueryUGCPreviewURL(FSIK_UGCQueryHandle QueryHandle, int32 Index, FString& URL);
	
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool GetQueryUGCResult(FSIK_UGCQueryHandle QueryHandle, int32 Index, FSIK_SteamUGCDetails& Details);
	
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool GetQueryUGCStatistic(FSIK_UGCQueryHandle QueryHandle, int32 Index, TEnumAsByte<ESIK_ItemStatistic> StatType, int64& Value);
	
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static int32 GetSubscribedItems(TArray<FSIK_PublishedFileId>& PublishedFileIDs, int32 MaxEntries);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool ReleaseQueryUGCRequest(FSIK_UGCQueryHandle QueryHandle);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool RemoveItemKeyValueTags(FSIK_UGCUpdateHandle UpdateHandle, const FString& Key);
	
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool RemoveItemPreview(FSIK_UGCUpdateHandle UpdateHandle, int32 PreviewIndex);
	
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool AddContentDescriptor(FSIK_UGCUpdateHandle UpdateHandle, TEnumAsByte<ESIK_UGCContentDescriptorID> ContentDescriptor);
	
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool RemoveContentDescriptor(FSIK_UGCUpdateHandle UpdateHandle, TEnumAsByte<ESIK_UGCContentDescriptorID> ContentDescriptor);
	
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool SetAllowCachedResponse(FSIK_UGCQueryHandle QueryHandle, int32 MaxAgeSeconds);
	
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool SetCloudFileNameFilter(FSIK_UGCQueryHandle QueryHandle, const FString& MatchCloudFileName);
	
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool SetItemContent(FSIK_UGCUpdateHandle UpdateHandle, const FString& Content);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool SetItemDescription(FSIK_UGCUpdateHandle UpdateHandle, const FString& Description);
	
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool SetItemMetadata(FSIK_UGCUpdateHandle UpdateHandle, const FString& Metadata);
	
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool SetItemPreview(FSIK_UGCUpdateHandle UpdateHandle, const FString& PreviewFile);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool SetItemTags(FSIK_UGCUpdateHandle UpdateHandle, const TArray<FString>& Tags);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool SetItemTitle(FSIK_UGCUpdateHandle UpdateHandle, const FString& Title);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool SetItemUpdateLanguage(FSIK_UGCUpdateHandle UpdateHandle, const FString& Language);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool SetItemVisibility(FSIK_UGCUpdateHandle UpdateHandle, TEnumAsByte<ESIK_RemoteStoragePublishedFileVisibility> Visibility);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool SetLanguage(FSIK_UGCQueryHandle QueryHandle, const FString& Language);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool SetMatchAnyTag(FSIK_UGCQueryHandle QueryHandle, bool bMatchAnyTag);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool SetRankedByTrendDays(FSIK_UGCQueryHandle QueryHandle, int32 Days);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool SetReturnAdditionalPreviews(FSIK_UGCQueryHandle QueryHandle, bool bReturnAdditionalPreviews);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool SetReturnChildren(FSIK_UGCQueryHandle QueryHandle, bool bReturnChildren);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool SetReturnKeyValueTags(FSIK_UGCQueryHandle QueryHandle, bool bReturnKeyValueTags);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool SetReturnLongDescription(FSIK_UGCQueryHandle QueryHandle, bool bReturnLongDescription);
	
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool SetReturnMetadata(FSIK_UGCQueryHandle QueryHandle, bool bReturnMetadata);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool SetReturnOnlyIDs(FSIK_UGCQueryHandle QueryHandle, bool bReturnOnlyIDs);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool SetReturnPlaytimeStats(FSIK_UGCQueryHandle QueryHandle, int32 Days);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool SetReturnTotalOnly(FSIK_UGCQueryHandle QueryHandle, bool bReturnTotalOnly);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool SetSearchText(FSIK_UGCQueryHandle QueryHandle, const FString& SearchText);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool SetUserItemVote(FSIK_PublishedFileId PublishedFileId, bool bVoteUp);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static FSIK_UGCUpdateHandle StartItemUpdate(FSIK_AppId AppID, FSIK_PublishedFileId PublishedFileID);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static void SuspendDownloads(bool bSuspend);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool UpdateItemPreviewFile(FSIK_UGCUpdateHandle UpdateHandle, int32 PreviewIndex, const FString& PreviewFile);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool UpdateItemPreviewVideo(FSIK_UGCUpdateHandle UpdateHandle, int32 PreviewIndex, const FString& VideoID);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | SDK Functions | UGC")
	static bool ShowWorkshopEULA();
	







	
};
