// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_UserSubsystem.h"

#include "Async/Async.h"

USIK_UserSubsystem::USIK_UserSubsystem()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	m_CallbackClientGameServerDeny.Register(this, &USIK_UserSubsystem::OnClientGameServerDeny);
	m_CallbackDurationControl.Register(this, &USIK_UserSubsystem::OnDurationControl);
	m_CallbackGameWebCallback.Register(this, &USIK_UserSubsystem::OnGameWebCallback);
	m_CallbackGetAuthSessionTicketResponse.Register(this, &USIK_UserSubsystem::OnGetAuthSessionTicketResponse);
#if !WITH_ENGINE_STEAM
	m_CallbackGetTicketForWebApiResponse.Register(this, &USIK_UserSubsystem::OnGetTicketForWebApiResponse);
#endif
	m_CallbackIPCFailure.Register(this, &USIK_UserSubsystem::OnIPCFailure);
	m_CallbackLicensesUpdated.Register(this, &USIK_UserSubsystem::OnLicensesUpdated);
	m_CallbackMicroTxnAuthorizationResponse.Register(this, &USIK_UserSubsystem::OnMicroTxnAuthorizationResponse);
	m_CallbackSteamServerConnectFailure.Register(this, &USIK_UserSubsystem::OnSteamServerConnectFailure);
	m_CallbackSteamServersConnected.Register(this, &USIK_UserSubsystem::OnSteamServersConnected);
	m_CallbackSteamServersDisconnected.Register(this, &USIK_UserSubsystem::OnSteamServersDisconnected);
	m_CallbackStoreAuthURLResponse.Register(this, &USIK_UserSubsystem::OnStoreAuthURLResponse);
	m_CallbackValidateAuthTicketResponse.Register(this, &USIK_UserSubsystem::OnValidateAuthTicketResponse);

 	if(IsRunningDedicatedServer())
 	{
	m_CallbackClientGameServerDeny.SetGameserverFlag();
	m_CallbackDurationControl.SetGameserverFlag();
	m_CallbackGameWebCallback.SetGameserverFlag();
	m_CallbackGetAuthSessionTicketResponse.SetGameserverFlag();
#if !WITH_ENGINE_STEAM
	m_CallbackGetTicketForWebApiResponse.SetGameserverFlag();
#endif
	m_CallbackIPCFailure.SetGameserverFlag();
	m_CallbackLicensesUpdated.SetGameserverFlag();
	m_CallbackMicroTxnAuthorizationResponse.SetGameserverFlag();
	m_CallbackSteamServerConnectFailure.SetGameserverFlag();
	m_CallbackSteamServersConnected.SetGameserverFlag();
	m_CallbackSteamServersDisconnected.SetGameserverFlag();
	m_CallbackStoreAuthURLResponse.SetGameserverFlag();
	m_CallbackValidateAuthTicketResponse.SetGameserverFlag();
}
#endif
	
}

USIK_UserSubsystem::~USIK_UserSubsystem()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	m_CallbackClientGameServerDeny.Unregister();
	m_CallbackDurationControl.Unregister();
	m_CallbackGameWebCallback.Unregister();
	m_CallbackGetAuthSessionTicketResponse.Unregister();
#if !WITH_ENGINE_STEAM
	m_CallbackGetTicketForWebApiResponse.Unregister();
#endif
	m_CallbackIPCFailure.Unregister();
	m_CallbackLicensesUpdated.Unregister();
	m_CallbackMicroTxnAuthorizationResponse.Unregister();
	m_CallbackSteamServerConnectFailure.Unregister();
	m_CallbackSteamServersConnected.Unregister();
	m_CallbackSteamServersDisconnected.Unregister();
	m_CallbackStoreAuthURLResponse.Unregister();
	m_CallbackValidateAuthTicketResponse.Unregister();
#endif
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
void USIK_UserSubsystem::OnClientGameServerDeny(ClientGameServerDeny_t *pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnClientGameServerDenyCallback.Broadcast(Param.m_uAppID, FString::Printf(TEXT("%d.%d.%d.%d"),
		(Param.m_unGameServerIP >> 24) & 0xFF,
		(Param.m_unGameServerIP >> 16) & 0xFF,
		(Param.m_unGameServerIP >> 8) & 0xFF,
		Param.m_unGameServerIP & 0xFF), Param.m_usGameServerPort, Param.m_bSecure, Param.m_uReason);
	});
}

void USIK_UserSubsystem::OnDurationControl(DurationControl_t *pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnDurationControlCallback.Broadcast(Param.m_appid);
	});
}

void USIK_UserSubsystem::OnGameWebCallback(GameWebCallback_t *pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnGameWebCallbackCallback.Broadcast(FString(UTF8_TO_TCHAR(Param.m_szURL)));
	});
}

void USIK_UserSubsystem::OnGetAuthSessionTicketResponse(GetAuthSessionTicketResponse_t *pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnGetAuthSessionTicketResponseCallback.Broadcast(Param.m_hAuthTicket);
	});
}

#if !WITH_ENGINE_STEAM || ENGINE_MINOR_VERSION > 3
void USIK_UserSubsystem::OnGetTicketForWebApiResponse(GetTicketForWebApiResponse_t *pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		// Handle GetTicketForWebApiResponse
		TArray<uint8> TicketData;
		TicketData.Append(Param.m_rgubTicket, Param.m_cubTicket);
		FString ResultToken = BytesToHex(Param.m_rgubTicket, Param.m_cubTicket);
		OnGetTicketForWebApiResponseCallback.Broadcast(Param.m_eResult, Param.m_hAuthTicket, TicketData, ResultToken);
	});
}
#endif

void USIK_UserSubsystem::OnIPCFailure(IPCFailure_t *pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnIPCFailureCallback.Broadcast(Param.m_eFailureType);
	});
}

void USIK_UserSubsystem::OnLicensesUpdated(LicensesUpdated_t *pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnLicensesUpdatedCallback.Broadcast();
	});
}	

void USIK_UserSubsystem::OnMicroTxnAuthorizationResponse(MicroTxnAuthorizationResponse_t *pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnMicroTxnAuthorizationResponseCallback.Broadcast(Param.m_unAppID, Param.m_ulOrderID, Param.m_bAuthorized != 0);
	});
}

void USIK_UserSubsystem::OnSteamServerConnectFailure(SteamServerConnectFailure_t *pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnSteamServerConnectFailureCallback.Broadcast(Param.m_eResult);
	});
}

void USIK_UserSubsystem::OnSteamServersConnected(SteamServersConnected_t *pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnSteamServersConnectedCallback.Broadcast();
	});
}

void USIK_UserSubsystem::OnSteamServersDisconnected(SteamServersDisconnected_t *pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnSteamServersDisconnectedCallback.Broadcast();
	});
}

void USIK_UserSubsystem::OnStoreAuthURLResponse(StoreAuthURLResponse_t *pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnStoreAuthURLResponseCallback.Broadcast(FString(UTF8_TO_TCHAR(Param.m_szURL)));
	});
}

void USIK_UserSubsystem::OnValidateAuthTicketResponse(ValidateAuthTicketResponse_t *pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnValidateAuthTicketResponseCallback.Broadcast(Param.m_SteamID, Param.m_eAuthSessionResponse, Param.m_OwnerSteamID);
	});
}
#endif