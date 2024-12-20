// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SIK_SharedFile.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SIK_PlayerDetails_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAddPlayerToList, FString, PlayerName, int32, Score, float, TimePlayed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayersFailedToRespond);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayersRefreshComplete);

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_PlayerDetails_AsyncFunction : public UBlueprintAsyncActionBase
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	, public ISteamMatchmakingPlayersResponse
#endif
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
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	virtual void AddPlayerToList(const char* pchName, int nScore, float flTimePlayed) override;
	virtual void PlayersFailedToRespond() override;
	virtual void PlayersRefreshComplete() override;
	HServerQuery ServerQueryHandle;
#endif

};
