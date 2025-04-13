// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_UserLibrary.h"

void USIK_UserLibrary::AdvertiseGame(FSIK_SteamId GameServerId, FString GameServerIP, int32 GameServerPort)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUser())
	{
		return;
	}
	FIPv4Address IP;
	FIPv4Address::Parse(GameServerIP, IP);
	SteamUser()->AdvertiseGame(GameServerId.GetSteamID(),IP.Value,GameServerPort);
#endif
}

TEnumAsByte<ESIK_BeginAuthSessionResult> USIK_UserLibrary::BeginAuthSession(TArray<uint8> Ticket,
	FSIK_SteamId EntitySteamId)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUser())
	{
		return ESIK_BeginAuthSessionResult::BeginAuthSessionResultInvalidTicket;
	}
	void *TicketData = Ticket.GetData();
	int TicketLength = Ticket.Num();
	return static_cast<TEnumAsByte<ESIK_BeginAuthSessionResult>>(SteamUser()->BeginAuthSession(TicketData, TicketLength, EntitySteamId.GetSteamID()));
#else
	return ESIK_BeginAuthSessionResult::BeginAuthSessionResultInvalidTicket;
#endif
}

bool USIK_UserLibrary::IsBehindNAT()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUser())
	{
		return false;
	}
	return SteamUser()->BIsBehindNAT();
#else
	return false;
#endif
}

bool USIK_UserLibrary::IsPhoneIdentifying()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUser())
	{
		return false;
	}
	return SteamUser()->BIsPhoneIdentifying();
#else
	return false;
#endif
}

bool USIK_UserLibrary::IsPhoneRequiringVerification()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUser())
	{
		return false;
	}
	return SteamUser()->BIsPhoneRequiringVerification();
#else
	return false;
#endif
}

bool USIK_UserLibrary::IsPhoneVerified()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUser())
	{
		return false;
	}
	return SteamUser()->BIsPhoneVerified();
#else
	return false;
#endif
}

bool USIK_UserLibrary::IsTwoFactorEnabled()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUser())
	{
		return false;
	}
	return SteamUser()->BIsTwoFactorEnabled();
#else
	return false;
#endif
}

bool USIK_UserLibrary::LoggedOn()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUser())
	{
		return false;
	}
	return SteamUser()->BLoggedOn();
#else
	return false;
#endif
}

bool USIK_UserLibrary::LoggedOnPure()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUser())
	{
		return false;
	}
	return SteamUser()->BLoggedOn();
#else
	return false;
#endif
}

void USIK_UserLibrary::CancelAuthTicket(int32 AuthTicket)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUser())
	{
		return;
	}
	SteamUser()->CancelAuthTicket(AuthTicket);
#endif
}

TEnumAsByte<ESIK_VoiceResult> USIK_UserLibrary::DecompressVoice(const TArray<uint8>& Compressed,
	int32 DesiredSampleRate, TArray<uint8>& Uncompressed, int32& BytesWritten)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if (!SteamUser())
	{
		return ESIK_VoiceResult::VoiceResultNoData;
	}

	uint32 BytesWritten2 = 0;
	Uncompressed.SetNum(1024 * 20);
	auto Result = static_cast<TEnumAsByte<ESIK_VoiceResult>>(SteamUser()->DecompressVoice(Compressed.GetData(), Compressed.Num(), Uncompressed.GetData(), Uncompressed.Num(), &BytesWritten2, DesiredSampleRate));

	if (Result == ESIK_VoiceResult::VoiceResultBufferTooSmall)
	{
		// Resize the buffer to the required size and try again
		Uncompressed.SetNum(BytesWritten2);
		Result = static_cast<TEnumAsByte<ESIK_VoiceResult>>(SteamUser()->DecompressVoice(Compressed.GetData(), Compressed.Num(),Uncompressed.GetData(), Uncompressed.Num(), &BytesWritten2, DesiredSampleRate));
	}
	BytesWritten = BytesWritten2;
	Uncompressed.SetNum(BytesWritten);
	return Result;
#else
	return ESIK_VoiceResult::VoiceResultNoData;
#endif
}


void USIK_UserLibrary::EndAuthSession(FSIK_SteamId SteamId)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUser())
	{
		return;
	}
	SteamUser()->EndAuthSession(SteamId.GetSteamID());
#endif
}

int32 USIK_UserLibrary::GetAuthSessionTicket(TArray<uint8>& Ticket, FSIK_SteamNetworkingIdentity Identity)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUser())
	{
		return 0;
	}
	uint32 TicketLength = 0;
	HAuthTicket Result;
	bool LocalCheckForSteamNetworkingIdentity = false;
	if(Identity.m_eType.GetIntValue() == k_ESteamNetworkingIdentityType_Invalid)
	{
		LocalCheckForSteamNetworkingIdentity = true;		
	}
	SteamNetworkingIdentity SteamNetworkingIdentity = Identity.GetSteamNetworkingIdentity();
	uint8 AuthToken[1024];
	uint32 AuthTokenSize = 0;
	Ticket.SetNum(1024);
#if !WITH_ENGINE_STEAM || ENGINE_MINOR_VERSION > 3
	Result = SteamUser()->GetAuthSessionTicket(AuthToken, UE_ARRAY_COUNT(AuthToken), &AuthTokenSize, LocalCheckForSteamNetworkingIdentity ? nullptr : &SteamNetworkingIdentity);
	Ticket.SetNum(AuthTokenSize);
	FMemory::Memcpy(Ticket.GetData(), AuthToken, AuthTokenSize);
	return Result;
#else
	Result = SteamUser()->GetAuthSessionTicket(Ticket.GetData(), Ticket.Num(), &TicketLength);
	Ticket.SetNum(TicketLength);
	return Result;
#endif
#else
	return 0;
#endif
}

int32 USIK_UserLibrary::GetAuthTicketForWebApi(FString Identity)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUser())
	{
		return 0;
	}
#if !WITH_ENGINE_STEAM || ENGINE_MINOR_VERSION > 3
	return SteamUser()->GetAuthTicketForWebApi(TCHAR_TO_ANSI(*Identity));
#else
	return 0;
#endif
#else
	return 0;
#endif
}

TEnumAsByte<ESIK_VoiceResult> USIK_UserLibrary::GetAvailableVoice(int32& Compressed, int32& Uncompressed,
	int32 DesiredSampleRate)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
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
#else
	return ESIK_VoiceResult::VoiceResultNoData;
#endif
}

bool USIK_UserLibrary::GetEncryptedAppTicket(TArray<uint8>& Ticket)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUser())
	{
		return false;
	}
	Ticket.SetNum(1024);
	uint32 TicketLength = 0;
	auto Result = SteamUser()->GetEncryptedAppTicket(Ticket.GetData(), Ticket.Num(), &TicketLength);
	Ticket.SetNum(TicketLength);
	return Result;
#else
	return false;
#endif
}

int32 USIK_UserLibrary::GetGameBadgeLevel(int32 Series, bool Foil)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUser())
	{
		return 0;
	}
	return SteamUser()->GetGameBadgeLevel(Series, Foil);
#else
	return 0;
#endif
}

int32 USIK_UserLibrary::GetPlayerSteamLevel()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUser())
	{
		return 0;
	}
	return SteamUser()->GetPlayerSteamLevel();
#else
	return 0;
#endif
}

FSIK_SteamId USIK_UserLibrary::GetSteamId()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
	if(!SteamUser())
	{
		return FSIK_SteamId();
	}
	return SteamUser()->GetSteamID();
#else
	return FSIK_SteamId();
#endif
}

FSIK_SteamId USIK_UserLibrary::GetSteamIdPure()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUser())
	{
		return FSIK_SteamId();
	}
	return SteamUser()->GetSteamID();
#else
	return FSIK_SteamId();
#endif
}

TEnumAsByte<ESIK_VoiceResult> USIK_UserLibrary::GetVoice(bool bWantCompressed, TArray<uint8>& DestBuffer, int32& BytesWritten)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if (!SteamUser())
	{
		return ESIK_VoiceResult::VoiceResultNoData;
	}

	uint32 AvailableVoiceBufferSize = 0;
	SteamUser()->GetAvailableVoice(&AvailableVoiceBufferSize);

	TArray<uint8> VoiceData;
	VoiceData.SetNumUninitialized(AvailableVoiceBufferSize);

	uint32 BytesWritten2 = 0;
	auto Result = static_cast<TEnumAsByte<ESIK_VoiceResult>>(SteamUser()->GetVoice(bWantCompressed, VoiceData.GetData(), VoiceData.Num(), &BytesWritten2));

	BytesWritten = BytesWritten2;

	DestBuffer.SetNum(BytesWritten);
	FMemory::Memcpy(DestBuffer.GetData(), VoiceData.GetData(), BytesWritten);

	return Result;
#else
	return ESIK_VoiceResult::VoiceResultNoData;
#endif
}


int32 USIK_UserLibrary::GetVoiceOptimalSampleRate()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUser())
	{
		return 0;
	}
	return SteamUser()->GetVoiceOptimalSampleRate();
#else
	return 0;
#endif
}

void USIK_UserLibrary::StartVoiceRecording()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUser())
	{
		return;
	}
	SteamUser()->StartVoiceRecording();
#endif
}

void USIK_UserLibrary::StopVoiceRecording()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUser())
	{
		return;
	}
	SteamUser()->StopVoiceRecording();
#endif
}

bool USIK_UserLibrary::UserHasLicenseForApp(FSIK_SteamId SteamId, int32 AppId)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUser())
	{
		return false;
	}
	if(SteamUser()->UserHasLicenseForApp(SteamId.GetSteamID(), AppId) == k_EUserHasLicenseResultHasLicense)
	{
		return true;
	}
	return false;
#else
	return false;
#endif
}

USIK_SoundWaveProcedural* USIK_UserLibrary::ConstructSIKSoundWaveProcedural(int32 SampleRate, int32 NumChannels,
	float Duration)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	USIK_SoundWaveProcedural* SoundWave = NewObject<USIK_SoundWaveProcedural>();
	SoundWave->AddToRoot();
	SoundWave->NumChannels = NumChannels;
	SoundWave->SetSampleRate(SampleRate);
	SoundWave->bLooping = false;
	SoundWave->Duration = Duration;
	SoundWave->SoundGroup = SOUNDGROUP_Voice;
	return SoundWave;
#else
	return nullptr;
#endif
}

void USIK_UserLibrary::DestroySIKSoundWaveProcedural(USIK_SoundWaveProcedural* SoundWaveProcedural)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SoundWaveProcedural)
	{
		SoundWaveProcedural->RemoveFromRoot();
	}
#endif
}
