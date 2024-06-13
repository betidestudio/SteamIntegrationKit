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
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SIK_PlayerDetails_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAddPlayerToList, FString, PlayerName, int32, Score, float, TimePlayed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayersFailedToRespond);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayersRefreshComplete);

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_PlayerDetails_AsyncFunction : public UBlueprintAsyncActionBase, public ISteamMatchmakingPlayersResponse
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, DisplayName = "Request Player Details", Category = "Steam Integration Kit || SDK Functions || Matchmaking Servers")
	static USIK_PlayerDetails_AsyncFunction* RequestPlayerDetails(const FString& ServerIP, int32 ServerPort);
	
	UPROPERTY(BlueprintAssignable)
	FOnAddPlayerToList OnAddPlayerToList;

	UPROPERTY(BlueprintAssignable)
	FOnPlayersFailedToRespond OnPlayersFailedToRespond;

	UPROPERTY(BlueprintAssignable)
	FOnPlayersRefreshComplete OnPlayersRefreshComplete;
private:
	FString Var_ServerIP;
	int32 Var_ServerPort;
	virtual void Activate() override;
	virtual void AddPlayerToList(const char* pchName, int nScore, float flTimePlayed) override;
	virtual void PlayersFailedToRespond() override;
	virtual void PlayersRefreshComplete() override;
	HServerQuery ServerQueryHandle;

};
