// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_WebApi_GetFriendList.h"

#include "Dom/JsonObject.h"

USIK_WebApi_GetFriendList* USIK_WebApi_GetFriendList::GetFriendList(const FString& Key, const FString& SteamId,
	const FString& Relationship)
{
	USIK_WebApi_GetFriendList* Action = NewObject<USIK_WebApi_GetFriendList>();
	Action->Var_Key = Key;
	Action->Var_SteamId = SteamId;
	Action->Var_Relationship = Relationship;
	return Action;
}

void USIK_WebApi_GetFriendList::Activate()
{
	InterfaceName = "ISteamUser";
	MethodName = "GetFriendList";
	RequestMethod = "GET";
	Super::Activate();
}

void USIK_WebApi_GetFriendList::AddFieldsToRequestContent(TSharedRef<FJsonObject> JsonObject)
{
	Super::AddFieldsToRequestContent(JsonObject);
	JsonObject->SetStringField("key", Var_Key);
	JsonObject->SetStringField("steamid", Var_SteamId);
	if(Var_Relationship.Len() > 0)
	{
		JsonObject->SetStringField("relationship", Var_Relationship);
	}
	FString UrlParameters = "?key=" + Var_Key + "&steamid=" + Var_SteamId + "&relationship=" + Var_Relationship;
	SteamUrl += UrlParameters;
}
