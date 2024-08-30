// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Launch/Resources/Version.h"
#include "SIK_SharedFile.h"
#include "SIK_SoundWaveProcedural.h"
#include "SteamIntegrationKit/Functions/GameServer/SIK_GameServerLibrary.h"

#include "SIK_UserLibrary.generated.h"

/**
 * 
 */
UCLASS()
class STEAMINTEGRATIONKIT_API USIK_UserLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, DisplayName = "Advertise Game", meta=(Keywords="AdvertiseGame"), Category="Steam Integration Kit || SDK Functions || User")
	static void AdvertiseGame(FSIK_SteamId GameServerId, FString GameServerIP, int32 GameServerPort);

	UFUNCTION(BlueprintCallable, DisplayName = "Begin Auth Session", meta=(Keywords="BeginAuthSession"), Category="Steam Integration Kit || SDK Functions || User")
	static TEnumAsByte<ESIK_BeginAuthSessionResult> BeginAuthSession(TArray<uint8> Ticket, FSIK_SteamId EntitySteamId);
	
	UFUNCTION(BlueprintCallable, DisplayName = "Is Behind NAT", meta=(Keywords="BIsBehindNAT"), Category="Steam Integration Kit || SDK Functions || User")
	static bool IsBehindNAT();

	UFUNCTION(BlueprintCallable, DisplayName = "Is Phone Identifying", meta=(Keywords="BIsPhoneIdentifying"), Category="Steam Integration Kit || SDK Functions || User")
	static bool IsPhoneIdentifying();

	UFUNCTION(BlueprintCallable, DisplayName = "Is Phone Requiring Verification", meta=(Keywords="BIsPhoneRequiringVerification"), Category="Steam Integration Kit || SDK Functions || User")
	static bool IsPhoneRequiringVerification();

	UFUNCTION(BlueprintCallable, DisplayName = "Is Phone Verified", meta=(Keywords="BIsPhoneVerified"), Category="Steam Integration Kit || SDK Functions || User")
	static bool IsPhoneVerified();

	UFUNCTION(BlueprintCallable, DisplayName = "Is Two Factor Enabled", meta=(Keywords="BIsTwoFactorEnabled"), Category="Steam Integration Kit || SDK Functions || User")
	static bool IsTwoFactorEnabled();

	UFUNCTION(BlueprintCallable, DisplayName = "Logged On", meta=(Keywords="BLoggedOn"), Category="Steam Integration Kit || SDK Functions || User")
	static bool LoggedOn();

	UFUNCTION(BlueprintPure, DisplayName = "Logged On as Pure", meta=(Keywords="BLoggedOn"), Category="Steam Integration Kit || SDK Functions || User")
	static bool LoggedOnPure();

	UFUNCTION(BlueprintCallable, DisplayName = "Cancel Auth Ticket", meta=(Keywords="CancelAuthTicket"), Category="Steam Integration Kit || SDK Functions || User")
	static void CancelAuthTicket(int32 AuthTicket);

	UFUNCTION(BlueprintCallable, DisplayName = "Decompress Voice", meta=(Keywords="DecompressVoice"), Category="Steam Integration Kit || SDK Functions || User")
	static TEnumAsByte<ESIK_VoiceResult> DecompressVoice(const TArray<uint8>& Compressed, int32 DesiredSampleRate, TArray<uint8>& Uncompressed, int32& BytesWritten);

	UFUNCTION(BlueprintCallable, DisplayName = "End Auth Session", meta=(Keywords="EndAuthSession"), Category="Steam Integration Kit || SDK Functions || User")
	static void EndAuthSession(FSIK_SteamId SteamId);

	UFUNCTION(BlueprintCallable, DisplayName = "Get Auth Session Ticket", meta=(Keywords="GetAuthSessionTicket"), Category="Steam Integration Kit || SDK Functions || User")
	static int32 GetAuthSessionTicket(TArray<uint8>& Ticket, FSIK_SteamNetworkingIdentity Identity);

	UFUNCTION(BlueprintCallable, DisplayName = "Get Auth Ticket For Web Api", meta=(Keywords="GetAuthTicketForWebApi"), Category="Steam Integration Kit || SDK Functions || User")
	static int32 GetAuthTicketForWebApi(FString Identity);

	UFUNCTION(BlueprintCallable, DisplayName = "Get Available Voice", meta=(Keywords="GetAvailableVoice"), Category="Steam Integration Kit || SDK Functions || User")
	static TEnumAsByte<ESIK_VoiceResult> GetAvailableVoice(int32& Compressed, int32& Uncompressed, int32 DesiredSampleRate);

	UFUNCTION(BlueprintCallable, DisplayName = "Get Encrypted App Ticket", meta=(Keywords="GetEncryptedAppTicket"), Category="Steam Integration Kit || SDK Functions || User")
	static bool GetEncryptedAppTicket(TArray<uint8>& Ticket);

	UFUNCTION(BlueprintCallable, DisplayName = "Get Game Badge Level", meta=(Keywords="GetGameBadgeLevel"), Category="Steam Integration Kit || SDK Functions || User")
	static int32 GetGameBadgeLevel(int32 Series, bool Foil);

	UFUNCTION(BlueprintCallable, DisplayName = "Get Player Steam Level", meta=(Keywords="GetPlayerSteamLevel"), Category="Steam Integration Kit || SDK Functions || User")
	static int32 GetPlayerSteamLevel();

	UFUNCTION(BlueprintCallable, DisplayName = "Get Steam Id", meta=(Keywords="GetSteamId"), Category="Steam Integration Kit || SDK Functions || User")
	static FSIK_SteamId GetSteamId();

	UFUNCTION(BlueprintPure, DisplayName = "Get Steam Id as Pure", meta=(Keywords="GetSteamId"), Category="Steam Integration Kit || SDK Functions || User")
	static FSIK_SteamId GetSteamIdPure();
	
	UFUNCTION(BlueprintCallable, DisplayName = "Get Voice", meta=(Keywords="GetVoice"), Category="Steam Integration Kit || SDK Functions || User")
	static TEnumAsByte<ESIK_VoiceResult> GetVoice(bool bWantCompressed, TArray<uint8>& DestBuffer, int32& BytesWritten);

	UFUNCTION(BlueprintCallable, DisplayName = "Get Voice Optimal Sample Rate", meta=(Keywords="GetVoiceOptimalSampleRate"), Category="Steam Integration Kit || SDK Functions || User")
	static int32 GetVoiceOptimalSampleRate();

	UFUNCTION(BlueprintCallable, DisplayName = "Start Voice Recording", meta=(Keywords="StartVoiceRecording"), Category="Steam Integration Kit || SDK Functions || User")
	static void StartVoiceRecording();

	UFUNCTION(BlueprintCallable, DisplayName = "Stop Voice Recording", meta=(Keywords="StopVoiceRecording"), Category="Steam Integration Kit || SDK Functions || User")
	static void StopVoiceRecording();

	UFUNCTION(BlueprintCallable, DisplayName = "User Has License For App", meta=(Keywords="UserHasLicenseForApp"), Category="Steam Integration Kit || SDK Functions || User")
	static bool UserHasLicenseForApp(FSIK_SteamId SteamId, int32 AppId);

	UFUNCTION(BlueprintCallable, DisplayName = "Construct SIK Sound Wave Procedural", meta=(Keywords="ConstructSIKSoundWaveProcedural"), Category="Steam Integration Kit || SDK Functions || User")
	static USIK_SoundWaveProcedural* ConstructSIKSoundWaveProcedural(int32 SampleRate, int32 NumChannels = 1, float Duration = 10000.0f);

	UFUNCTION(BlueprintCallable, DisplayName = "Destroy SIK Sound Wave Procedural", meta=(Keywords="DestroySIKSoundWaveProcedural"), Category="Steam Integration Kit || SDK Functions || User")
	static void DestroySIKSoundWaveProcedural(USIK_SoundWaveProcedural* SoundWaveProcedural);
};
