// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_GameServerLibrary.h"

TEnumAsByte<ESIK_BeginAuthSessionResult> USIK_GameServerLibrary::BeginAuthSession(const TArray<uint8>& Token,
	FSIK_SteamId SteamId)
{
	if(!SteamGameServer())
	{
		return ESIK_BeginAuthSessionResult::BeginAuthSessionResultFailure;
	}
	return static_cast<ESIK_BeginAuthSessionResult>(SteamGameServer()->BeginAuthSession(Token.GetData(), Token.Num(), SteamId.GetSteamID()));
}

bool USIK_GameServerLibrary::LoggedOn()
{
	if(!SteamGameServer())
	{
		return false;
	}
	return SteamGameServer()->BLoggedOn();
}

bool USIK_GameServerLibrary::Secure()
{
	if(!SteamGameServer())
	{
		return false;
	}
	return SteamGameServer()->BSecure();
}

bool USIK_GameServerLibrary::UpdateUserData(FSIK_SteamId SteamId, const FString& PlayerName, int32 Score)
{
	if(!SteamGameServer())
	{
		return false;
	}
	return SteamGameServer()->BUpdateUserData(SteamId.GetSteamID(), TCHAR_TO_ANSI(*PlayerName), Score);
}

void USIK_GameServerLibrary::CancelAuthTicket(FSIK_AuthTicket AuthTicket)
{
	if(!SteamGameServer())
	{
		return;
	}
	SteamGameServer()->CancelAuthTicket(AuthTicket.GetAuthTicket());
}

void USIK_GameServerLibrary::ClearAllKeyValues()
{
	if(!SteamGameServer())
	{
		return;
	}
	SteamGameServer()->ClearAllKeyValues();
}

FSIK_SteamId USIK_GameServerLibrary::CreateUnauthenticatedUserConnection()
{
	if(!SteamGameServer())
	{
		return FSIK_SteamId();
	}
	return SteamGameServer()->CreateUnauthenticatedUserConnection();
}

void USIK_GameServerLibrary::EnableHeartbeats(bool bActive)
{
	//TODO: Implement this function
	if(!SteamGameServer())
	{
		return;
	}
	//SteamGameServer()->EnableHeartbeats(bActive);
}

void USIK_GameServerLibrary::EndAuthSession(FSIK_SteamId SteamId)
{
	if(!SteamGameServer())
	{
		return;
	}
	SteamGameServer()->EndAuthSession(SteamId.GetSteamID());
}

void USIK_GameServerLibrary::ForceHeartbeat()
{
	//TODO: Implement this function
}

TArray<uint8> USIK_GameServerLibrary::GetAuthSessionTicket()
{
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
}

FSIK_SteamIPAddress USIK_GameServerLibrary::GetPublicIP()
{
	if(!SteamGameServer())
	{
		return FSIK_SteamIPAddress();
	}
	return SteamGameServer()->GetPublicIP();
}

FSIK_SteamId USIK_GameServerLibrary::GetSteamID()
{
	if(!SteamGameServer())
	{
		return FSIK_SteamId();
	}
	return SteamGameServer()->GetSteamID();
}

void USIK_GameServerLibrary::LogOff()
{
	if(!SteamGameServer())
	{
		return;
	}
	SteamGameServer()->LogOff();
}

void USIK_GameServerLibrary::LogOn(const FString& Token)
{
	if(!SteamGameServer())
	{
		return;
	}
	SteamGameServer()->LogOn(TCHAR_TO_ANSI(*Token));
}

void USIK_GameServerLibrary::LogOnAnonymous()
{
	if(!SteamGameServer())
	{
		return;
	}
	SteamGameServer()->LogOnAnonymous();
}

bool USIK_GameServerLibrary::RequestUserGroupStatus(FSIK_SteamId SteamId, FSIK_SteamId GroupId)
{
	if(!SteamGameServer())
	{
		return false;
	}
	return SteamGameServer()->RequestUserGroupStatus(SteamId.GetSteamID(), GroupId.GetSteamID());
}

void USIK_GameServerLibrary::SetBotPlayerCount(int32 BotPlayerCount)
{
	if(!SteamGameServer())
	{
		return;
	}
	SteamGameServer()->SetBotPlayerCount(BotPlayerCount);
}

void USIK_GameServerLibrary::SetDedicatedServer(bool bDedicated)
{
	if(!SteamGameServer())
	{
		return;
	}
	SteamGameServer()->SetDedicatedServer(bDedicated);
}

void USIK_GameServerLibrary::SetGameData(const FString& GameData)
{
	if(!SteamGameServer())
	{
		return;
	}
	SteamGameServer()->SetGameData(TCHAR_TO_ANSI(*GameData));
}

void USIK_GameServerLibrary::SetGameDescription(const FString& GameDescription)
{
	if(!SteamGameServer())
	{
		return;
	}
	SteamGameServer()->SetGameDescription(TCHAR_TO_ANSI(*GameDescription));
}

void USIK_GameServerLibrary::SetGameTags(const FString& GameTags)
{
	if(!SteamGameServer())
	{
		return;
	}
	SteamGameServer()->SetGameTags(TCHAR_TO_ANSI(*GameTags));
}

void USIK_GameServerLibrary::SetKeyValue(const FString& Key, const FString& Value)
{
	if(!SteamGameServer())
	{
		return;
	}
	SteamGameServer()->SetKeyValue(TCHAR_TO_ANSI(*Key), TCHAR_TO_ANSI(*Value));
}

void USIK_GameServerLibrary::SetMapName(const FString& MapName)
{
	if(!SteamGameServer())
	{
		return;
	}
	SteamGameServer()->SetMapName(TCHAR_TO_ANSI(*MapName));
}

void USIK_GameServerLibrary::SetMaxPlayerCount(int32 MaxPlayerCount)
{
	if(!SteamGameServer())
	{
		return;
	}
	SteamGameServer()->SetMaxPlayerCount(MaxPlayerCount);
}

void USIK_GameServerLibrary::SetModDir(const FString& ModDir)
{
	if(!SteamGameServer())
	{
		return;
	}
	SteamGameServer()->SetModDir(TCHAR_TO_ANSI(*ModDir));
}

void USIK_GameServerLibrary::SetPasswordProtected(bool bPasswordProtected)
{
	if(!SteamGameServer())
	{
		return;
	}
	SteamGameServer()->SetPasswordProtected(bPasswordProtected);
}

void USIK_GameServerLibrary::SetProduct(const FString& Product)
{
	if(!SteamGameServer())
	{
		return;
	}
	SteamGameServer()->SetProduct(TCHAR_TO_ANSI(*Product));
}

void USIK_GameServerLibrary::SetRegion(const FString& Region)
{
	if(!SteamGameServer())
	{
		return;
	}
	SteamGameServer()->SetRegion(TCHAR_TO_ANSI(*Region));
}

void USIK_GameServerLibrary::SetServerName(const FString& ServerName)
{
	if(!SteamGameServer())
	{
		return;
	}
	SteamGameServer()->SetServerName(TCHAR_TO_ANSI(*ServerName));
}

void USIK_GameServerLibrary::SetSpectatorPort(int32 SpectatorPort)
{
	if(!SteamGameServer())
	{
		return;
	}
	SteamGameServer()->SetSpectatorPort(SpectatorPort);
}

void USIK_GameServerLibrary::SetSpectatorServerName(const FString& SpectatorServerName)
{
	if(!SteamGameServer())
	{
		return;
	}
	SteamGameServer()->SetSpectatorServerName(TCHAR_TO_ANSI(*SpectatorServerName));
}

TEnumAsByte<ESIK_UserHasLicenseForAppResult> USIK_GameServerLibrary::UserHasLicenseForApp(FSIK_SteamId SteamId, int32 AppId)
{
	if(!SteamGameServer())
	{
		return ESIK_UserHasLicenseForAppResult::UserHasLicenseResultNoAuth;
	}
	return static_cast<ESIK_UserHasLicenseForAppResult>(SteamGameServer()->UserHasLicenseForApp(SteamId.GetSteamID(), AppId));
}

bool USIK_GameServerLibrary::WasRestartRequested()
{
	if(!SteamGameServer())
	{
		return false;
	}
	return SteamGameServer()->WasRestartRequested();
}
