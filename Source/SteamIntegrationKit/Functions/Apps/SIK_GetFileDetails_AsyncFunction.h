// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
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
	virtual void Activate() override;
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	void OnGetFileDetails(FileDetailsResult_t* FileDetailsResult, bool bIOFailure);
	SteamAPICall_t m_CallbackHandle;
	CCallResult<USIK_GetFileDetails_AsyncFunction, FileDetailsResult_t> m_Callback;
#endif
};
