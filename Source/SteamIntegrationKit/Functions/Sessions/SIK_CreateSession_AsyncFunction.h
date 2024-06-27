// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "OnlineSubsystemUtils.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Engine/LocalPlayer.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Kismet/GameplayStatics.h"
#include "SIK_SharedFile.h"
#include "SIK_CreateSession_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSIK_CreateSession_Delegate, const FString&, SessionID);

USTRUCT(BlueprintType)
struct FSIKDedicatedServerSettings
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category="Steam Integration Kit")
	bool bIsDedicatedServer = false;

	UPROPERTY(BlueprintReadWrite, Category="Steam Integration Kit")
	int32 PortInfo = 7777;
};

USTRUCT(BlueprintType)
struct FSIK_CreateSessionExtraSettings
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category="Steam Integration Kit")
	bool bIsLanMatch = false;

	UPROPERTY(BlueprintReadWrite, Category="Steam Integration Kit")
	int32 NumberOfPrivateConnections = 0;

	UPROPERTY(BlueprintReadWrite, Category="Steam Integration Kit")
	bool bShouldAdvertise = true;

	UPROPERTY(BlueprintReadWrite, Category="Steam Integration Kit")
	bool bAllowJoinInProgress = true;

	UPROPERTY(BlueprintReadWrite, Category="Steam Integration Kit")
	bool bUsePresence = false;

	UPROPERTY(BlueprintReadWrite, Category="Steam Integration Kit")
	bool bAllowJoinViaPresence = false;
	
	UPROPERTY(BlueprintReadWrite, Category="Steam Integration Kit")
	bool bAllowJoinViaPresenceFriendsOnly = false;
};

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_CreateSession_AsyncFunction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	int32 NumberOfPublicConnections;
	TMap<FString, FSIKAttribute> SessionSettings;
	FSIKDedicatedServerSettings DedicatedServerSettings;
	FSIK_CreateSessionExtraSettings ExtraSettings;
	FName VSessionName;

	bool bDelegateCalled = false;
	UPROPERTY(BlueprintAssignable)
	FSIK_CreateSession_Delegate OnSuccess;
	UPROPERTY(BlueprintAssignable)
	FSIK_CreateSession_Delegate OnFail;

	virtual void Activate() override;

	void CreateSession();

	void OnCreateSessionCompleted(FName SessionName, bool bWasSuccessful);

	/*
	This C++ method creates a session in Steam using the selected method and sets up a callback function to handle the response.
	Documentation link: https://betide-studio.gitbook.io/Steam-integration-kit/sessions/
	For Input Parameters, please refer to the documentation link above.
	*/
	UFUNCTION(BlueprintCallable, DisplayName="Create Dedicated Server Session", meta = (BlueprintInternalUseOnly = "true",AutoCreateRefTerm = SessionSettings), Category="Steam Integration Kit || Game Functions || Sessions")
	static USIK_CreateSession_AsyncFunction* CreateEIKSession(
        TMap<FString, FSIKAttribute> SessionSettings,
        FName SessionName = "GameSession",
		int32 NumberOfPublicConnections = 15,
		FSIKDedicatedServerSettings DedicatedServerSettings = FSIKDedicatedServerSettings(), 
		FSIK_CreateSessionExtraSettings ExtraSettings = FSIK_CreateSessionExtraSettings() 
	);};
