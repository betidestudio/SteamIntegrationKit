// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SIK_FriendsLibrary.h"
#include "SIK_SharedFile.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SIK_SetPersonaName_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSetPersonaNameDelegate);
UCLASS()
class STEAMINTEGRATIONKIT_API USIK_SetPersonaName_AsyncFunction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, DisplayName="Set Steam Persona Name",meta = (BlueprintInternalUseOnly = "true",Keywords="SetPersonaName"), Category= "Steam Integration Kit || SDK Functions || Friends")
	static USIK_SetPersonaName_AsyncFunction* SetPersonaName(const FString& PersonaName);
	
	UPROPERTY(BlueprintAssignable)
	FSetPersonaNameDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FSetPersonaNameDelegate OnFailure;
private:
	FString m_PersonaName;
	void OnSetPersonaName(PersonaStateChange_t* PersonaStateChange, bool bIOFailure);
	virtual void Activate() override;
	SteamAPICall_t m_CallbackHandle;
	CCallResult<USIK_SetPersonaName_AsyncFunction, PersonaStateChange_t> m_Callback;
};
