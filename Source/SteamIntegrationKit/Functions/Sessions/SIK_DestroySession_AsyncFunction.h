// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "SIK_DestroySession_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSIK_DestroySession_Delegate);

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_DestroySession_AsyncFunction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
public:

	bool bDelegateCalled = false;
	FName Var_SessionName;
	
	UPROPERTY(BlueprintAssignable, DisplayName="Success")
	FSIK_DestroySession_Delegate OnSuccess;
	
	UPROPERTY(BlueprintAssignable, DisplayName="Failure")
	FSIK_DestroySession_Delegate OnFail;
	
	UFUNCTION(BlueprintCallable, DisplayName="Destroy SIK Session",meta = (BlueprintInternalUseOnly = "true"), Category="Steam Integration Kit || Game Functions || Sessions")
	static USIK_DestroySession_AsyncFunction* DestroySIKSessions(FName SessionName = "GameSession");


	virtual void Activate() override;

	void DestroySession();

	void OnDestroySessionCompleted(FName SessionName, bool bWasSuccess);
};
