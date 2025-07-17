// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SIK_SharedFile.h"
#include "SIK_UGCDownload_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnUGCDownloadComplete, TEnumAsByte<ESIK_Result>, Result, FSIK_UGCHandle, UGCHandle, int32, AppID, FString, FileName, int32, Size, FSIK_SteamId, SteamIDOwner);

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_UGCDownload_AsyncFunction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	/*
	Downloads a UGC file. A file is downloaded by UGC handle.
	Priority and cubUncompressedFileSize are available on the file page of the UGC item and are passed in so 
	Steam can prioritize downloads and display progress to the user. Be sure to pass the uncompress file size 
	even if it's the same as the compressed file size.
	
	Returns a SteamAPICall_t handle that is watched for the callback RemoteStorageDownloadUGCResult_t.
	*/
	UFUNCTION(BlueprintCallable, DisplayName="UGC Download",meta = (BlueprintInternalUseOnly = "true"), Category="Steam Integration Kit || SDK Functions || Remote Storage|| Async")
	static USIK_UGCDownload_AsyncFunction* UGCDownload(FSIK_UGCHandle UGCHandle, int32 Priority);

	UPROPERTY(BlueprintAssignable)
	FOnUGCDownloadComplete OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnUGCDownloadComplete OnFailure;
private:
	FSIK_UGCHandle Var_UGCHandle;
	int32 Var_Priority;
	virtual void Activate() override;
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
	void OnUGCDownload(RemoteStorageDownloadUGCResult_t* RemoteStorageDownloadUGCResult, bool bIOFailure);
	SteamAPICall_t CallbackHandle;
	CCallResult<USIK_UGCDownload_AsyncFunction, RemoteStorageDownloadUGCResult_t> OnUGCDownloadCallResult;
#endif

};