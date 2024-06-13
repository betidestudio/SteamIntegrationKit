// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
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
#include "SIK_RequestLobbyList_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRequestLobbyList, int32, LobbiesMatching);

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_RequestLobbyList_AsyncFunction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, DisplayName="Request Lobby List",meta = (BlueprintInternalUseOnly = "true"), Category= "Steam Integration Kit || SDK Functions || Matchmaking")
	static USIK_RequestLobbyList_AsyncFunction* RequestLobbyList();
	
	UPROPERTY(BlueprintAssignable)
	FOnRequestLobbyList OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnRequestLobbyList OnFailure;
private:
	void OnLobbyListReceived(LobbyMatchList_t* LobbyMatches, bool bIOFailure);
	virtual void Activate() override;
	SteamAPICall_t CallbackHandle;
	CCallResult<USIK_RequestLobbyList_AsyncFunction, LobbyMatchList_t> CallResult;
};
