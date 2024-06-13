// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
THIRD_PARTY_INCLUDES_START
#if WITH_ENGINE_STEAM
#include <steam/steamtypes.h>
#include <steam/isteammatchmaking.h>
#include <steam/steam_api_common.h>
#else
#include <steamtypes.h>
#include <isteammatchmaking.h>
#include <steam_api_common.h>
#endif
THIRD_PARTY_INCLUDES_END
#include "SIK_SharedFile.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SIK_ChangeNumOpenSlots_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChangeNumOpenSlotsDelegate, const TEnumAsByte<ESIK_Result>, Result);
UCLASS()
class STEAMINTEGRATIONKIT_API USIK_ChangeNumOpenSlots_AsyncFunction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, DisplayName="Change Num Open Slots",meta = (BlueprintInternalUseOnly = "true"), Category="Steam Integration Kit || SDK Functions || Parties")
	static USIK_ChangeNumOpenSlots_AsyncFunction* ChangeNumOpenSlots(const FSIK_PartyBeaconID& PartyBeaconID, int32 OpenSlots);
	
	UPROPERTY(BlueprintAssignable)
	FChangeNumOpenSlotsDelegate OnSuccess;
	
	UPROPERTY(BlueprintAssignable)
	FChangeNumOpenSlotsDelegate OnFailure;
	
private:
	int32 Var_nOpenSlots;
	FSIK_PartyBeaconID PartyBeaconID;
	void OnChangeNumOpenSlots(ChangeNumOpenSlotsCallback_t* ChangeNumOpenSlotsCallback, bool bIOFailure);
	virtual void Activate() override;
	SteamAPICall_t CallbackHandle;
	CCallResult<USIK_ChangeNumOpenSlots_AsyncFunction, ChangeNumOpenSlotsCallback_t> OnChangeNumOpenSlotsCallResult;
};
