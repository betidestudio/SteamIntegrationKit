// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "OnlineSubsystemUtils.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSubsystem.h"
#include "SIK_SharedFile.h"
#include "Engine/LocalPlayer.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Kismet/GameplayStatics.h"
#include "SIK_CreateLobby_AsyncFunction.generated.h"

USTRUCT(BlueprintType)
struct FSIKCreateLobbySettings
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category="Steam Integration Kit")
	bool bIsLanMatch = false;

	UPROPERTY(BlueprintReadWrite, Category="Steam Integration Kit")
	bool bAllowInvites = true;

	UPROPERTY(BlueprintReadWrite, Category="Steam Integration Kit")
	int32 NumberOfPrivateConnections = 0;

	UPROPERTY(BlueprintReadWrite, Category="Steam Integration Kit")
	bool bShouldAdvertise = true;

	UPROPERTY(BlueprintReadWrite, Category="Steam Integration Kit")
	bool bAllowJoinInProgress = true;

	UPROPERTY(BlueprintReadWrite, Category="Steam Integration Kit")
	bool bUsePresence = true;
	
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSIK_CreateLobby_Delegate, const FSIK_SteamId&, LobbyID);

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_CreateLobby_AsyncFunction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	int32 NumberOfPublicConnections;
	TMap<FString, FSIKAttribute> SessionSettings;
	FSIKCreateLobbySettings Var_CreateLobbySettings;
	bool bDelegateCalled = false;
	FName VSessionName;
	
	UPROPERTY(BlueprintAssignable, DisplayName="Success")
	FSIK_CreateLobby_Delegate OnSuccess;
	UPROPERTY(BlueprintAssignable, DisplayName="Failure")
	FSIK_CreateLobby_Delegate OnFail;

	virtual void Activate() override;

	void CreateLobby();

	void OnCreateLobbyCompleted(FName SessionName, bool bWasSuccessful);

	/*
	This function is used to create a lobby with the given settings and returns a result delegate which can be used to determine if the lobby was created successfully or not.

	*/
	UFUNCTION(BlueprintCallable, DisplayName="Create Listen Server Session",meta = (BlueprintInternalUseOnly = "true",AutoCreateRefTerm=SessionSettings), Category="Steam Integration Kit || Game Functions || Sessions")
	static USIK_CreateLobby_AsyncFunction* CreateSIKLobby(
		TMap<FString, FSIKAttribute> SessionSettings,
		FName SessionName = "GameSession",
		int32 NumberOfPublicConnections = 0,
		FSIKCreateLobbySettings ExtraSettings = FSIKCreateLobbySettings());
};
