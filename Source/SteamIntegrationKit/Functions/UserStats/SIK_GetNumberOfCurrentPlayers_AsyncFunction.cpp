// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_GetNumberOfCurrentPlayers_AsyncFunction.h"

#include "Async/Async.h"

USIK_GetNumberOfCurrentPlayers_AsyncFunction* USIK_GetNumberOfCurrentPlayers_AsyncFunction::GetNumberOfCurrentPlayers()
{
	auto* Node = NewObject<USIK_GetNumberOfCurrentPlayers_AsyncFunction>();
	return Node;
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
void USIK_GetNumberOfCurrentPlayers_AsyncFunction::OnNumberOfCurrentPlayersReceived(NumberOfCurrentPlayers_t* NumberOfCurrentPlayers, bool bIOFailure)
{
	auto Param = *NumberOfCurrentPlayers;
	AsyncTask(ENamedThreads::GameThread, [this, Param,bIOFailure]()
	{
		if (bIOFailure)
		{
			OnFailure.Broadcast(0);
		}
		else
		{
			if(Param.m_bSuccess == 1)
			{
				OnSuccess.Broadcast(Param.m_cPlayers);
			}
			else
			{
				OnFailure.Broadcast(-1);
			}
		}
	});
	SetReadyToDestroy();
	MarkAsGarbage();
}
#endif

void USIK_GetNumberOfCurrentPlayers_AsyncFunction::Activate()
{
	Super::Activate();
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
	if(!SteamUserStats())
	{
		OnFailure.Broadcast(-1);
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	m_CallbackHandle = SteamUserStats()->GetNumberOfCurrentPlayers();
	if(m_CallbackHandle == k_uAPICallInvalid)
	{
		OnFailure.Broadcast(-1);
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	m_OnNumberOfCurrentPlayersReceived.Set(m_CallbackHandle, this, &USIK_GetNumberOfCurrentPlayers_AsyncFunction::OnNumberOfCurrentPlayersReceived);
#else
	OnFailure.Broadcast(-1);
	SetReadyToDestroy();
	MarkAsGarbage();
#endif
}
