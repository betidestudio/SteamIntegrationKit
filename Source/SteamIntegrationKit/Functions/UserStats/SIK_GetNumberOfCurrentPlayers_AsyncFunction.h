// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
THIRD_PARTY_INCLUDES_START
#if WITH_ENGINE_STEAM
#include <steam/steam_api.h>
#include <steam/isteamuserstats.h>
#include <steam/steam_api_common.h>
#else
#include <steam_api.h>
#include <isteamuserstats.h>
#include <steam_api_common.h>
#endif
THIRD_PARTY_INCLUDES_END
#include "SIK_SharedFile.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SIK_GetNumberOfCurrentPlayers_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNumberOfCurrentPlayersReceived, int32, NumberOfCurrentPlayers);

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_GetNumberOfCurrentPlayers_AsyncFunction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, DisplayName="Get Number Of Current Players", meta = (BlueprintInternalUseOnly = "true", Keywords="GetNumberOfCurrentPlayers"), Category="Steam Integration Kit || SDK Functions || User Stats")
	static USIK_GetNumberOfCurrentPlayers_AsyncFunction* GetNumberOfCurrentPlayers();
	
	UPROPERTY(BlueprintAssignable)
	FOnNumberOfCurrentPlayersReceived OnSuccess;
	
	UPROPERTY(BlueprintAssignable)
	FOnNumberOfCurrentPlayersReceived OnFailure;
	
private:
	void OnNumberOfCurrentPlayersReceived(NumberOfCurrentPlayers_t* NumberOfCurrentPlayers, bool bIOFailure);
	virtual void Activate() override;
	SteamAPICall_t m_CallbackHandle;
	CCallResult<USIK_GetNumberOfCurrentPlayers_AsyncFunction, NumberOfCurrentPlayers_t> m_OnNumberOfCurrentPlayersReceived;
};
