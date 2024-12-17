// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SIK_SharedFile.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SIK_AssociateWithClan_AsyncFunction.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAssociateWithClanDelegate, const TEnumAsByte<ESIK_Result>&, Result);

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_AssociateWithClan_AsyncFunction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, DisplayName="Associate With Clan",meta = (BlueprintInternalUseOnly = "true"), Category= "Steam Integration Kit || SDK Functions || Game Server")
	static USIK_AssociateWithClan_AsyncFunction* AssociateWithClan(const FSIK_SteamId& SteamIdClan);

	UPROPERTY(BlueprintAssignable)
	FAssociateWithClanDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FAssociateWithClanDelegate OnFailure;

private:
	FSIK_SteamId SteamIdClan;
	virtual void Activate() override;

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	void OnAssociateWithClanCallBack(AssociateWithClanResult_t* AssociateWithClanResult, bool bIOFailure);
	SteamAPICall_t CallbackHandle;
	CCallResult<USIK_AssociateWithClan_AsyncFunction, AssociateWithClanResult_t> OnAssociateWithClanCallResult;
#endif
};
