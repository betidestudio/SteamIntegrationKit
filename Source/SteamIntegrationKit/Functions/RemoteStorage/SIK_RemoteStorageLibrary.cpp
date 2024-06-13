// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_RemoteStorageLibrary.h"

bool USIK_RemoteStorageLibrary::BeginFileWriteBatch()
{
	if(!SteamRemoteStorage())
	{
		return false;
	}
	return SteamRemoteStorage()->BeginFileWriteBatch();
}

bool USIK_RemoteStorageLibrary::EndFileWriteBatch()
{
	if(!SteamRemoteStorage())
	{
		return false;
	}
	return SteamRemoteStorage()->EndFileWriteBatch();
}

bool USIK_RemoteStorageLibrary::FileDelete(const FString& FileName)
{
	if(!SteamRemoteStorage())
	{
		return false;
	}
	return SteamRemoteStorage()->FileDelete(TCHAR_TO_ANSI(*FileName));
}

bool USIK_RemoteStorageLibrary::FileExists(const FString& FileName)
{
	if(!SteamRemoteStorage())
	{
		return false;
	}
	return SteamRemoteStorage()->FileExists(TCHAR_TO_ANSI(*FileName));
}

bool USIK_RemoteStorageLibrary::FileForget(const FString& FileName)
{
	if(!SteamRemoteStorage())
	{
		return false;
	}
	return SteamRemoteStorage()->FileForget(TCHAR_TO_ANSI(*FileName));
}

bool USIK_RemoteStorageLibrary::FilePersisted(const FString& FileName)
{
	if(!SteamRemoteStorage())
	{
		return false;
	}
	return SteamRemoteStorage()->FilePersisted(TCHAR_TO_ANSI(*FileName));
}

int32 USIK_RemoteStorageLibrary::FileRead(const FString& FileName, TArray<uint8>& Data)
{
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
}

bool USIK_RemoteStorageLibrary::FileWrite(const FString& FileName, const TArray<uint8>& Data)
{
	if(!SteamRemoteStorage())
	{
		return false;
	}
	return SteamRemoteStorage()->FileWrite(TCHAR_TO_ANSI(*FileName), Data.GetData(), Data.Num());
}

bool USIK_RemoteStorageLibrary::FileWriteStreamCancel(FSIK_UGCFileWriteStreamHandle WriteStreamHandle)
{
	if(!SteamRemoteStorage())
	{
		return false;
	}
	return SteamRemoteStorage()->FileWriteStreamCancel(WriteStreamHandle.GetUGCFileWriteStreamHandle());
}

bool USIK_RemoteStorageLibrary::FileWriteStreamClose(FSIK_UGCFileWriteStreamHandle WriteStreamHandle)
{
	if(!SteamRemoteStorage())
	{
		return false;
	}
	return SteamRemoteStorage()->FileWriteStreamClose(WriteStreamHandle.GetUGCFileWriteStreamHandle());
}

FSIK_UGCFileWriteStreamHandle USIK_RemoteStorageLibrary::FileWriteStreamOpen(const FString& FileName)
{
	if(!SteamRemoteStorage())
	{
		return FSIK_UGCFileWriteStreamHandle();
	}
	return FSIK_UGCFileWriteStreamHandle(SteamRemoteStorage()->FileWriteStreamOpen(TCHAR_TO_ANSI(*FileName)));
}

bool USIK_RemoteStorageLibrary::FileWriteStreamWriteChunk(FSIK_UGCFileWriteStreamHandle WriteStreamHandle,
	const TArray<uint8>& Data)
{
	if(!SteamRemoteStorage())
	{
		return false;
	}
	return SteamRemoteStorage()->FileWriteStreamWriteChunk(WriteStreamHandle.GetUGCFileWriteStreamHandle(), Data.GetData(), Data.Num());
}

int32 USIK_RemoteStorageLibrary::GetCachedUGCCount()
{
	if(!SteamRemoteStorage())
	{
		return 0;
	}
	return SteamRemoteStorage()->GetCachedUGCCount();
}

FSIK_UGCHandle USIK_RemoteStorageLibrary::GetCachedUGCHandle(int32 CachedContent)
{
	if(!SteamRemoteStorage())
	{
		return FSIK_UGCHandle();
	}
	return FSIK_UGCHandle(SteamRemoteStorage()->GetCachedUGCHandle(CachedContent));
}

int32 USIK_RemoteStorageLibrary::GetFileCount()
{
	if(!SteamRemoteStorage())
	{
		return 0;
	}
	return SteamRemoteStorage()->GetFileCount();
}

FString USIK_RemoteStorageLibrary::GetFileNameAndSize(int32 File, int32& FileSize)
{
	if(!SteamRemoteStorage())
	{
		return FString();
	}
	return UTF8_TO_TCHAR(SteamRemoteStorage()->GetFileNameAndSize(File, &FileSize));
}

int32 USIK_RemoteStorageLibrary::GetFileSize(const FString& FileName)
{
	if(!SteamRemoteStorage())
	{
		return 0;
	}
	return SteamRemoteStorage()->GetFileSize(TCHAR_TO_ANSI(*FileName));
}

FDateTime USIK_RemoteStorageLibrary::GetFileTimestamp(const FString& FileName, int64& Timestamp)
{
	if(!SteamRemoteStorage())
	{
		return FDateTime();
	}
	Timestamp = SteamRemoteStorage()->GetFileTimestamp(TCHAR_TO_ANSI(*FileName));
	return FDateTime::FromUnixTimestamp(Timestamp);
}

int32 USIK_RemoteStorageLibrary::GetLocalFileChangeCount()
{
	if(!SteamRemoteStorage())
	{
		return 0;
	}
	return SteamRemoteStorage()->GetLocalFileChangeCount();
}

FString USIK_RemoteStorageLibrary::GetLocalFileChange(int32 File, TEnumAsByte<ESIK_RemoteStorageLocalFileChange>& ChangeType,
	TEnumAsByte<ESIK_RemoteStorageFilePathType>& PathType)
{
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
}

bool USIK_RemoteStorageLibrary::GetQuota(int64& TotalBytes, int64& AvailableBytes)
{
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
}

TEnumAsByte<ESIK_RemoteStoragePlatform> USIK_RemoteStorageLibrary::GetSyncPlatforms(const FString& FileName)
{
	if(!SteamRemoteStorage())
	{
		return ESIK_RemoteStoragePlatform::RemoteStoragePlatformNone;
	}
	return static_cast<ESIK_RemoteStoragePlatform>(SteamRemoteStorage()->GetSyncPlatforms(TCHAR_TO_ANSI(*FileName)));
}

bool USIK_RemoteStorageLibrary::GetUGCDetails(FSIK_UGCHandle UGCHandle, FString& FileName, int32& FileSize,
	FSIK_SteamId& OwnerID)
{
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
}

bool USIK_RemoteStorageLibrary::GetUGCDownloadProgress(FSIK_UGCHandle UGCHandle, int32& BytesDownloaded,
	int32& BytesExpected)
{
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
}

bool USIK_RemoteStorageLibrary::IsCloudEnabledForAccount()
{
	if(!SteamRemoteStorage())
	{
		return false;
	}
	return SteamRemoteStorage()->IsCloudEnabledForAccount();
}

bool USIK_RemoteStorageLibrary::IsCloudEnabledForApp()
{
	if(!SteamRemoteStorage())
	{
		return false;
	}
	return SteamRemoteStorage()->IsCloudEnabledForApp();
}

void USIK_RemoteStorageLibrary::SetCloudEnabledForApp(bool bEnabled)
{
	if(!SteamRemoteStorage())
	{
		return;
	}
	SteamRemoteStorage()->SetCloudEnabledForApp(bEnabled);
}

bool USIK_RemoteStorageLibrary::SetSyncPlatforms(const FString& FileName,
	ESIK_RemoteStoragePlatform RemoteStoragePlatform)
{
	if(!SteamRemoteStorage())
	{
		return false;
	}
	return SteamRemoteStorage()->SetSyncPlatforms(TCHAR_TO_ANSI(*FileName), static_cast<ERemoteStoragePlatform>(RemoteStoragePlatform));
}

int32 USIK_RemoteStorageLibrary::UGCRead(const FSIK_UGCHandle UGCHandle, TArray<uint8>& Data, int32 DataToRead,
	int32 Offset,TEnumAsByte<ESIK_UGCReadAction> Action)
{
	if(!SteamRemoteStorage())
	{
		return 0;
	}
	Data.SetNumUninitialized(DataToRead);
	return SteamRemoteStorage()->UGCRead(UGCHandle.GetUGCHandle(), Data.GetData(), DataToRead, Offset, static_cast<EUGCReadAction>(Action.GetValue()));
}
