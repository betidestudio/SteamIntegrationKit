// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_NetworkingUtilsLibrary.h"

void USIK_NetworkingUtilsLibrary::InitRelayNetworkAccess()
{
	if(!SteamNetworkingUtils())
	{
		return;
	}
	SteamNetworkingUtils()->InitRelayNetworkAccess();
}

TEnumAsByte<ESIK_SteamNetworkingAvailability> USIK_NetworkingUtilsLibrary::GetRelayNetworkStatus()
{
	if(!SteamNetworkingUtils())
	{
		return ESIK_SteamNetworkingAvailability::SteamNetworkingAvailability_Unknown;
	}
	return static_cast<ESIK_SteamNetworkingAvailability>(SteamNetworkingUtils()->GetRelayNetworkStatus(nullptr));
}

float USIK_NetworkingUtilsLibrary::GetLocalPingLocation(FSIK_SteamNetworkPingLocation& OutPingLocation)
{
	if(!SteamNetworkingUtils())
	{
		return -1.0f;
	}
	SteamNetworkPingLocation_t SteamPingLocation;
	auto Result = SteamNetworkingUtils()->GetLocalPingLocation(SteamPingLocation);
	OutPingLocation = SteamPingLocation;
	return Result;
}

int32 USIK_NetworkingUtilsLibrary::EstimatePingTimeBetweenTwoLocations(const FSIK_SteamNetworkPingLocation& Location1,
	const FSIK_SteamNetworkPingLocation& Location2)
{
	if(!SteamNetworkingUtils())
	{
		return -1;
	}
	return SteamNetworkingUtils()->EstimatePingTimeBetweenTwoLocations(Location1.GetSteamNetworkPingLocation(), Location2.GetSteamNetworkPingLocation());
}

int32 USIK_NetworkingUtilsLibrary::EstimatePingTimeFromLocalHost(const FSIK_SteamNetworkPingLocation& Location)
{
	if(!SteamNetworkingUtils())
	{
		return -1;
	}
	return SteamNetworkingUtils()->EstimatePingTimeFromLocalHost(Location.GetSteamNetworkPingLocation());
}

FString USIK_NetworkingUtilsLibrary::ConvertPingLocationToString(const FSIK_SteamNetworkPingLocation& Location)
{
	if(!SteamNetworkingUtils())
	{
		return FString();
	}
	TArray<char> Buffer;
	Buffer.SetNum(k_cchMaxSteamNetworkingPingLocationString);
	SteamNetworkingUtils()->ConvertPingLocationToString(Location.GetSteamNetworkPingLocation(),Buffer.GetData(),Buffer.Num());
	return UTF8_TO_TCHAR(Buffer.GetData());
}

bool USIK_NetworkingUtilsLibrary::ParsePingLocationString(const FString& PingLocationString,
	FSIK_SteamNetworkPingLocation& OutPingLocation)
{
	if(!SteamNetworkingUtils())
	{
		return false;
	}
	SteamNetworkPingLocation_t SteamPingLocation;
	auto Result = SteamNetworkingUtils()->ParsePingLocationString(TCHAR_TO_ANSI(*PingLocationString),SteamPingLocation);
	OutPingLocation = SteamPingLocation;
	return Result;
}

bool USIK_NetworkingUtilsLibrary::CheckPingDataUpToDate(float MaxAgeSeconds)
{
	if(!SteamNetworkingUtils())
	{
		return false;
	}
	return SteamNetworkingUtils()->CheckPingDataUpToDate(MaxAgeSeconds);
}

bool USIK_NetworkingUtilsLibrary::IsPingMeasurementInProgress()
{
	if(!SteamNetworkingUtils())
	{
		return false;
	}
	return false;
	//return SteamNetworkingUtils()->IsPingMeasurementInProgress();
}

int32 USIK_NetworkingUtilsLibrary::GetPingToDataCenter(FSIK_SteamNetworkingPOPID PopID,
	FSIK_SteamNetworkingPOPID& ViaRelayPoP)
{
	if(!SteamNetworkingUtils())
	{
		return -1;
	}
	SteamNetworkingPOPID Var_ViaRelayPoP;
	auto Result = SteamNetworkingUtils()->GetPingToDataCenter(PopID.GetSteamNetworkingPOPID(),&Var_ViaRelayPoP);
	ViaRelayPoP = Var_ViaRelayPoP;
	return Result;
}

int32 USIK_NetworkingUtilsLibrary::GetDirectPingToPOP(FSIK_SteamNetworkingPOPID PopID)
{
	if(!SteamNetworkingUtils())
	{
		return -1;
	}
	return SteamNetworkingUtils()->GetDirectPingToPOP(PopID.GetSteamNetworkingPOPID());
}

int32 USIK_NetworkingUtilsLibrary::GetPOPCount()
{
	if(!SteamNetworkingUtils())
	{
		return -1;
	}
	return SteamNetworkingUtils()->GetPOPCount();
}

int32 USIK_NetworkingUtilsLibrary::GetPOPList(int32 ListSize, TArray<FSIK_SteamNetworkingPOPID>& OutPOPIDList)
{
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
}
