// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SIK_SharedFile.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SIK_RequestPrices_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRequestPrices, TEnumAsByte<ESIK_Result>, Result, const FString&, CurrencyCode);

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_RequestPrices_AsyncFunction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, DisplayName = "Request Prices", meta = (BlueprintInternalUseOnly = "true"), Category = "Steam Integration Kit || SDK Functions || Inventory")
	static USIK_RequestPrices_AsyncFunction* RequestPrices();
	
	UPROPERTY(BlueprintAssignable)
	FOnRequestPrices OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnRequestPrices OnFailure;
private:
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	void OnPricesReceived(SteamInventoryRequestPricesResult_t* SteamInventoryRequestPricesResult, bool bIOFailure);
	SteamAPICall_t CallbackHandle;
	CCallResult<USIK_RequestPrices_AsyncFunction, SteamInventoryRequestPricesResult_t> CallResult;
#endif
	virtual void Activate() override;

};
