// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
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
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
	void OnNumberOfCurrentPlayersReceived(NumberOfCurrentPlayers_t* NumberOfCurrentPlayers, bool bIOFailure);
	SteamAPICall_t m_CallbackHandle;
	CCallResult<USIK_GetNumberOfCurrentPlayers_AsyncFunction, NumberOfCurrentPlayers_t> m_OnNumberOfCurrentPlayersReceived;
#endif
	virtual void Activate() override;

};
