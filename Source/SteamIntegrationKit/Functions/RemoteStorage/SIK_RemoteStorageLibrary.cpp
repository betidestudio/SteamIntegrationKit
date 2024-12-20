// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_RemoteStorageLibrary.h"

bool USIK_RemoteStorageLibrary::BeginFileWriteBatch()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamRemoteStorage())
	{
		return false;
	}
	return SteamRemoteStorage()->BeginFileWriteBatch();
#else
	return false;
#endif
}

bool USIK_RemoteStorageLibrary::EndFileWriteBatch()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamRemoteStorage())
	{
		return false;
	}
	return SteamRemoteStorage()->EndFileWriteBatch();
#else
	return false;
#endif
}

bool USIK_RemoteStorageLibrary::FileDelete(const FString& FileName)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamRemoteStorage())
	{
		return false;
	}
	return SteamRemoteStorage()->FileDelete(TCHAR_TO_ANSI(*FileName));
#else
	return false;
#endif
}

bool USIK_RemoteStorageLibrary::FileExists(const FString& FileName)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamRemoteStorage())
	{
		return false;
	}
	return SteamRemoteStorage()->FileExists(TCHAR_TO_ANSI(*FileName));
#else
	return false;
#endif
}

bool USIK_RemoteStorageLibrary::FileForget(const FString& FileName)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamRemoteStorage())
	{
		return false;
	}
	return SteamRemoteStorage()->FileForget(TCHAR_TO_ANSI(*FileName));
#else
	return false;
#endif
}

bool USIK_RemoteStorageLibrary::FilePersisted(const FString& FileName)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamRemoteStorage())
	{
		return false;
	}
	return SteamRemoteStorage()->FilePersisted(TCHAR_TO_ANSI(*FileName));
#else
	return false;
#endif
}

int32 USIK_RemoteStorageLibrary::FileRead(const FString& FileName, TArray<uint8>& Data)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamRemoteStorage())
	{
		return 0;
	}
	int32 DataSize = SteamRemoteStorage()->GetFileSize(TCHAR_TO_ANSI(*FileName));
	if(DataSize <= 0)
	{
		return 0;
	}
	Data.SetNumUninitialized(DataSize);
	return SteamRemoteStorage()->FileRead(TCHAR_TO_ANSI(*FileName), Data.GetData(), DataSize);
#else
	return 0;
#endif
}

bool USIK_RemoteStorageLibrary::FileWrite(const FString& FileName, const TArray<uint8>& Data)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamRemoteStorage())
	{
		return false;
	}
	return SteamRemoteStorage()->FileWrite(TCHAR_TO_ANSI(*FileName), Data.GetData(), Data.Num());
#else
	return false;
#endif
}

bool USIK_RemoteStorageLibrary::FileWriteStreamCancel(FSIK_UGCFileWriteStreamHandle WriteStreamHandle)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamRemoteStorage())
	{
		return false;
	}
	return SteamRemoteStorage()->FileWriteStreamCancel(WriteStreamHandle.GetUGCFileWriteStreamHandle());
#else
	return false;
#endif
}

bool USIK_RemoteStorageLibrary::FileWriteStreamClose(FSIK_UGCFileWriteStreamHandle WriteStreamHandle)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamRemoteStorage())
	{
		return false;
	}
	return SteamRemoteStorage()->FileWriteStreamClose(WriteStreamHandle.GetUGCFileWriteStreamHandle());
#else
	return false;
#endif
}

FSIK_UGCFileWriteStreamHandle USIK_RemoteStorageLibrary::FileWriteStreamOpen(const FString& FileName)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamRemoteStorage())
	{
		return FSIK_UGCFileWriteStreamHandle();
	}
	return FSIK_UGCFileWriteStreamHandle(SteamRemoteStorage()->FileWriteStreamOpen(TCHAR_TO_ANSI(*FileName)));
#else
	return FSIK_UGCFileWriteStreamHandle();
#endif
}

bool USIK_RemoteStorageLibrary::FileWriteStreamWriteChunk(FSIK_UGCFileWriteStreamHandle WriteStreamHandle,
	const TArray<uint8>& Data)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamRemoteStorage())
	{
		return false;
	}
	return SteamRemoteStorage()->FileWriteStreamWriteChunk(WriteStreamHandle.GetUGCFileWriteStreamHandle(), Data.GetData(), Data.Num());
#else
	return false;
#endif
}

int32 USIK_RemoteStorageLibrary::GetCachedUGCCount()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamRemoteStorage())
	{
		return 0;
	}
	return SteamRemoteStorage()->GetCachedUGCCount();
#else
	return 0;
#endif
}

FSIK_UGCHandle USIK_RemoteStorageLibrary::GetCachedUGCHandle(int32 CachedContent)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamRemoteStorage())
	{
		return FSIK_UGCHandle();
	}
	return FSIK_UGCHandle(SteamRemoteStorage()->GetCachedUGCHandle(CachedContent));
#else
	return FSIK_UGCHandle();
#endif
}

int32 USIK_RemoteStorageLibrary::GetFileCount()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamRemoteStorage())
	{
		return 0;
	}
	return SteamRemoteStorage()->GetFileCount();
#else
	return 0;
#endif
}

FString USIK_RemoteStorageLibrary::GetFileNameAndSize(int32 File, int32& FileSize)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamRemoteStorage())
	{
		return FString();
	}
	return UTF8_TO_TCHAR(SteamRemoteStorage()->GetFileNameAndSize(File, &FileSize));
#else
	return FString();
#endif
}

int32 USIK_RemoteStorageLibrary::GetFileSize(const FString& FileName)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamRemoteStorage())
	{
		return 0;
	}
	return SteamRemoteStorage()->GetFileSize(TCHAR_TO_ANSI(*FileName));
#else
	return 0;
#endif
}

FDateTime USIK_RemoteStorageLibrary::GetFileTimestamp(const FString& FileName, int64& Timestamp)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamRemoteStorage())
	{
		return FDateTime();
	}
	Timestamp = SteamRemoteStorage()->GetFileTimestamp(TCHAR_TO_ANSI(*FileName));
	return FDateTime::FromUnixTimestamp(Timestamp);
#else
	return FDateTime();
#endif
}

int32 USIK_RemoteStorageLibrary::GetLocalFileChangeCount()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamRemoteStorage())
	{
		return 0;
	}
	return SteamRemoteStorage()->GetLocalFileChangeCount();
#else
	return 0;
#endif
}

FString USIK_RemoteStorageLibrary::GetLocalFileChange(int32 File, TEnumAsByte<ESIK_RemoteStorageLocalFileChange>& ChangeType,
	TEnumAsByte<ESIK_RemoteStorageFilePathType>& PathType)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamRemoteStorage())
	{
		return FString();
	}
	ERemoteStorageLocalFileChange ChangeTypeLocal;
	ERemoteStorageFilePathType PathTypeLocal;
	auto Response = SteamRemoteStorage()->GetLocalFileChange(File, &ChangeTypeLocal, &PathTypeLocal);
	ChangeType = static_cast<ESIK_RemoteStorageLocalFileChange>(ChangeTypeLocal);
	PathType = static_cast<ESIK_RemoteStorageFilePathType>(PathTypeLocal);
	return Response;
#else
	return FString();
#endif
}

bool USIK_RemoteStorageLibrary::GetQuota(int64& TotalBytes, int64& AvailableBytes)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamRemoteStorage())
	{
		UE_LOG(LogTemp, Error, TEXT("Steam Remote Storage is not available"));
		return false;
	}
	uint64 TotalBytesLocal;
	uint64 AvailableBytesLocal;
	auto response = SteamRemoteStorage()->GetQuota(&TotalBytesLocal, &AvailableBytesLocal);
	UE_LOG(LogTemp, Log, TEXT("Total Bytes: %llu, Available Bytes: %llu"), TotalBytesLocal, AvailableBytesLocal);
	TotalBytes = TotalBytesLocal;
	AvailableBytes = AvailableBytesLocal;
	return response;
#else
	return false;
#endif
}

TEnumAsByte<ESIK_RemoteStoragePlatform> USIK_RemoteStorageLibrary::GetSyncPlatforms(const FString& FileName)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamRemoteStorage())
	{
		return ESIK_RemoteStoragePlatform::RemoteStoragePlatformNone;
	}
	return static_cast<ESIK_RemoteStoragePlatform>(SteamRemoteStorage()->GetSyncPlatforms(TCHAR_TO_ANSI(*FileName)));
#else
	return ESIK_RemoteStoragePlatform::RemoteStoragePlatformNone;
#endif
}

bool USIK_RemoteStorageLibrary::GetUGCDetails(FSIK_UGCHandle UGCHandle, FString& FileName, int32& FileSize,
	FSIK_SteamId& OwnerID)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamRemoteStorage())
	{
		return false;
	}
	char* FileNameLocal[1024];
	int32 *FileSizeLocal = 0;
	CSteamID OwnerIDLocal;
	AppId_t AppIDLocal;
	auto response = SteamRemoteStorage()->GetUGCDetails(UGCHandle.GetUGCHandle(),&AppIDLocal, FileNameLocal, FileSizeLocal, &OwnerIDLocal);
	FileName = FString(*FileNameLocal);
	FileSize = *FileSizeLocal;
	OwnerID = OwnerIDLocal;
	return response;
#else
	return false;
#endif
}

bool USIK_RemoteStorageLibrary::GetUGCDownloadProgress(FSIK_UGCHandle UGCHandle, int32& BytesDownloaded,
	int32& BytesExpected)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamRemoteStorage())
	{
		return false;
	}
	int32 BytesDownloadedLocal;
	int32 BytesExpectedLocal;
	auto response = SteamRemoteStorage()->GetUGCDownloadProgress(UGCHandle.GetUGCHandle(), &BytesDownloadedLocal, &BytesExpectedLocal);
	BytesDownloaded = BytesDownloadedLocal;
	BytesExpected = BytesExpectedLocal;
	return response;
#else
	return false;
#endif
}

bool USIK_RemoteStorageLibrary::IsCloudEnabledForAccount()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamRemoteStorage())
	{
		return false;
	}
	return SteamRemoteStorage()->IsCloudEnabledForAccount();
#else
	return false;
#endif
}

bool USIK_RemoteStorageLibrary::IsCloudEnabledForApp()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamRemoteStorage())
	{
		return false;
	}
	return SteamRemoteStorage()->IsCloudEnabledForApp();
#else
	return false;
#endif
}

void USIK_RemoteStorageLibrary::SetCloudEnabledForApp(bool bEnabled)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamRemoteStorage())
	{
		return;
	}
	SteamRemoteStorage()->SetCloudEnabledForApp(bEnabled);
#endif
}

bool USIK_RemoteStorageLibrary::SetSyncPlatforms(const FString& FileName,
	ESIK_RemoteStoragePlatform RemoteStoragePlatform)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamRemoteStorage())
	{
		return false;
	}
	return SteamRemoteStorage()->SetSyncPlatforms(TCHAR_TO_ANSI(*FileName), static_cast<ERemoteStoragePlatform>(RemoteStoragePlatform));
#else
	return false;
#endif
}

int32 USIK_RemoteStorageLibrary::UGCRead(const FSIK_UGCHandle UGCHandle, TArray<uint8>& Data, int32 DataToRead,
	int32 Offset,TEnumAsByte<ESIK_UGCReadAction> Action)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamRemoteStorage())
	{
		return 0;
	}
	Data.SetNumUninitialized(DataToRead);
	return SteamRemoteStorage()->UGCRead(UGCHandle.GetUGCHandle(), Data.GetData(), DataToRead, Offset, static_cast<EUGCReadAction>(Action.GetValue()));
#else
	return 0;
#endif
}
