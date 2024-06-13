// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "SIK_WebApi_ActionBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRequestComplete, bool, bSuccess, const FString&, Response);

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_WebApi_ActionBase : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | WebApi")
	FOnRequestComplete OnComplete;

	FString SteamUrl = "https://partner.steam-api.com/";


protected:
	virtual void Activate() override;

	// Virtual function to allow child classes to add fields to the request content
	virtual void AddFieldsToRequestContent(TSharedRef<FJsonObject> JsonObject);

	FString InterfaceName = "ICheatReportingService";
	FString MethodName = "ReportPlayerCheating";
	int32 Version = 1;
	FString RequestContent;
	FString RequestMethod = "POST";
private:

	void OnRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSuccess);

	TSharedRef<IHttpRequest> CreateHttpRequest();
};
