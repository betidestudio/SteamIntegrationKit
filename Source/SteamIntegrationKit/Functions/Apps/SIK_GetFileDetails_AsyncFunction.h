// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
THIRD_PARTY_INCLUDES_START
#if WITH_ENGINE_STEAM
#include <steam/steam_api.h>
#include <steam/isteamapps.h>
#include <steam/steam_api_common.h>
#else
#include <steam_api.h>
#include <isteamapps.h>
#endif
THIRD_PARTY_INCLUDES_END
#include "SIK_SharedFile.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SIK_GetFileDetails_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FGetFileDetailsResult, TEnumAsByte<ESIK_Result>, Result, int64, FileSize, const TArray<int32>&, FileHash, int32, Flags);
UCLASS()
class STEAMINTEGRATIONKIT_API USIK_GetFileDetails_AsyncFunction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, DisplayName="Get File Details", meta = (BlueprintInternalUseOnly = "true", Keywords="GetFileDetails"), Category="Steam Integration Kit || SDK Functions || Apps")
	static USIK_GetFileDetails_AsyncFunction* GetFileDetails(const FString& FileName);
	
	UPROPERTY(BlueprintAssignable)
	FGetFileDetailsResult OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FGetFileDetailsResult OnFailure;
private:
	FString m_FileName;
	void OnGetFileDetails(FileDetailsResult_t* FileDetailsResult, bool bIOFailure);
	virtual void Activate() override;
	SteamAPICall_t m_CallbackHandle;
	CCallResult<USIK_GetFileDetails_AsyncFunction, FileDetailsResult_t> m_Callback;
};
