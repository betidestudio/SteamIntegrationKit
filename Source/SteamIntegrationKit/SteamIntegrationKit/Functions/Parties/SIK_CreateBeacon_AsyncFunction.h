// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
THIRD_PARTY_INCLUDES_START
#if WITH_ENGINE_STEAM
#include <steam/steam_api.h>
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
#include "SIK_CreateBeacon_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCreateBeaconDelegate, TEnumAsByte<ESIK_Result>, Result, FSIK_PartyBeaconID, BeaconID);
UCLASS()
class STEAMINTEGRATIONKIT_API USIK_CreateBeacon_AsyncFunction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, DisplayName="Create Beacon",meta = (BlueprintInternalUseOnly = "true"), Category="Steam Integration Kit || SDK Functions || Parties")
	static USIK_CreateBeacon_AsyncFunction* CreateBeacon(int32 OpenSlots, const FSIK_SteamPartyBeaconLocation& Location, const FString& ConnectString, const FString& Metadata);
	
	UPROPERTY(BlueprintAssignable)
	FCreateBeaconDelegate OnSuccess;
	
	UPROPERTY(BlueprintAssignable)
	FCreateBeaconDelegate OnFailure;
private:
	int32 Var_nOpenSlots;
	SteamPartyBeaconLocation_t Var_Location;
	FString Var_sConnectString;
	FString Var_sMetadata;
	void OnCreateBeaconCallback(CreateBeaconCallback_t* CreateBeaconCallback, bool bIOFailure);
	virtual void Activate() override;
	SteamAPICall_t CallbackHandle;
	CCallResult<USIK_CreateBeacon_AsyncFunction, CreateBeaconCallback_t> OnCreateBeaconCallResult;
};
