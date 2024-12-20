// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "HostMigrationSubsystem.h"
#include "Async/Async.h"


void UHostMigrationSubsystem::StartHostMigration(FSIK_SteamId LobbyId)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!LobbyId.GetSteamID().IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid LobbyId"));
		return;
	}
	CurrentLobbyId = LobbyId;
#endif
}

UHostMigrationSubsystem::UHostMigrationSubsystem()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	m_CallbackLobbyDataUpdate.Register(this, &UHostMigrationSubsystem::OnLobbyDataUpdateCallback);
	if(IsRunningDedicatedServer())
	{
		m_CallbackLobbyDataUpdate.SetGameserverFlag();
	}
#endif
}

UHostMigrationSubsystem::~UHostMigrationSubsystem()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	m_CallbackLobbyDataUpdate.Unregister();
#endif
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
void UHostMigrationSubsystem::OnLobbyDataUpdateCallback(LobbyDataUpdate_t* pParam)
{
	if(!SteamMatchmaking() || !SteamUser())
	{
		return;
	}
	if(CurrentLobbyId.GetSteamID().IsValid() == false)
	{
		return;
	}
	if(pParam->m_ulSteamIDLobby != pParam->m_ulSteamIDMember)
	{
		return;
	}
	if(pParam->m_ulSteamIDLobby != CurrentLobbyId.Result)
	{
		return;
	}
	if(SteamMatchmaking()->GetLobbyOwner(CurrentLobbyId.GetSteamID()) == CurrentOwner.GetSteamID())
	{
		return;
	}
	CurrentOwner = SteamMatchmaking()->GetLobbyOwner(CurrentLobbyId.GetSteamID());
	if(CurrentOwner.GetSteamID() == SteamUser()->GetSteamID())
	{
		uint32 Var_ServerIP;
		uint16 Var_ServerPort = 0;
		CSteamID Var_SteamID;
		if(SteamMatchmaking()->GetLobbyGameServer(CurrentLobbyId.GetSteamID(), &Var_ServerIP, &Var_ServerPort, &Var_SteamID))
		{
			if(Var_SteamID.IsValid())
			{
				SteamMatchmaking()->SetLobbyGameServer(CurrentLobbyId.GetSteamID(), 0, 0, CurrentOwner.GetSteamID());
				AsyncTask(ENamedThreads::GameThread, [this]()
				{
					OnHostMigration.Broadcast(CurrentLobbyId, true);
				});
			}
		}
	}
}
#endif
