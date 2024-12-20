// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_JoinLobby_AsyncFunction.h"

#include "Async/Async.h"

USIK_JoinLobby_AsyncFunction* USIK_JoinLobby_AsyncFunction::JoinLobby(FSIK_SteamId LobbyId)
{
	USIK_JoinLobby_AsyncFunction* JoinLobby = NewObject<USIK_JoinLobby_AsyncFunction>();
	JoinLobby->Var_LobbyId = LobbyId;
	return JoinLobby;
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
void USIK_JoinLobby_AsyncFunction::OnLobbyEnter(LobbyEnter_t* LobbyEnter, bool bIOFailure)
{
	auto Param = *LobbyEnter;
	AsyncTask(ENamedThreads::GameThread, [this, Param,bIOFailure]()
	{
		if(bIOFailure)
		{
			OnFailure.Broadcast(ESIK_Result::ResultFail, false, ESIK_ChatRoomEnterResponse::None);
		}
		else
		{
			TEnumAsByte<ESIK_ChatRoomEnterResponse> ChatRoomEnterResponse = static_cast<ESIK_ChatRoomEnterResponse>(Param.m_EChatRoomEnterResponse);
			TEnumAsByte<ESIK_Result> Result = static_cast<ESIK_Result>(Param.m_EChatRoomEnterResponse);
			if(Param.m_EChatRoomEnterResponse == k_EChatRoomEnterResponseSuccess)
			{
				OnSuccess.Broadcast(Result, Param.m_bLocked, ChatRoomEnterResponse);
			}
			else
			{
				OnFailure.Broadcast(ESIK_Result::ResultFail, false, ChatRoomEnterResponse);
			}
		}
	});
	SetReadyToDestroy();
	MarkAsGarbage();
}
#endif
	

void USIK_JoinLobby_AsyncFunction::Activate()
{
	Super::Activate();
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMatchmaking())
	{
		OnFailure.Broadcast(ESIK_Result::ResultFail, false, ESIK_ChatRoomEnterResponse::None);
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	CallbackHandle = SteamMatchmaking()->JoinLobby(Var_LobbyId.GetSteamID());
	if(CallbackHandle == k_uAPICallInvalid)
	{
		OnFailure.Broadcast(ESIK_Result::ResultFail, false, ESIK_ChatRoomEnterResponse::None);
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	CallResult.Set(CallbackHandle, this, &USIK_JoinLobby_AsyncFunction::OnLobbyEnter);
#else
	OnFailure.Broadcast(ESIK_Result::ResultFail, false, ESIK_ChatRoomEnterResponse::None);
	SetReadyToDestroy();
	MarkAsGarbage();
#endif
}
