// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SteamWebApi.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnSteamWebApiRequestComplete, bool, bSuccess, const FString&, Response);

UCLASS()
class STEAMINTEGRATIONKIT_API USteamWebApi : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | WebApi")
	void AuthenticateUser(const FString& SteamId, const TArray<uint8>& SessionKey, const TArray<uint8>& EncryptedLoginKey, FOnSteamWebApiRequestComplete OnComplete);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | WebApi")
	void AuthenticateUserTicket(const FString& Key, const FString& AppId, const FString& Ticket, const FString& Identity, FOnSteamWebApiRequestComplete OnComplete);

private:
	void OnRequestComplete_Internal(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSuccess, FOnSteamWebApiRequestComplete OnComplete);
	void MakeHttpRequest(const FString& Url, const FString& RequestMethod, const TSharedRef<FJsonObject>& JsonObject, FOnSteamWebApiRequestComplete OnComplete);
};