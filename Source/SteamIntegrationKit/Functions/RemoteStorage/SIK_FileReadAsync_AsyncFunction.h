// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SIK_SharedFile.h"
#include "SIK_FileReadAsync_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnRemoteStorageFileReadAsyncComplete, const TEnumAsByte<ESIK_Result>&, Result, int32, nOffset, int32, nBytesRead, const TArray<uint8>&, Data);

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_FileReadAsync_AsyncFunction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	/*
	Starts an asynchronous read from a file.
	The offset and amount to read should be valid for the size of the file, as indicated by GetFileSize or GetFileTimestamp.
	
	Returns k_uAPICallInvalid under the following conditions:
	*You tried to read from invalid path or filename. Because Steam Cloud is cross platform the files need to have valid names on all supported OSes and file systems. See Microsoft's documentation on Naming Files, Paths, and Namespaces.
	*The file doesn't exist.
	*cubDataToRead is <= 0 bytes. You need to be able to read something!
	*The combination of pvData and cubDataToRead would read past the end of the file.
	*You have an async read in progress on this file already.
	
	Upon completion of the read request you will receive the call result, if the value of m_eResult within the call result is k_EResultOK you can then call FileReadAsyncComplete to read the requested data into your buffer
	*/
	UFUNCTION(BlueprintCallable, DisplayName="File Read Async",meta = (BlueprintInternalUseOnly = "true"), Category="Steam Integration Kit || SDK Functions || Remote Storage|| Async")
	static USIK_FileReadAsync_AsyncFunction* FileReadAsync(const FString& FileName, int32 nOffset, int32 nBytesToRead);

	UPROPERTY(BlueprintAssignable)
	FOnRemoteStorageFileReadAsyncComplete OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnRemoteStorageFileReadAsyncComplete OnFailure;
private:
	FString Var_FileName;
	int32 Var_nOffset;
	int32 Var_nBytesToRead;
	virtual void Activate() override;
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
	void OnFileReadAsync(RemoteStorageFileReadAsyncComplete_t* RemoteStorageFileReadAsyncComplete, bool bIOFailure);
	SteamAPICall_t CallbackHandle;
	CCallResult<USIK_FileReadAsync_AsyncFunction, RemoteStorageFileReadAsyncComplete_t> OnFileReadAsyncCallResult;
#endif

};
