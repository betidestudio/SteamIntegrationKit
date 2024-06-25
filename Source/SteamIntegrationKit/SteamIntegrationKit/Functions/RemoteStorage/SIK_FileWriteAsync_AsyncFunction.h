// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SIK_SharedFile.h"
THIRD_PARTY_INCLUDES_START
#if WITH_ENGINE_STEAM
#include <steam/steam_api.h>
#include <steam/isteamremotestorage.h>
#include <steam/steam_api_common.h>
#else
#include <steam_api.h>
#include <isteamremotestorage.h>
#include <steam_api_common.h>
#endif
THIRD_PARTY_INCLUDES_END
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
	void OnFileWriteAsyncComplete(RemoteStorageFileWriteAsyncComplete_t* RemoteStorageFileWriteAsyncComplete, bool bIOFailure);
	virtual void Activate() override;
	SteamAPICall_t CallbackHandle;
	CCallResult<USIK_FileWriteAsync_AsyncFunction, RemoteStorageFileWriteAsyncComplete_t> OnFileWriteAsyncCallResult;
};
