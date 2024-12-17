// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_NetworkingSubsystem.h"

#include "Async/Async.h"


USIK_NetworkingSubsystem::USIK_NetworkingSubsystem()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	m_CallbackP2PSessionConnectFail.Register(this, &USIK_NetworkingSubsystem::OnP2PSessionConnectFailCallbck);
	m_CallbackP2PSessionRequest.Register(this, &USIK_NetworkingSubsystem::OnP2PSessionRequestCallback);

 	if(IsRunningDedicatedServer())
 	{
	m_CallbackP2PSessionConnectFail.SetGameserverFlag();
	m_CallbackP2PSessionRequest.SetGameserverFlag();
}
#endif
}

USIK_NetworkingSubsystem::~USIK_NetworkingSubsystem()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	m_CallbackP2PSessionConnectFail.Unregister();
	m_CallbackP2PSessionRequest.Unregister();
#endif
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
void USIK_NetworkingSubsystem::OnP2PSessionConnectFailCallbck(P2PSessionConnectFail_t* pCallback)
{
	auto Param = *pCallback;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		FSIK_SteamId SteamID = Param.m_steamIDRemote;
		TEnumAsByte<ESIK_P2PSessionError> Error = static_cast<ESIK_P2PSessionError>(Param.m_eP2PSessionError);
		OnP2PSessionConnectFail.Broadcast(SteamID, Error);
	});
}

void USIK_NetworkingSubsystem::OnP2PSessionRequestCallback(P2PSessionRequest_t* pCallback)
{
	auto Param = *pCallback;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		FSIK_SteamId SteamID = Param.m_steamIDRemote;
		OnP2PSessionRequest.Broadcast(SteamID);
	});
}
#endif