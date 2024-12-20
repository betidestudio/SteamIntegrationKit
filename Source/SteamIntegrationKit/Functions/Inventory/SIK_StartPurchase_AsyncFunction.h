// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SIK_SharedFile.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SIK_StartPurchase_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnStartPurchaseResult, TEnumAsByte<ESIK_Result>, Result, int64, OrderID, int64, TransID);
UCLASS()
class STEAMINTEGRATIONKIT_API USIK_StartPurchase_AsyncFunction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, DisplayName = "Start Purchase", meta = (BlueprintInternalUseOnly = "true"), Category = "Steam Integration Kit || SDK Functions || Inventory")
	static USIK_StartPurchase_AsyncFunction* StartPurchase(TArray<FSIK_SteamItemDef> Items, TArray<int32> Quantity);
	
	UPROPERTY(BlueprintAssignable)
	FOnStartPurchaseResult OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnStartPurchaseResult OnFailure;	
private:
	TArray<FSIK_SteamItemDef> Items;
	TArray<int32> Quantity;
	virtual void Activate() override;
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	void OnStartPurchaseResult(SteamInventoryStartPurchaseResult_t* SteamInventoryStartPurchaseResult, bool bIOFailure);
	SteamAPICall_t CallbackHandle;
	CCallResult<USIK_StartPurchase_AsyncFunction, SteamInventoryStartPurchaseResult_t> CallResult;
#endif
};
