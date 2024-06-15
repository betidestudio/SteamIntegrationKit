// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_UserLibrary.h"

void USIK_UserLibrary::AdvertiseGame(FSIK_SteamId GameServerId, FString GameServerIP, int32 GameServerPort)
{
	if(!SteamUser())
	{
		return;
	}
	FIPv4Address IP;
	FIPv4Address::Parse(GameServerIP, IP);
	SteamUser()->AdvertiseGame(GameServerId.GetSteamID(),IP.Value,GameServerPort);
}

TEnumAsByte<ESIK_BeginAuthSessionResult> USIK_UserLibrary::BeginAuthSession(TArray<uint8> Ticket,
	FSIK_SteamId EntitySteamId)
{
	if(!SteamUser())
	{
		return ESIK_BeginAuthSessionResult::BeginAuthSessionResultInvalidTicket;
	}
	void *TicketData = Ticket.GetData();
	int TicketLength = Ticket.Num();
	return static_cast<TEnumAsByte<ESIK_BeginAuthSessionResult>>(SteamUser()->BeginAuthSession(TicketData, TicketLength, EntitySteamId.GetSteamID()));
}

bool USIK_UserLibrary::IsBehindNAT()
{
	if(!SteamUser())
	{
		return false;
	}
	return SteamUser()->BIsBehindNAT();
}

bool USIK_UserLibrary::IsPhoneIdentifying()
{
	if(!SteamUser())
	{
		return false;
	}
	return SteamUser()->BIsPhoneIdentifying();
}

bool USIK_UserLibrary::IsPhoneRequiringVerification()
{
	if(!SteamUser())
	{
		return false;
	}
	return SteamUser()->BIsPhoneRequiringVerification();
}

bool USIK_UserLibrary::IsPhoneVerified()
{
	if(!SteamUser())
	{
		return false;
	}
	return SteamUser()->BIsPhoneVerified();
}

bool USIK_UserLibrary::IsTwoFactorEnabled()
{
	if(!SteamUser())
	{
		return false;
	}
	return SteamUser()->BIsTwoFactorEnabled();
}

bool USIK_UserLibrary::LoggedOn()
{
	if(!SteamUser())
	{
		return false;
	}
	return SteamUser()->BLoggedOn();
}

bool USIK_UserLibrary::LoggedOnPure()
{
	if(!SteamUser())
	{
		return false;
	}
	return SteamUser()->BLoggedOn();
}

void USIK_UserLibrary::CancelAuthTicket(int32 AuthTicket)
{
	if(!SteamUser())
	{
		return;
	}
	SteamUser()->CancelAuthTicket(AuthTicket);
}

TEnumAsByte<ESIK_VoiceResult> USIK_UserLibrary::DecompressVoice(const TArray<uint8>& Compressed,
	int32 DesiredSampleRate, TArray<uint8>& Uncompressed, int32& BytesWritten)
{
	if(!SteamUser())
	{
		return ESIK_VoiceResult::VoiceResultNoData;
	}
	TArray<uint8> UncompressedData;
	uint32 BytesWritten2 = 0;
	auto Result = static_cast<TEnumAsByte<ESIK_VoiceResult>>(SteamUser()->DecompressVoice(Compressed.GetData(), Compressed.Num(), UncompressedData.GetData(), UncompressedData.Num(), &BytesWritten2, DesiredSampleRate));
	BytesWritten = BytesWritten2;
	Uncompressed = UncompressedData;
	return Result;
}

void USIK_UserLibrary::EndAuthSession(FSIK_SteamId SteamId)
{
	if(!SteamUser())
	{
		return;
	}
	SteamUser()->EndAuthSession(SteamId.GetSteamID());
}

int32 USIK_UserLibrary::GetAuthSessionTicket(TArray<uint8>& Ticket, FSIK_SteamNetworkingIdentity Identity)
{
	if(!SteamUser())
	{
		return 0;
	}
	uint32 TicketLength = 0;
	HAuthTicket Result;
	SteamNetworkingIdentity SteamNetworkingIdentity = Identity.GetSteamNetworkingIdentity();
#if !WITH_ENGINE_STEAM || ENGINE_MINOR_VERSION > 3
	Result = SteamUser()->GetAuthSessionTicket(Ticket.GetData(), Ticket.Num(), &TicketLength, &SteamNetworkingIdentity);
#else
	Result = SteamUser()->GetAuthSessionTicket(Ticket.GetData(), Ticket.Num(), &TicketLength);
#endif
	Ticket.SetNum(TicketLength);
	return Result;
}

int32 USIK_UserLibrary::GetAuthTicketForWebApi(FString Identity)
{
	if(!SteamUser())
	{
		return 0;
	}
#if !WITH_ENGINE_STEAM
	return SteamUser()->GetAuthTicketForWebApi(TCHAR_TO_ANSI(*Identity));
#else
	return 0;
#endif
}

TEnumAsByte<ESIK_VoiceResult> USIK_UserLibrary::GetAvailableVoice(int32& Compressed, int32& Uncompressed,
	int32 DesiredSampleRate)
{
	if(!SteamUser())
	{
		return ESIK_VoiceResult::VoiceResultNoData;
	}
	uint32 Compressed2 = 0;
	uint32 Uncompressed2 = 0;
	auto Result = static_cast<TEnumAsByte<ESIK_VoiceResult>>(SteamUser()->GetAvailableVoice(&Compressed2, &Uncompressed2, DesiredSampleRate));
	Compressed = Compressed2;
	Uncompressed = Uncompressed2;
	return Result;
}

bool USIK_UserLibrary::GetEncryptedAppTicket(TArray<uint8>& Ticket)
{
	if(!SteamUser())
	{
		return false;
	}
	uint32 TicketLength = 0;
	auto Result = SteamUser()->GetEncryptedAppTicket(Ticket.GetData(), Ticket.Num(), &TicketLength);
	Ticket.SetNum(TicketLength);
	return Result;
}

int32 USIK_UserLibrary::GetGameBadgeLevel(int32 Series, bool Foil)
{
	if(!SteamUser())
	{
		return 0;
	}
	return SteamUser()->GetGameBadgeLevel(Series, Foil);
}

int32 USIK_UserLibrary::GetPlayerSteamLevel()
{
	if(!SteamUser())
	{
		return 0;
	}
	return SteamUser()->GetPlayerSteamLevel();
}

FSIK_SteamId USIK_UserLibrary::GetSteamId()
{
	if(!SteamUser())
	{
		return FSIK_SteamId();
	}
	return SteamUser()->GetSteamID();
}

FSIK_SteamId USIK_UserLibrary::GetSteamIdPure()
{
	if(!SteamUser())
	{
		return FSIK_SteamId();
	}
	return SteamUser()->GetSteamID();
}

TEnumAsByte<ESIK_VoiceResult> USIK_UserLibrary::GetVoice(bool bWantCompressed, TArray<uint8>& DestBuffer, int32& BytesWritten)
{
	if(!SteamUser())
	{
		return ESIK_VoiceResult::VoiceResultNoData;
	}
	// Create a buffer for the voice data
	TArray<uint8> VoiceData;
	VoiceData.SetNumUninitialized(8000); // Start with an 8KiB buffer
	// Create a variable to hold the number of bytes written
	uint32 BytesWritten2 = 0;
	// Call the SteamUser()->GetVoice function
	auto Result = static_cast<TEnumAsByte<ESIK_VoiceResult>>(SteamUser()->GetVoice(bWantCompressed, VoiceData.GetData(), VoiceData.Num(), &BytesWritten2));
	BytesWritten = BytesWritten2;
	DestBuffer = VoiceData;

	return Result;
}

int32 USIK_UserLibrary::GetVoiceOptimalSampleRate()
{
	if(!SteamUser())
	{
		return 0;
	}
	return SteamUser()->GetVoiceOptimalSampleRate();
}

void USIK_UserLibrary::StartVoiceRecording()
{
	if(!SteamUser())
	{
		return;
	}
	SteamUser()->StartVoiceRecording();
}

void USIK_UserLibrary::StopVoiceRecording()
{
	if(!SteamUser())
	{
		return;
	}
	SteamUser()->StopVoiceRecording();
}

bool USIK_UserLibrary::UserHasLicenseForApp(FSIK_SteamId SteamId, int32 AppId)
{
	if(!SteamUser())
	{
		return false;
	}
	if(SteamUser()->UserHasLicenseForApp(SteamId.GetSteamID(), AppId) == k_EUserHasLicenseResultHasLicense)
	{
		return true;
	}
	return false;
}
