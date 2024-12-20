// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SIK_SharedFile.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SIK_PartiesLibrary.generated.h"

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_PartiesLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, DisplayName = "Get Num Available Beacon Locations", meta=(Keywords="GetNumAvailableBeaconLocations"), Category="Steam Integration Kit || SDK Functions || Parties")
	static bool GetNumAvailableBeaconLocations(int32& NumLocations);

	UFUNCTION(BlueprintCallable, DisplayName = "Get Available Beacon Locations", meta=(Keywords="GetAvailableBeaconLocations"), Category="Steam Integration Kit || SDK Functions || Parties")
	static bool GetAvailableBeaconLocations(int32 MaxNumberOfLocations, TArray<FSIK_SteamPartyBeaconLocation>& Locations);

	UFUNCTION(BlueprintCallable, DisplayName = "On Reservation Completed", meta=(Keywords="OnReservationCompleted"), Category="Steam Integration Kit || SDK Functions || Parties")
	static void OnReservationCompleted(FSIK_PartyBeaconID BeaconID, FSIK_SteamId UserSteamID);

	UFUNCTION(BlueprintCallable, DisplayName = "Destroy Beacon", meta=(Keywords="DestroyBeacon"), Category="Steam Integration Kit || SDK Functions || Parties")
	static bool DestroyBeacon(FSIK_PartyBeaconID BeaconID);

	UFUNCTION(BlueprintCallable, DisplayName = "Get Num Active Beacons", meta=(Keywords="GetNumActiveBeacons"), Category="Steam Integration Kit || SDK Functions || Parties")
	static void GetNumActiveBeacons(int32& NumActiveBeacons);

	UFUNCTION(BlueprintCallable, DisplayName = "Get Beacon By Index", meta=(Keywords="GetBeaconByIndex"), Category="Steam Integration Kit || SDK Functions || Parties")
	static FSIK_PartyBeaconID GetBeaconByIndex(int32 Index);

	UFUNCTION(BlueprintCallable, DisplayName = "Get Beacon Details", meta=(Keywords="GetBeaconDetails"), Category="Steam Integration Kit || SDK Functions || Parties")
	static bool GetBeaconDetails(FSIK_PartyBeaconID BeaconID, FSIK_SteamId& CreatorId, FSIK_SteamPartyBeaconLocation& Location, FString& MetaData);

	UFUNCTION(BlueprintCallable, DisplayName = "Get Beacon Location Data", meta=(Keywords="GetBeaconLocationData"), Category="Steam Integration Kit || SDK Functions || Parties")
	static bool GetBeaconLocationData(FSIK_SteamPartyBeaconLocation BeaconLocation, TEnumAsByte<ESIK_SteamPartyBeaconLocationType>& LocationType, FString& LocationString);
};
