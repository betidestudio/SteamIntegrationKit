// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SIK_SharedFile.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SIK_RequestEligiblePromoItemDefinitionsIDs_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnRequestEligiblePromoItemDefinitionsIDs, TEnumAsByte<ESIK_Result>, Result, FSIK_SteamId, SteamID, int32, numEligiblePromoItemDefs, bool, bCachedData);
UCLASS()
class STEAMINTEGRATIONKIT_API
	USIK_RequestEligiblePromoItemDefinitionsIDs_AsyncFunction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, DisplayName = "Request Eligible Promo Item Definitions IDs", meta = (BlueprintInternalUseOnly = "true"), Category = "Steam Integration Kit || SDK Functions || Inventory")
	static USIK_RequestEligiblePromoItemDefinitionsIDs_AsyncFunction* RequestEligiblePromoItemDefinitionsIDs(FSIK_SteamId SteamID);
	
	UPROPERTY(BlueprintAssignable)
	FOnRequestEligiblePromoItemDefinitionsIDs OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnRequestEligiblePromoItemDefinitionsIDs OnFailure;
private:
	FSIK_SteamId Var_SteamID;
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	void OnEligiblePromoItemDefinitionsIDsReceived(SteamInventoryEligiblePromoItemDefIDs_t* SteamInventoryEligiblePromoItemDefIDs, bool bIOFailure);
	SteamAPICall_t CallbackHandle;
	CCallResult<USIK_RequestEligiblePromoItemDefinitionsIDs_AsyncFunction, SteamInventoryEligiblePromoItemDefIDs_t> CallResult;
#endif
	virtual void Activate() override;

};
