// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
THIRD_PARTY_INCLUDES_START
#if WITH_ENGINE_STEAM
#include <steam/steam_api.h>
#include <steam/isteammatchmaking.h>
#include <steam/steam_api_common.h>
#include <steam/steamtypes.h>
#else
#include <steamtypes.h>
#include <isteammatchmaking.h>
#include <steam_api_common.h>
#endif
THIRD_PARTY_INCLUDES_END
#include "SIK_SharedFile.h"
#include "SIK_JoinParty_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FSIK_JoinPartyResult, TEnumAsByte<ESIK_Result>, Result, FSIK_PartyBeaconID, PartyBeaconID, FSIK_SteamId, BeaconOwner, FString, ConnectString);
UCLASS()
class STEAMINTEGRATIONKIT_API USIK_JoinParty_AsyncFunction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, DisplayName="Join Party",meta = (BlueprintInternalUseOnly = "true"), Category="Steam Integration Kit || SDK Functions || Parties")
	static USIK_JoinParty_AsyncFunction* JoinParty(FSIK_PartyBeaconID SteamId);
	
	UPROPERTY(BlueprintAssignable)
	FSIK_JoinPartyResult OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FSIK_JoinPartyResult OnFailure;

private:
	FSIK_PartyBeaconID Var_SteamId;
	void OnJoinPartyCallback(JoinPartyCallback_t* JoinPartyCallback, bool bIOFailure);
	virtual void Activate() override;
	SteamAPICall_t CallbackHandle;
	CCallResult<USIK_JoinParty_AsyncFunction, JoinPartyCallback_t> JoinPartyCallResult;
};
