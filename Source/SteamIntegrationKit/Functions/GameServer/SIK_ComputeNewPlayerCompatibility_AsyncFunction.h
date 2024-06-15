// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
THIRD_PARTY_INCLUDES_START
#if WITH_ENGINE_STEAM
#include <steam/steamtypes.h>
#include <steam/isteamuserstats.h>
#include <steam/steam_api_common.h>
#include <steam/steam_gameserver.h>
#else
#include <steamtypes.h>
#include <isteamuserstats.h>
#include <steam_api_common.h>
#include <steam_gameserver.h>
#endif
THIRD_PARTY_INCLUDES_END
#include "SIK_SharedFile.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SIK_ComputeNewPlayerCompatibility_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FComputeNewPlayerCompatibilityDelegate, const TEnumAsByte<ESIK_Result>&, Result, int32, PlayersThatDontLikeCandidate, int32, PlayersThatCandidateDoesntLike, int32, ClanPlayersThatDontLikeCandidate);
UCLASS()
class STEAMINTEGRATIONKIT_API USIK_ComputeNewPlayerCompatibility_AsyncFunction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, DisplayName="Compute New Player Compatibility",meta = (BlueprintInternalUseOnly = "true"), Category= "Steam Integration Kit || SDK Functions || Game Server")
	static USIK_ComputeNewPlayerCompatibility_AsyncFunction* ComputeNewPlayerCompatibility(const FSIK_SteamId& PlayerSteamId);

	UPROPERTY(BlueprintAssignable)
	FComputeNewPlayerCompatibilityDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FComputeNewPlayerCompatibilityDelegate OnFailure;
private:
	FSIK_SteamId Var_PlayerSteamId;
	void OnComputeNewPlayerCompatibilityCallback(ComputeNewPlayerCompatibilityResult_t* ComputeNewPlayerCompatibilityResult, bool bIOFailure);
	virtual void Activate() override;
	SteamAPICall_t CallbackHandle;
	CCallResult<USIK_ComputeNewPlayerCompatibility_AsyncFunction, ComputeNewPlayerCompatibilityResult_t> OnComputeNewPlayerCompatibilityCallResult;
};
