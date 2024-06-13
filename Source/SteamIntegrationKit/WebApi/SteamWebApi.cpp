// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SteamWebApi.h"

#include "HttpModule.h"
#include "Dom/JsonObject.h"
#include "Interfaces/IHttpResponse.h"
#include "Misc/Base64.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

void USteamWebApi::AuthenticateUser(const FString& SteamId, const TArray<uint8>& SessionKey, const TArray<uint8>& EncryptedLoginKey, FOnSteamWebApiRequestComplete OnComplete)
{
    FString Url = "https://partner.steam-api.com/ISteamUserAuth/AuthenticateUser/v1/";
    FString RequestMethod = "POST";

    TSharedRef<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
    JsonObject->SetStringField("steamid", SteamId);

    FString SessionKeyBase64 = FBase64::Encode(SessionKey);
    FString EncryptedLoginKeyBase64 = FBase64::Encode(EncryptedLoginKey);

    JsonObject->SetStringField("sessionkey", SessionKeyBase64);
    JsonObject->SetStringField("encrypted_loginkey", EncryptedLoginKeyBase64);

    MakeHttpRequest(Url, RequestMethod, JsonObject, OnComplete);
}

void USteamWebApi::AuthenticateUserTicket(const FString& Key, const FString& AppId, const FString& Ticket, const FString& Identity, FOnSteamWebApiRequestComplete OnComplete)
{
    FString Url = FString::Printf(TEXT("https://partner.steam-api.com/ISteamUserAuth/AuthenticateUserTicket/v1/?key=%s&appid=%s&ticket=%s&identity=%s"),
                                  *Key, *AppId, *Ticket, *Identity);
    FString RequestMethod = "GET";

    MakeHttpRequest(Url, RequestMethod, MakeShareable(new FJsonObject()), OnComplete);
}

void USteamWebApi::MakeHttpRequest(const FString& Url, const FString& RequestMethod, const TSharedRef<FJsonObject>& JsonObject, FOnSteamWebApiRequestComplete OnComplete)
{
    FHttpModule& HttpModule = FHttpModule::Get();
    TSharedRef<IHttpRequest> HttpRequest = HttpModule.CreateRequest();
    HttpRequest->SetURL(Url);
    HttpRequest->SetVerb(RequestMethod);
    HttpRequest->SetHeader("Content-Type", "application/x-www-form-urlencoded");

    if (RequestMethod == "POST" && JsonObject.ToSharedPtr().IsValid())
    {
        FString OutputString;
        TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
        FJsonSerializer::Serialize(JsonObject, Writer);
        HttpRequest->SetContentAsString(OutputString);
    }

    HttpRequest->OnProcessRequestComplete().BindUObject(this, &USteamWebApi::OnRequestComplete_Internal, OnComplete);
    HttpRequest->ProcessRequest();
}

void USteamWebApi::OnRequestComplete_Internal(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSuccess, FOnSteamWebApiRequestComplete OnComplete)
{
    if (bSuccess && HttpResponse.IsValid())
    {
        FString Response = HttpResponse->GetContentAsString();
        UE_LOG(LogTemp, Warning, TEXT("Response: %s"), *Response);
        OnComplete.ExecuteIfBound(true, Response);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Request failed"));
        OnComplete.ExecuteIfBound(false, "");
    }
}