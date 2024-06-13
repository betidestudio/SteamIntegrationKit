// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SteamIntegrationKit/WebApi/SIK_WebApi_ActionBase.h"
#include "SIK_WebApi_GetFriendList.generated.h"

/**
 * 
 */
UCLASS()
class STEAMINTEGRATIONKIT_API USIK_WebApi_GetFriendList : public USIK_WebApi_ActionBase
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | WebApi")
	static USIK_WebApi_GetFriendList* GetFriendList(const FString& Key, const FString& SteamId, const FString& Relationship = "");

private:
	FString Var_Key = "key";
	FString Var_SteamId = "steamid";
	FString Var_Relationship = "friend";
	virtual void Activate() override;
	virtual void AddFieldsToRequestContent(TSharedRef<FJsonObject> JsonObject) override;
};
