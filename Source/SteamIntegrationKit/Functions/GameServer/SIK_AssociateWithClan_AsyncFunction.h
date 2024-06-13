// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
THIRD_PARTY_INCLUDES_START
#if WITH_ENGINE_STEAM
#include <steam/steam_api.h>
#include <steam/steam_api_common.h>
#include <steam/steam_gameserver.h>
#include <steam/isteamuserstats.h>
#else
#include <steam_api.h>
#include <steam_api_common.h>
#include <steam_gameserver.h>
#include <isteamuserstats.h>
#endif
THIRD_PARTY_INCLUDES_END
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
	void OnAssociateWithClanCallBack(AssociateWithClanResult_t* AssociateWithClanResult, bool bIOFailure);
	virtual void Activate() override;
	SteamAPICall_t CallbackHandle;
	CCallResult<USIK_AssociateWithClan_AsyncFunction, AssociateWithClanResult_t> OnAssociateWithClanCallResult;
};
