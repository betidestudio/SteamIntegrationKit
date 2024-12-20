// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_PartiesLibrary.h"


bool USIK_PartiesLibrary::GetNumAvailableBeaconLocations(int32& NumLocations)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamParties())
	{
		return false;
	}
	uint32 NumLocations_t;
	auto Response =  SteamParties()->GetNumAvailableBeaconLocations(&NumLocations_t);
	NumLocations = NumLocations_t;
	return Response;
#else
	return false;
#endif
}

bool USIK_PartiesLibrary::GetAvailableBeaconLocations(int32 MaxNumberOfLocations, TArray<FSIK_SteamPartyBeaconLocation>& Locations)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamParties())
	{
		return false;
	}
	SteamPartyBeaconLocation_t Locations_t[50];
	TArray<FSIK_SteamPartyBeaconLocation> LocationsOut;
	auto Rsponse = SteamParties()->GetAvailableBeaconLocations(Locations_t,MaxNumberOfLocations);
	for(int i = 0; i < MaxNumberOfLocations; i++)
	{
		FSIK_SteamPartyBeaconLocation Location = FSIK_SteamPartyBeaconLocation(Locations_t[i]);
		LocationsOut.Add(Location);
	}
	Locations = LocationsOut;
	return Rsponse;
#else
	return false;
#endif
}

void USIK_PartiesLibrary::OnReservationCompleted(FSIK_PartyBeaconID BeaconID, FSIK_SteamId UserSteamID)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamParties())
	{
		return;
	}
	SteamParties()->OnReservationCompleted(BeaconID.GetPartyBeaconID(), UserSteamID.GetSteamID());
#endif
}

bool USIK_PartiesLibrary::DestroyBeacon(FSIK_PartyBeaconID BeaconID)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamParties())
	{
		return false;
	}
	return SteamParties()->DestroyBeacon(BeaconID.GetPartyBeaconID());
#else
	return false;
#endif
}

void USIK_PartiesLibrary::GetNumActiveBeacons(int32& NumActiveBeacons)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamParties())
	{
		return;
	}
	NumActiveBeacons = SteamParties()->GetNumActiveBeacons();
#endif
}

FSIK_PartyBeaconID USIK_PartiesLibrary::GetBeaconByIndex(int32 Index)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamParties())
	{
		return FSIK_PartyBeaconID();
	}
	return SteamParties()->GetBeaconByIndex(Index);
#else
	return FSIK_PartyBeaconID();
#endif
}

bool USIK_PartiesLibrary::GetBeaconDetails(FSIK_PartyBeaconID BeaconID, FSIK_SteamId& CreatorId,
	FSIK_SteamPartyBeaconLocation& Location, FString& MetaData)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamParties())
	{
		return false;
	}
	SteamPartyBeaconLocation_t Location_t;
	char MetaData_t[1024];
	CSteamID CreatorId_t;
	bool Response = SteamParties()->GetBeaconDetails(BeaconID.GetPartyBeaconID(), &CreatorId_t, &Location_t, MetaData_t, 1024);
	CreatorId = CreatorId_t;
	Location = FSIK_SteamPartyBeaconLocation(Location_t);
	MetaData = FString(MetaData_t);
	return Response;
#else
	return false;
#endif
}

bool USIK_PartiesLibrary::GetBeaconLocationData(FSIK_SteamPartyBeaconLocation BeaconLocation,
	TEnumAsByte<ESIK_SteamPartyBeaconLocationType>& LocationType, FString& LocationString)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamParties())
	{
		return false;
	}
	ESteamPartyBeaconLocationData LocationType_t = ESteamPartyBeaconLocationData::k_ESteamPartyBeaconLocationDataName;
	char LocationString_t[1024];
	bool Response = SteamParties()->GetBeaconLocationData(BeaconLocation.GetSteamPartyBeaconLocation(), LocationType_t, LocationString_t, 1024);
	LocationType = static_cast<ESIK_SteamPartyBeaconLocationType>(LocationType_t);
	LocationString = FString(LocationString_t);
	return Response;
#else
	return false;
#endif
}
