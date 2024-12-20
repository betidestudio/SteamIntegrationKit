// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SIK_SharedFile.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SIK_SteamCreateLobby_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCreateLobbyDelegate, TEnumAsByte<ESIK_Result>, Result, FSIK_SteamId, LobbyID);
UCLASS()
class STEAMINTEGRATIONKIT_API USIK_SteamCreateLobby_AsyncFunction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, DisplayName="Create Lobby",meta = (BlueprintInternalUseOnly = "true"), Category= "Steam Integration Kit || SDK Functions || Matchmaking")
	static USIK_SteamCreateLobby_AsyncFunction* CreateLobby(int32 MaxMembers, TEnumAsByte<ESIK_LobbyType> LobbyType);

	UPROPERTY(BlueprintAssignable)
	FCreateLobbyDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FCreateLobbyDelegate OnFailure;

private:
	int32 Var_nMaxMembers;
	TEnumAsByte<ESIK_LobbyType> Var_LobbyType;
	virtual void Activate() override;
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	void OnCreateLobbyCallback(LobbyCreated_t* LobbyCreated, bool bIOFailure);
	SteamAPICall_t CallbackHandle;
	CCallResult<USIK_SteamCreateLobby_AsyncFunction, LobbyCreated_t> OnCreateLobbyCallResult;
#endif
};
