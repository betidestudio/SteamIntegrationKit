// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SIK_SharedFile.h"
#include "SIK_UGCDownloadToLocation_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnUGCDownloadToLocationComplete, TEnumAsByte<ESIK_Result>, Result, FSIK_UGCHandle, UGCHandle, int32, AppID, FString, FileName, int32, Size, FSIK_SteamId, SteamIDOwner);

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_UGCDownloadToLocation_AsyncFunction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	/*
	Downloads a UGC file to a specified location. A file is downloaded by UGC handle.
	If a valid path is passed the file is saved to that location rather than to the cached UGC folder.
	
	Returns a SteamAPICall_t handle that is watched for the callback RemoteStorageDownloadUGCResult_t.
	*/
	UFUNCTION(BlueprintCallable, DisplayName="UGC Download To Location",meta = (BlueprintInternalUseOnly = "true"), Category="Steam Integration Kit || SDK Functions || Remote Storage|| Async")
	static USIK_UGCDownloadToLocation_AsyncFunction* UGCDownloadToLocation(FSIK_UGCHandle UGCHandle, const FString& Location, int32 Priority);

	UPROPERTY(BlueprintAssignable)
	FOnUGCDownloadToLocationComplete OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnUGCDownloadToLocationComplete OnFailure;
private:
	FSIK_UGCHandle Var_UGCHandle;
	FString Var_Location;
	int32 Var_Priority;
	virtual void Activate() override;
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
	void OnUGCDownloadToLocation(RemoteStorageDownloadUGCResult_t* RemoteStorageDownloadUGCResult, bool bIOFailure);
	SteamAPICall_t CallbackHandle;
	CCallResult<USIK_UGCDownloadToLocation_AsyncFunction, RemoteStorageDownloadUGCResult_t> OnUGCDownloadToLocationCallResult;
#endif

};