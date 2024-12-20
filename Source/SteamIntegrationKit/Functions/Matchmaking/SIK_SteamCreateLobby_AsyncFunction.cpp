// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_SteamCreateLobby_AsyncFunction.h"

#include "Async/Async.h"

USIK_SteamCreateLobby_AsyncFunction* USIK_SteamCreateLobby_AsyncFunction::CreateLobby(int32 MaxMembers,
                                                                                      TEnumAsByte<ESIK_LobbyType> LobbyType)
{
	USIK_SteamCreateLobby_AsyncFunction* CreateLobby = NewObject<USIK_SteamCreateLobby_AsyncFunction>();
	CreateLobby->Var_nMaxMembers = MaxMembers;
	CreateLobby->Var_LobbyType = LobbyType;
	return CreateLobby;
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
void USIK_SteamCreateLobby_AsyncFunction::OnCreateLobbyCallback(LobbyCreated_t* LobbyCreated, bool bIOFailure)
{
	auto Param = *LobbyCreated;
	AsyncTask(ENamedThreads::GameThread, [this, Param,bIOFailure]()
	{
		if(bIOFailure)
		{
			OnFailure.Broadcast(ESIK_Result::ResultFail, FSIK_SteamId(0));
		}
		else
		{
			TEnumAsByte<ESIK_Result> Result = static_cast<ESIK_Result>(Param.m_eResult);
			if(Param.m_eResult == k_EResultOK)
			{
				OnSuccess.Broadcast(Result, FSIK_SteamId(Param.m_ulSteamIDLobby));
			}
			else
			{
				OnFailure.Broadcast(Result, FSIK_SteamId(Param.m_ulSteamIDLobby));
			}
		}
	});
	SetReadyToDestroy();
	MarkAsGarbage();
}
#endif

void USIK_SteamCreateLobby_AsyncFunction::Activate()
{
	Super::Activate();
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMatchmaking())
	{
		OnFailure.Broadcast(ESIK_Result::ResultFail, FSIK_SteamId(0));
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	CallbackHandle = SteamMatchmaking()->CreateLobby(static_cast<ELobbyType>(Var_LobbyType.GetValue()), Var_nMaxMembers);
	if(CallbackHandle == k_uAPICallInvalid)
	{
		OnFailure.Broadcast(ESIK_Result::ResultFail, FSIK_SteamId(0));
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	OnCreateLobbyCallResult.Set(CallbackHandle, this, &USIK_SteamCreateLobby_AsyncFunction::OnCreateLobbyCallback);
#else
	OnFailure.Broadcast(ESIK_Result::ResultFail, FSIK_SteamId(0));
	SetReadyToDestroy();
	MarkAsGarbage();
#endif
}
