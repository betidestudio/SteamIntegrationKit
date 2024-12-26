// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_SharedFile.h"
#include "Online/CoreOnline.h"
#include "Interfaces/IPluginManager.h"
#include "GameFramework/OnlineReplStructs.h"
#include "Misc/FileHelper.h"


TArray<uint8> USIK_SharedFile::ConvertStringToUint8Array(FString String)
{
	TArray<uint8> Array;
	Array.AddUninitialized(String.Len());
	for (int32 i = 0; i < String.Len(); i++) {
		Array[i] = String[i];
	}
	return Array;
}

FString USIK_SharedFile::ConvertUint8ArrayToString(TArray<uint8> Array)
{
	return FString(Array.Num(), UTF8_TO_TCHAR(Array.GetData()));
}

FString USIK_SharedFile::ConvertHexUint8ArrayToString(TArray<uint8> Array)
{
	return BytesToHex(Array.GetData(), Array.Num());
}	

TArray<uint8> USIK_SharedFile::ConvertFileToUint8Array(FString FilePath, bool& bSuccess)
{
	TArray<uint8> Array;
	bSuccess = FFileHelper::LoadFileToArray(Array, *FilePath);
	return Array;
}

int64 USIK_SharedFile::ConvertSteamIdToInt64(FSIK_SteamId SteamId)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	return SteamId.GetSteamID().ConvertToUint64();
#else
	return -11;
#endif
}

FSIK_SteamId USIK_SharedFile::ConvertInt64ToSteamId(int64 Int64)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	CSteamID SteamId;
	SteamId.SetFromUint64(Int64);
	return SteamId;
#else
	return FSIK_SteamId();
#endif
}

FSIK_AccountID USIK_SharedFile::GetAccountID(FSIK_SteamId SteamId)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	return SteamId.GetSteamID().GetAccountID();
#else
	return FSIK_AccountID();
#endif
}

TEnumAsByte<ESIK_Universe> USIK_SharedFile::GetUniverse(FSIK_SteamId SteamId)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	return static_cast<TEnumAsByte<ESIK_Universe>>(SteamId.GetSteamID().GetEUniverse());
#else
	return UniverseInvalid;
#endif
}

bool USIK_SharedFile::IsValidSteamId(FSIK_SteamId SteamId)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	return SteamId.GetSteamID().IsValid();
#else
	return false;
#endif
}

bool USIK_SharedFile::IsValidGameId(FSIK_GameID GameId)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	return GameId.GetGameID().IsValid();
#else
	return false;
#endif
}

bool USIK_SharedFile::IsEqualSteamId(FSIK_SteamId SteamId1, FSIK_SteamId SteamId2)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	return SteamId1.GetSteamID() == SteamId2.GetSteamID();
#else
	return false;
#endif
}

bool USIK_SharedFile::IsEqualGameId(FSIK_GameID GameId1, FSIK_GameID GameId2)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	return GameId1.GetGameID() == GameId2.GetGameID();
#else
	return false;
#endif
}

FSIK_SteamId USIK_SharedFile::GetSteamIdFromUniqueNetId(const FUniqueNetIdRepl& UniqueNetId)
{
	if(!UniqueNetId.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("UniqueNetId is not valid"));
		return FSIK_SteamId();
	}
	if(!UniqueNetId.GetUniqueNetId().IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("UniqueNetId is not valid"));
		return FSIK_SteamId();
	}
	return FSIK_SteamId(UniqueNetId.GetUniqueNetId().ToSharedRef()->ToString());
}
