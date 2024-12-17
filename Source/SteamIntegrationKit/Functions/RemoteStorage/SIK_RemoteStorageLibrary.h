// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SIK_SharedFile.h"
#include "SIK_RemoteStorageLibrary.generated.h"

/**
 * 
 */
UCLASS()
class STEAMINTEGRATIONKIT_API USIK_RemoteStorageLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Remote Storage")
	static bool BeginFileWriteBatch();
	
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Remote Storage")
	static bool EndFileWriteBatch();

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Remote Storage")
	static bool FileDelete(const FString& FileName);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Remote Storage")
	static bool FileExists(const FString& FileName);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Remote Storage")
	static bool FileForget(const FString& FileName);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Remote Storage")
	static bool FilePersisted(const FString& FileName);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Remote Storage")
	static int32 FileRead(const FString& FileName, TArray<uint8>& Data);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Remote Storage")
	static bool FileWrite(const FString& FileName, const TArray<uint8>& Data);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Remote Storage")
	static bool FileWriteStreamCancel(FSIK_UGCFileWriteStreamHandle WriteStreamHandle);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Remote Storage")
	static bool FileWriteStreamClose(FSIK_UGCFileWriteStreamHandle WriteStreamHandle);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Remote Storage")
	static FSIK_UGCFileWriteStreamHandle FileWriteStreamOpen(const FString& FileName);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Remote Storage")
	static bool FileWriteStreamWriteChunk(FSIK_UGCFileWriteStreamHandle WriteStreamHandle, const TArray<uint8>& Data);
	
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Remote Storage")
	static int32 GetCachedUGCCount();

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Remote Storage")
	static FSIK_UGCHandle GetCachedUGCHandle(int32 CachedContent);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Remote Storage")
	static int32 GetFileCount();
	
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Remote Storage")
	static FString GetFileNameAndSize(int32 File, int32& FileSize);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Remote Storage")
	static int32 GetFileSize(const FString& FileName);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Remote Storage")
	static FDateTime GetFileTimestamp(const FString& FileName, int64& Timestamp);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Remote Storage")
	static int32 GetLocalFileChangeCount();

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Remote Storage")
	static FString GetLocalFileChange(int32 File, TEnumAsByte<ESIK_RemoteStorageLocalFileChange>& ChangeType, TEnumAsByte<ESIK_RemoteStorageFilePathType>& PathType);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Remote Storage")
	static bool GetQuota(int64& TotalBytes, int64& AvailableBytes);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Remote Storage")
	static TEnumAsByte<ESIK_RemoteStoragePlatform> GetSyncPlatforms(const FString& FileName);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Remote Storage")
	static bool GetUGCDetails(FSIK_UGCHandle UGCHandle, FString& FileName, int32& FileSize, FSIK_SteamId& OwnerID);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Remote Storage")
	static bool GetUGCDownloadProgress(FSIK_UGCHandle UGCHandle, int32& BytesDownloaded, int32& BytesExpected);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Remote Storage")
	static bool IsCloudEnabledForAccount();

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Remote Storage")
	static bool IsCloudEnabledForApp();

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Remote Storage")
	static void SetCloudEnabledForApp(bool bEnabled);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Remote Storage")
	static bool SetSyncPlatforms(const FString& FileName, ESIK_RemoteStoragePlatform RemoteStoragePlatform);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Remote Storage")
	static int32 UGCRead(const FSIK_UGCHandle UGCHandle, TArray<uint8>& Data, int32 DataToRead, int32 Offset,TEnumAsByte<ESIK_UGCReadAction> Action);
	
};
