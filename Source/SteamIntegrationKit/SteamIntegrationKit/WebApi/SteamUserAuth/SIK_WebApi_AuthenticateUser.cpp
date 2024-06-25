// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_WebApi_AuthenticateUser.h"

#include "Dom/JsonObject.h"

USIK_WebApi_AuthenticateUser* USIK_WebApi_AuthenticateUser::AuthenticateUser(const FString& SteamId, const FString& SessionKey, const FString& EncryptedLoginKey)
{
	USIK_WebApi_AuthenticateUser* Action = NewObject<USIK_WebApi_AuthenticateUser>();
	Action->Var_SteamId = SteamId;
	Action->Var_SessionKey = SessionKey;
	Action->Var_EncryptedLoginKey = EncryptedLoginKey;
	return Action;
}

void USIK_WebApi_AuthenticateUser::Activate()
{
	InterfaceName = "ISteamUserAuth";
	MethodName = "AuthenticateUser";
	RequestMethod = "POST";
	Super::Activate();
}

void USIK_WebApi_AuthenticateUser::AddFieldsToRequestContent(TSharedRef<FJsonObject> JsonObject)
{
	Super::AddFieldsToRequestContent(JsonObject);
	JsonObject->SetStringField("steamid", Var_SteamId);
	JsonObject->SetStringField("sessionkey", Var_SessionKey);
	JsonObject->SetStringField("encrypted_loginkey", Var_EncryptedLoginKey);
}
