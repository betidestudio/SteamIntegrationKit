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
#include "SIK_JoinLobby_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnJoinLobby, bool, bLocked, TEnumAsByte<ESIK_ChatRoomEnterResponse>, ChatRoomEnterResponse);
UCLASS()
class STEAMINTEGRATIONKIT_API USIK_JoinLobby_AsyncFunction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, DisplayName="Join Lobby",meta = (BlueprintInternalUseOnly = "true"), Category= "Steam Integration Kit || SDK Functions || Matchmaking" )
	static USIK_JoinLobby_AsyncFunction* JoinLobby(FSIK_SteamId LobbyId);
	
	UPROPERTY(BlueprintAssignable)
	FOnJoinLobby OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnJoinLobby OnFailure;
private:
	FSIK_SteamId Var_LobbyId;
	void OnLobbyEnter(LobbyEnter_t* LobbyEnter, bool bIOFailure);
	virtual void Activate() override;
	SteamAPICall_t CallbackHandle;
	CCallResult<USIK_JoinLobby_AsyncFunction, LobbyEnter_t> CallResult;
};
