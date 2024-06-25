// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#pragma once

#include "CoreMinimal.h"
#include "SteamIntegrationKit/WebApi/SIK_WebApi_ActionBase.h"
#include "SIK_WebApi_AuthenticateUser.generated.h"

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_WebApi_AuthenticateUser : public USIK_WebApi_ActionBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | WebApi")
	static USIK_WebApi_AuthenticateUser* AuthenticateUser(const FString& SteamId, const FString& SessionKey, const FString& EncryptedLoginKey);

protected:
	virtual void AddFieldsToRequestContent(TSharedRef<FJsonObject> JsonObject) override;

private:
	FString Var_SteamId;
	FString Var_SessionKey;
	FString Var_EncryptedLoginKey;
	virtual void Activate() override;
};
