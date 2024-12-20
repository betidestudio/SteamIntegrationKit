// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_NetworkingUtilsLibrary.h"

void USIK_NetworkingUtilsLibrary::InitRelayNetworkAccess()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamNetworkingUtils())
	{
		return;
	}
	SteamNetworkingUtils()->InitRelayNetworkAccess();
#endif
}

TEnumAsByte<ESIK_SteamNetworkingAvailability> USIK_NetworkingUtilsLibrary::GetRelayNetworkStatus()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamNetworkingUtils())
	{
		return ESIK_SteamNetworkingAvailability::SteamNetworkingAvailability_Unknown;
	}
	return static_cast<ESIK_SteamNetworkingAvailability>(SteamNetworkingUtils()->GetRelayNetworkStatus(nullptr));
#else
	return ESIK_SteamNetworkingAvailability::SteamNetworkingAvailability_Unknown;
#endif
}

float USIK_NetworkingUtilsLibrary::GetLocalPingLocation(FSIK_SteamNetworkPingLocation& OutPingLocation)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamNetworkingUtils())
	{
		return -1.0f;
	}
	SteamNetworkPingLocation_t SteamPingLocation;
	auto Result = SteamNetworkingUtils()->GetLocalPingLocation(SteamPingLocation);
	OutPingLocation = SteamPingLocation;
	return Result;
#else
	return -1.0f;
#endif
}

int32 USIK_NetworkingUtilsLibrary::EstimatePingTimeBetweenTwoLocations(const FSIK_SteamNetworkPingLocation& Location1,
	const FSIK_SteamNetworkPingLocation& Location2)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamNetworkingUtils())
	{
		return -1;
	}
	return SteamNetworkingUtils()->EstimatePingTimeBetweenTwoLocations(Location1.GetSteamNetworkPingLocation(), Location2.GetSteamNetworkPingLocation());
#else
	return -1;
#endif
}

int32 USIK_NetworkingUtilsLibrary::EstimatePingTimeFromLocalHost(const FSIK_SteamNetworkPingLocation& Location)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamNetworkingUtils())
	{
		return -1;
	}
	return SteamNetworkingUtils()->EstimatePingTimeFromLocalHost(Location.GetSteamNetworkPingLocation());
#else
	return -1;
#endif
}

FString USIK_NetworkingUtilsLibrary::ConvertPingLocationToString(const FSIK_SteamNetworkPingLocation& Location)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamNetworkingUtils())
	{
		return FString();
	}
	TArray<char> Buffer;
	Buffer.SetNum(k_cchMaxSteamNetworkingPingLocationString);
	SteamNetworkingUtils()->ConvertPingLocationToString(Location.GetSteamNetworkPingLocation(),Buffer.GetData(),Buffer.Num());
	return UTF8_TO_TCHAR(Buffer.GetData());
#else
	return FString();
#endif
}

bool USIK_NetworkingUtilsLibrary::ParsePingLocationString(const FString& PingLocationString,
	FSIK_SteamNetworkPingLocation& OutPingLocation)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamNetworkingUtils())
	{
		return false;
	}
	SteamNetworkPingLocation_t SteamPingLocation;
	auto Result = SteamNetworkingUtils()->ParsePingLocationString(TCHAR_TO_ANSI(*PingLocationString),SteamPingLocation);
	OutPingLocation = SteamPingLocation;
	return Result;
#else
	return false;
#endif
}

bool USIK_NetworkingUtilsLibrary::CheckPingDataUpToDate(float MaxAgeSeconds)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamNetworkingUtils())
	{
		return false;
	}
	return SteamNetworkingUtils()->CheckPingDataUpToDate(MaxAgeSeconds);
#else
	return false;
#endif
}

int32 USIK_NetworkingUtilsLibrary::GetPingToDataCenter(FSIK_SteamNetworkingPOPID PopID,
	FSIK_SteamNetworkingPOPID& ViaRelayPoP)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamNetworkingUtils())
	{
		return -1;
	}
	SteamNetworkingPOPID Var_ViaRelayPoP;
	auto Result = SteamNetworkingUtils()->GetPingToDataCenter(PopID.GetSteamNetworkingPOPID(),&Var_ViaRelayPoP);
	ViaRelayPoP = Var_ViaRelayPoP;
	return Result;
#else
	return -1;
#endif
}

int32 USIK_NetworkingUtilsLibrary::GetDirectPingToPOP(FSIK_SteamNetworkingPOPID PopID)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamNetworkingUtils())
	{
		return -1;
	}
	return SteamNetworkingUtils()->GetDirectPingToPOP(PopID.GetSteamNetworkingPOPID());
#else
	return -1;
#endif
}

int32 USIK_NetworkingUtilsLibrary::GetPOPCount()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamNetworkingUtils())
	{
		return -1;
	}
	return SteamNetworkingUtils()->GetPOPCount();
#else
	return -1;
#endif
}

int32 USIK_NetworkingUtilsLibrary::GetPOPList(int32 ListSize, TArray<FSIK_SteamNetworkingPOPID>& OutPOPIDList)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamNetworkingUtils())
	{
		return -1;
	}
	SteamNetworkingPOPID* POPIDList = new SteamNetworkingPOPID[ListSize];
	auto Result = SteamNetworkingUtils()->GetPOPList(POPIDList,ListSize);
	for(int i = 0; i < ListSize; i++)
	{
		OutPOPIDList.Add(POPIDList[i]);
	}
	delete[] POPIDList;
	return Result;
#else
	return -1;
#endif
}
