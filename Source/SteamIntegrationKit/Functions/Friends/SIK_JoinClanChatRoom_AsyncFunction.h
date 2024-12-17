// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SIK_FriendsLibrary.h"
#include "SIK_SharedFile.h"
#include "SIK_JoinClanChatRoom_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FJoinClanChatRoomDelegate);
UCLASS()
class STEAMINTEGRATIONKIT_API USIK_JoinClanChatRoom_AsyncFunction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, DisplayName="Join Steam Clan Chat Room",meta = (BlueprintInternalUseOnly = "true",Keywords="JoinClanChatRoom"), Category= "Steam Integration Kit || SDK Functions || Friends")
	static USIK_JoinClanChatRoom_AsyncFunction* JoinClanChatRoom(FSIK_SteamId ClanId);

	UPROPERTY(BlueprintAssignable)
	FJoinClanChatRoomDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FJoinClanChatRoomDelegate OnFailure;
private:
	FSIK_SteamId m_ClanId;
	virtual void Activate() override;
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	void OnJoinClanChatRoom(GameConnectedChatJoin_t* GameConnectedChatJoin, bool bIOFailure);
	SteamAPICall_t m_CallbackHandle;
	CCallResult<USIK_JoinClanChatRoom_AsyncFunction, GameConnectedChatJoin_t> m_Callback;
#endif
};
