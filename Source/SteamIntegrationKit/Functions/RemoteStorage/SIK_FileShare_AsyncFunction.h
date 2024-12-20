// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SIK_SharedFile.h"
#include "SIK_FileShare_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnRemoteStorageFileShareComplete, const TEnumAsByte<ESIK_Result>&, Result, const FString&, SharedFile, const FSIK_UGCHandle&, UGCHandle);
UCLASS()
class STEAMINTEGRATIONKIT_API USIK_FileShare_AsyncFunction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, DisplayName = "File Share Async", meta = (BlueprintInternalUseOnly = "true"), Category = "Steam Integration Kit || SDK Functions || Remote Storage")
	static USIK_FileShare_AsyncFunction* FileShareAsync(const FString& FileName);

	UPROPERTY(BlueprintAssignable)
	FOnRemoteStorageFileShareComplete OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnRemoteStorageFileShareComplete OnFailure;
	
private:
	FString Var_FileName;
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
	void OnFileShare(RemoteStorageFileShareResult_t* RemoteStorageFileShareResult, bool bIOFailure);
	SteamAPICall_t CallbackHandle;
	CCallResult<USIK_FileShare_AsyncFunction, RemoteStorageFileShareResult_t> OnFileShareCallResult;
#endif
	virtual void Activate() override;

};
