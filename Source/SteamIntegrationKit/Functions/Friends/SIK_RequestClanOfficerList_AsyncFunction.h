// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SIK_FriendsLibrary.h"
#include "SIK_SharedFile.h"
#include "SIK_RequestClanOfficerList_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRequestClanOfficerList, int32, NumberOfOfficers);

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_RequestClanOfficerList_AsyncFunction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, DisplayName="Request Steam Clan Officer List",meta = (BlueprintInternalUseOnly = "true",Keywords="RequestClanOfficerList"), Category= "Steam Integration Kit || SDK Functions || Friends")
	static USIK_RequestClanOfficerList_AsyncFunction* RequestClanOfficerList(const FSIK_SteamId& ClanId);

	UPROPERTY(BlueprintAssignable)
	FOnRequestClanOfficerList OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnRequestClanOfficerList OnFailure;
	
private:
	FSIK_SteamId m_ClanId;
	virtual void Activate() override;
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	SteamAPICall_t m_CallbackHandle;
	CCallResult<USIK_RequestClanOfficerList_AsyncFunction, ClanOfficerListResponse_t> m_Callback;
	void OnRequestClanOfficerList(ClanOfficerListResponse_t* ClanOfficerListResponse, bool bIOFailure);
#endif
};
