// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#include "SIK_WebApi_ActionBase.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"

void USIK_WebApi_ActionBase::OnRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSuccess)
{
	if (bSuccess && HttpResponse.IsValid())
	{
		FString Response = HttpResponse->GetContentAsString();
		UE_LOG(LogTemp, Warning, TEXT("Response: %s"), *Response);
		OnComplete.Broadcast(true, Response);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Request failed"));
		OnComplete.Broadcast(false, "");
	} 
	SetReadyToDestroy();
	MarkAsGarbage();
}

void USIK_WebApi_ActionBase::Activate()
{
	Super::Activate();
	TSharedRef<IHttpRequest> HttpRequest = CreateHttpRequest();
	HttpRequest->ProcessRequest();
}

void USIK_WebApi_ActionBase::AddFieldsToRequestContent(TSharedRef<FJsonObject> JsonObject)
{
	
}

TSharedRef<IHttpRequest> USIK_WebApi_ActionBase::CreateHttpRequest()
{
	FHttpModule& HttpModule = FHttpModule::Get();
	TSharedRef<IHttpRequest> HttpRequest = HttpModule.CreateRequest();
	SteamUrl += InterfaceName + "/" + MethodName + "/v" + FString::FromInt(Version) + "/";
	HttpRequest->SetVerb(RequestMethod);
	HttpRequest->SetHeader("Content-Type", "application/x-www-form-urlencoded");
	// Create the JSON request content
	TSharedRef<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	AddFieldsToRequestContent(JsonObject);
	if(RequestMethod == "POST")
	{
		FString OutputString;
		TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
		FJsonSerializer::Serialize(JsonObject, Writer);

		HttpRequest->SetContentAsString(OutputString);
	}
	HttpRequest->SetURL(SteamUrl);
	UE_LOG(LogTemp, Warning, TEXT("Request URL: %s"), *HttpRequest->GetURL());
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &USIK_WebApi_ActionBase::OnRequestComplete);
	return HttpRequest;
}