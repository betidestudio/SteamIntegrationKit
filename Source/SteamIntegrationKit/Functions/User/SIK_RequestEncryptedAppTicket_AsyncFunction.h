// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
THIRD_PARTY_INCLUDES_START
#if WITH_ENGINE_STEAM
#include <steam/steam_api.h>
#include <steam/isteamuser.h>
#else
#include "isteamuser.h"
#include "steam_api.h"
#endif
THIRD_PARTY_INCLUDES_END
#include "SIK_SharedFile.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SIK_RequestEncryptedAppTicket_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRequestEncryptedAppTicket, TEnumAsByte<ESIK_Result>, Result);
UCLASS()
class STEAMINTEGRATIONKIT_API USIK_RequestEncryptedAppTicket_AsyncFunction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, DisplayName="Request Encrypted App Ticket",meta = (BlueprintInternalUseOnly = "true"), Category="Steam Integration Kit || SDK Functions || User")
	static USIK_RequestEncryptedAppTicket_AsyncFunction* RequestEncryptedAppTicket(const TArray<uint8>& EncryptedAppTicket);
	
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | User")
	FOnRequestEncryptedAppTicket OnSuccess;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | User")
	FOnRequestEncryptedAppTicket OnFailure;
private:
	TArray<uint8> m_EncryptedAppTicket;
	void OnRequestEncryptedAppTicket(EncryptedAppTicketResponse_t* EncryptedAppTicketResponse, bool bIOFailure);
	virtual void Activate() override;
	SteamAPICall_t m_SteamAPICall;
	CCallResult<USIK_RequestEncryptedAppTicket_AsyncFunction, EncryptedAppTicketResponse_t> m_Callback;
};
