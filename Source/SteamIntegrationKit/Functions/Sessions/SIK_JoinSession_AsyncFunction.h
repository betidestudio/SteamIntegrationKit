// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SIK_SharedFile.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "SIK_JoinSession_AsyncFunction.generated.h"


UENUM(BlueprintType)
enum class ESIKJoinResult : uint8 {
	Success       UMETA(DisplayName="Success"),
	SessionIsFull               UMETA(DisplayName="Session Is Full"),
	SessionDoesNotExist        UMETA(DisplayName="Session Does Not Exist"),
	CouldNotRetrieveAddress        UMETA(DisplayName="Could Not Retrieve Address"),
	AlreadyInSession              UMETA(DisplayName="Already In Session"),
	UnknownError              UMETA(DisplayName="UnknownError"),
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSIK_JoinSession_Delegate, ESIKJoinResult, Result, FString, SessionJoinAddress);
/**
 * 
 */
UCLASS()
class STEAMINTEGRATIONKIT_API USIK_JoinSession_AsyncFunction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	bool bDelegateCalled = false;
	FName Var_SessionName;
	
	UPROPERTY(BlueprintAssignable, DisplayName="Success")
	FSIK_JoinSession_Delegate OnSuccess;
	
	UPROPERTY(BlueprintAssignable, DisplayName="Failure")
	FSIK_JoinSession_Delegate OnFail;

	UFUNCTION(BlueprintCallable, DisplayName="Join SIK Session",meta = (BlueprintInternalUseOnly = "true",  WorldContext = "WorldContextObject"), Category="Steam Integration Kit || Game Functions || Sessions")
	static USIK_JoinSession_AsyncFunction* JoinSIKSessions(UObject* WorldContextObject,
		FName SessionName = "GameSession",
		FSSessionFindStruct SessionToJoin = FSSessionFindStruct());

	FSSessionFindStruct Var_SessionToJoin;

	UPROPERTY()
	TObjectPtr<UObject> Var_WorldContextObject;


	void Activate() override;

	void JoinSession();

	void OnJoinSessionCompleted(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
};
