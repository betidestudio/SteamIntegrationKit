// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_SharedFile.h"

#include "Interfaces/IPluginManager.h"
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
	return SteamId.GetSteamID().ConvertToUint64();
}

FSIK_SteamId USIK_SharedFile::ConvertInt64ToSteamId(int64 Int64)
{
	CSteamID SteamId;
	SteamId.SetFromUint64(Int64);
	return SteamId;
}

FSIK_AccountID USIK_SharedFile::GetAccountID(FSIK_SteamId SteamId)
{
	return SteamId.GetSteamID().GetAccountID();
}

TEnumAsByte<ESIK_Universe> USIK_SharedFile::GetUniverse(FSIK_SteamId SteamId)
{
	return static_cast<TEnumAsByte<ESIK_Universe>>(SteamId.GetSteamID().GetEUniverse());
}

bool USIK_SharedFile::IsValidSteamId(FSIK_SteamId SteamId)
{
	return SteamId.GetSteamID().IsValid();
}

bool USIK_SharedFile::IsValidGameId(FSIK_GameID GameId)
{
	return GameId.GetGameID().IsValid();
}

bool USIK_SharedFile::IsEqualSteamId(FSIK_SteamId SteamId1, FSIK_SteamId SteamId2)
{
	return SteamId1.GetSteamID() == SteamId2.GetSteamID();
}

bool USIK_SharedFile::IsEqualGameId(FSIK_GameID GameId1, FSIK_GameID GameId2)
{
	return GameId1.GetGameID() == GameId2.GetGameID();
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
