// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_PartiesSubsystem.h"

#include "Async/Async.h"

USIK_PartiesSubsystem::USIK_PartiesSubsystem()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	m_CallbackJoinParty.Register(this, &USIK_PartiesSubsystem::OnJoinPartyCallback);
	m_CallbackCreateBeacon.Register(this, &USIK_PartiesSubsystem::OnCreateBeaconCallback);
	m_CallbackReservationNotification.Register(this, &USIK_PartiesSubsystem::OnReservationNotificationCallback);
	m_CallbackChangeNumOpenSlots.Register(this, &USIK_PartiesSubsystem::OnChangeNumOpenSlotsCallback);
	m_CallbackAvailableBeaconLocationsUpdated.Register(this, &USIK_PartiesSubsystem::OnAvailableBeaconLocationsUpdatedCallback);
	m_CallbackActiveBeaconsUpdated.Register(this, &USIK_PartiesSubsystem::OnActiveBeaconsUpdatedCallback);

 	if(IsRunningDedicatedServer())
 	{
	m_CallbackJoinParty.SetGameserverFlag();
	m_CallbackCreateBeacon.SetGameserverFlag();
	m_CallbackReservationNotification.SetGameserverFlag();
	m_CallbackChangeNumOpenSlots.SetGameserverFlag();
	m_CallbackAvailableBeaconLocationsUpdated.SetGameserverFlag();
	m_CallbackActiveBeaconsUpdated.SetGameserverFlag();

}
#endif
}

USIK_PartiesSubsystem::~USIK_PartiesSubsystem()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	m_CallbackJoinParty.Unregister();
	m_CallbackCreateBeacon.Unregister();
	m_CallbackReservationNotification.Unregister();
	m_CallbackChangeNumOpenSlots.Unregister();
	m_CallbackAvailableBeaconLocationsUpdated.Unregister();
	m_CallbackActiveBeaconsUpdated.Unregister();
#endif
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
void USIK_PartiesSubsystem::OnJoinPartyCallback(JoinPartyCallback_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		TEnumAsByte<ESIK_Result> Result = static_cast<ESIK_Result>(Param.m_eResult);
		FSIK_PartyBeaconID PartyBeaconID = Param.m_ulBeaconID;
		FSIK_SteamId BeaconOwner = Param.m_SteamIDBeaconOwner;
		FString ConnectString = FString(UTF8_TO_TCHAR(Param.m_rgchConnectString));
		OnJoinPartyResult.Broadcast(Result, PartyBeaconID, BeaconOwner, ConnectString);
	});
	
		
}

void USIK_PartiesSubsystem::OnCreateBeaconCallback(CreateBeaconCallback_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		TEnumAsByte<ESIK_Result> Result = static_cast<ESIK_Result>(Param.m_eResult);
		FSIK_PartyBeaconID BeaconID = Param.m_ulBeaconID;
		OnCreateBeaconResult.Broadcast(Result, BeaconID);
	});
}

void USIK_PartiesSubsystem::OnReservationNotificationCallback(ReservationNotificationCallback_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		FSIK_PartyBeaconID BeaconID = Param.m_ulBeaconID;
		FSIK_SteamId SteamID = Param.m_steamIDJoiner;
		OnReservationNotification.Broadcast(BeaconID, SteamID);
	});
}

void USIK_PartiesSubsystem::OnChangeNumOpenSlotsCallback(ChangeNumOpenSlotsCallback_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		TEnumAsByte<ESIK_Result> Result = static_cast<ESIK_Result>(Param.m_eResult);
		OnChangeNumOpenSlots.Broadcast(Result);
	});
}

void USIK_PartiesSubsystem::OnAvailableBeaconLocationsUpdatedCallback(AvailableBeaconLocationsUpdated_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnAvailableBeaconLocationsUpdated.Broadcast();
	});
}

void USIK_PartiesSubsystem::OnActiveBeaconsUpdatedCallback(ActiveBeaconsUpdated_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnActiveBeaconsUpdated.Broadcast();
	});
}
#endif