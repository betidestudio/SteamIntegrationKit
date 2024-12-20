// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SIK_SharedFile.h"
#include "SIK_FileWriteAsync_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFileWriteAsyncComplete, const TEnumAsByte<ESIK_Result>&, Result);

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_FileWriteAsync_AsyncFunction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, DisplayName = "File Write Async", meta = (BlueprintInternalUseOnly = "true"), Category = "Steam Integration Kit || SDK Functions || Remote Storage")
	static USIK_FileWriteAsync_AsyncFunction* FileWriteAsync(const FString& FileName, const TArray<uint8>& FileData);

	UPROPERTY(BlueprintAssignable)
	FOnFileWriteAsyncComplete OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnFileWriteAsyncComplete OnFailure;
private:
	FString Var_FileName;
	TArray<uint8> Var_FileData;
	virtual void Activate() override;
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
	void OnFileWriteAsyncComplete(RemoteStorageFileWriteAsyncComplete_t* RemoteStorageFileWriteAsyncComplete, bool bIOFailure);
	SteamAPICall_t CallbackHandle;
	CCallResult<USIK_FileWriteAsync_AsyncFunction, RemoteStorageFileWriteAsyncComplete_t> OnFileWriteAsyncCallResult;
#endif
};
