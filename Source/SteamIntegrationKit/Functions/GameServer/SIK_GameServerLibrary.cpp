// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_GameServerLibrary.h"

TEnumAsByte<ESIK_BeginAuthSessionResult> USIK_GameServerLibrary::BeginAuthSession(const TArray<uint8>& Token,
	FSIK_SteamId SteamId)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamGameServer())
	{
		return ESIK_BeginAuthSessionResult::BeginAuthSessionResultFailure;
	}
	return static_cast<ESIK_BeginAuthSessionResult>(SteamGameServer()->BeginAuthSession(Token.GetData(), Token.Num(), SteamId.GetSteamID()));
#else
	return ESIK_BeginAuthSessionResult::BeginAuthSessionResultFailure;
#endif
}

bool USIK_GameServerLibrary::LoggedOn()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamGameServer())
	{
		return false;
	}
	return SteamGameServer()->BLoggedOn();
#else
	return false;
#endif
}

bool USIK_GameServerLibrary::Secure()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamGameServer())
	{
		return false;
	}
	return SteamGameServer()->BSecure();
#else
	return false;
#endif
}

bool USIK_GameServerLibrary::UpdateUserData(FSIK_SteamId SteamId, const FString& PlayerName, int32 Score)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamGameServer())
	{
		return false;
	}
	return SteamGameServer()->BUpdateUserData(SteamId.GetSteamID(), TCHAR_TO_ANSI(*PlayerName), Score);
#else
	return false;
#endif
}

void USIK_GameServerLibrary::CancelAuthTicket(FSIK_AuthTicket AuthTicket)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamGameServer())
	{
		return;
	}
	SteamGameServer()->CancelAuthTicket(AuthTicket.GetAuthTicket());
#endif
}

void USIK_GameServerLibrary::ClearAllKeyValues()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamGameServer())
	{
		return;
	}
	SteamGameServer()->ClearAllKeyValues();
#endif
}

FSIK_SteamId USIK_GameServerLibrary::CreateUnauthenticatedUserConnection()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamGameServer())
	{
		return FSIK_SteamId();
	}
	return SteamGameServer()->CreateUnauthenticatedUserConnection();
#else
	return FSIK_SteamId();
#endif
}

void USIK_GameServerLibrary::EndAuthSession(FSIK_SteamId SteamId)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamGameServer())
	{
		return;
	}
	SteamGameServer()->EndAuthSession(SteamId.GetSteamID());
#endif
}

TArray<uint8> USIK_GameServerLibrary::GetAuthSessionTicket()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamGameServer())
	{
		return TArray<uint8>();
	}
	void* Ticket = nullptr;
	int cbMaxTicket = 0;
	uint32* pcbTicket = nullptr;
	SteamNetworkingIdentity Identity;
	Identity.m_eType = ESteamNetworkingIdentityType::k_ESteamNetworkingIdentityType_IPAddress;
	SteamNetworkingIPAddr IPAddr;
	IPAddr.SetIPv4(0,0);
	Identity.SetIPAddr(IPAddr);
	uint32 TicketSize;
#if !WITH_ENGINE_STEAM || ENGINE_MINOR_VERSION > 3
	TicketSize = SteamGameServer()->GetAuthSessionTicket(Ticket, cbMaxTicket, pcbTicket, &Identity);
#else
	TicketSize = SteamGameServer()->GetAuthSessionTicket(Ticket, cbMaxTicket, &TicketSize);
#endif
	TArray<uint8> TicketArray;
	TicketArray.SetNum(TicketSize);
	FMemory::Memcpy(TicketArray.GetData(), Ticket, TicketSize);
	return TicketArray;
#else
	return TArray<uint8>();
#endif
}

FSIK_SteamIPAddress USIK_GameServerLibrary::GetPublicIP()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamGameServer())
	{
		return FSIK_SteamIPAddress();
	}
	return SteamGameServer()->GetPublicIP();
#else
	return FSIK_SteamIPAddress();
#endif
}

FSIK_SteamId USIK_GameServerLibrary::GetSteamID()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamGameServer())
	{
		return FSIK_SteamId();
	}
	return SteamGameServer()->GetSteamID();
#else
	return FSIK_SteamId();
#endif
}

void USIK_GameServerLibrary::LogOff()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamGameServer())
	{
		return;
	}
	SteamGameServer()->LogOff();
#endif
}

void USIK_GameServerLibrary::LogOn(const FString& Token)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamGameServer())
	{
		return;
	}
	SteamGameServer()->LogOn(TCHAR_TO_ANSI(*Token));
#endif
}

void USIK_GameServerLibrary::LogOnAnonymous()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamGameServer())
	{
		return;
	}
	SteamGameServer()->LogOnAnonymous();
#endif
}

bool USIK_GameServerLibrary::RequestUserGroupStatus(FSIK_SteamId SteamId, FSIK_SteamId GroupId)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamGameServer())
	{
		return false;
	}
	return SteamGameServer()->RequestUserGroupStatus(SteamId.GetSteamID(), GroupId.GetSteamID());
#else
	return false;
#endif
}

void USIK_GameServerLibrary::SetBotPlayerCount(int32 BotPlayerCount)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamGameServer())
	{
		return;
	}
	SteamGameServer()->SetBotPlayerCount(BotPlayerCount);
#endif
}

void USIK_GameServerLibrary::SetDedicatedServer(bool bDedicated)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamGameServer())
	{
		return;
	}
	SteamGameServer()->SetDedicatedServer(bDedicated);
#endif
}

void USIK_GameServerLibrary::SetGameData(const FString& GameData)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamGameServer())
	{
		return;
	}
	SteamGameServer()->SetGameData(TCHAR_TO_ANSI(*GameData));
#endif
}

void USIK_GameServerLibrary::SetGameDescription(const FString& GameDescription)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamGameServer())
	{
		return;
	}
	SteamGameServer()->SetGameDescription(TCHAR_TO_ANSI(*GameDescription));
#endif
}

void USIK_GameServerLibrary::SetGameTags(const FString& GameTags)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamGameServer())
	{
		return;
	}
	SteamGameServer()->SetGameTags(TCHAR_TO_ANSI(*GameTags));
#endif
}

void USIK_GameServerLibrary::SetKeyValue(const FString& Key, const FString& Value)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamGameServer())
	{
		return;
	}
	SteamGameServer()->SetKeyValue(TCHAR_TO_ANSI(*Key), TCHAR_TO_ANSI(*Value));
#endif
}

void USIK_GameServerLibrary::SetMapName(const FString& MapName)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamGameServer())
	{
		return;
	}
	SteamGameServer()->SetMapName(TCHAR_TO_ANSI(*MapName));
#endif
}

void USIK_GameServerLibrary::SetMaxPlayerCount(int32 MaxPlayerCount)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamGameServer())
	{
		return;
	}
	SteamGameServer()->SetMaxPlayerCount(MaxPlayerCount);
#endif
}

void USIK_GameServerLibrary::SetModDir(const FString& ModDir)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamGameServer())
	{
		return;
	}
	SteamGameServer()->SetModDir(TCHAR_TO_ANSI(*ModDir));
#endif
}

void USIK_GameServerLibrary::SetPasswordProtected(bool bPasswordProtected)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamGameServer())
	{
		return;
	}
	SteamGameServer()->SetPasswordProtected(bPasswordProtected);
#endif
}

void USIK_GameServerLibrary::SetProduct(const FString& Product)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamGameServer())
	{
		return;
	}
	SteamGameServer()->SetProduct(TCHAR_TO_ANSI(*Product));
#endif
}

void USIK_GameServerLibrary::SetRegion(const FString& Region)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamGameServer())
	{
		return;
	}
	SteamGameServer()->SetRegion(TCHAR_TO_ANSI(*Region));
#endif
}

void USIK_GameServerLibrary::SetServerName(const FString& ServerName)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamGameServer())
	{
		return;
	}
	SteamGameServer()->SetServerName(TCHAR_TO_ANSI(*ServerName));
#endif
}

void USIK_GameServerLibrary::SetSpectatorPort(int32 SpectatorPort)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamGameServer())
	{
		return;
	}
	SteamGameServer()->SetSpectatorPort(SpectatorPort);
#endif
}

void USIK_GameServerLibrary::SetSpectatorServerName(const FString& SpectatorServerName)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamGameServer())
	{
		return;
	}
	SteamGameServer()->SetSpectatorServerName(TCHAR_TO_ANSI(*SpectatorServerName));
#endif
}

TEnumAsByte<ESIK_UserHasLicenseForAppResult> USIK_GameServerLibrary::UserHasLicenseForApp(FSIK_SteamId SteamId, int32 AppId)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamGameServer())
	{
		return ESIK_UserHasLicenseForAppResult::UserHasLicenseResultNoAuth;
	}
	return static_cast<ESIK_UserHasLicenseForAppResult>(SteamGameServer()->UserHasLicenseForApp(SteamId.GetSteamID(), AppId));
#else
	return ESIK_UserHasLicenseForAppResult::UserHasLicenseResultNoAuth;
#endif
}

bool USIK_GameServerLibrary::WasRestartRequested()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamGameServer())
	{
		return false;
	}
	return SteamGameServer()->WasRestartRequested();
#else
	return false;
#endif
}
