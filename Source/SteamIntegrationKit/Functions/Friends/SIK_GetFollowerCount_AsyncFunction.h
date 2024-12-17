// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SIK_SharedFile.h"
#include "SIK_FriendsLibrary.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SIK_GetFollowerCount_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGetFollowerCount, int32, FollowerCount, FSIK_SteamId, UserSteamId);
UCLASS()
class STEAMINTEGRATIONKIT_API USIK_GetFollowerCount_AsyncFunction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, DisplayName="Get Steam Follower Count",meta = (BlueprintInternalUseOnly = "true",Keywords="GetFollowerCount"), Category= "Steam Integration Kit || SDK Functions || Friends")
	static USIK_GetFollowerCount_AsyncFunction* GetFollowerCount(const FSIK_SteamId& SteamId);
	
	UPROPERTY(BlueprintAssignable)
	FOnGetFollowerCount OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnGetFollowerCount OnFailure;

private:
	FSIK_SteamId m_SteamId;
	virtual void Activate() override;
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	void OnGetFollowerCount(FriendsGetFollowerCount_t* FriendsGetFollowerCount, bool bIOFailure);
	SteamAPICall_t m_CallbackHandle;
	CCallResult<USIK_GetFollowerCount_AsyncFunction, FriendsGetFollowerCount_t> m_Callback;
#endif
};
