// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SIK_SharedFile.h"
#include "SIK_RequestStoreAuthURL_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRequestStoreAuthURL, const FString&, URL);
UCLASS()
class STEAMINTEGRATIONKIT_API USIK_RequestStoreAuthURL_AsyncFunction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, DisplayName="Request Store Auth URL",meta = (BlueprintInternalUseOnly = "true"), Category="Steam Integration Kit || SDK Functions || User")
	static USIK_RequestStoreAuthURL_AsyncFunction* RequestStoreAuthURL(const FString& URL);
	
	UPROPERTY(BlueprintAssignable)
	FOnRequestStoreAuthURL OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnRequestStoreAuthURL OnFailure;
private:
	FString m_URL;
	virtual void Activate() override;
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
	void OnRequestStoreAuthURL(StoreAuthURLResponse_t* StoreAuthURLResponse, bool bIOFailure);
	SteamAPICall_t m_SteamAPICall;
	CCallResult<USIK_RequestStoreAuthURL_AsyncFunction, StoreAuthURLResponse_t> m_Callback;
#endif
};
