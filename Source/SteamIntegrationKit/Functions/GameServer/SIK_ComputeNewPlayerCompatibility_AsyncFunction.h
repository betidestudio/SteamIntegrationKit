// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
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
	virtual void Activate() override;
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	void OnComputeNewPlayerCompatibilityCallback(ComputeNewPlayerCompatibilityResult_t* ComputeNewPlayerCompatibilityResult, bool bIOFailure);
	SteamAPICall_t CallbackHandle;
	CCallResult<USIK_ComputeNewPlayerCompatibility_AsyncFunction, ComputeNewPlayerCompatibilityResult_t> OnComputeNewPlayerCompatibilityCallResult;
#endif
};
