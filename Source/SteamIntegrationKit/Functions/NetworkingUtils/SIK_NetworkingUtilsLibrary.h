// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SIK_SharedFile.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SIK_NetworkingUtilsLibrary.generated.h"

/**
 * 
 */
UCLASS()
class STEAMINTEGRATIONKIT_API USIK_NetworkingUtilsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Networking Utils")
	static void InitRelayNetworkAccess();

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Networking Utils")
	static TEnumAsByte<ESIK_SteamNetworkingAvailability> GetRelayNetworkStatus();

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Networking Utils")
	static float GetLocalPingLocation(FSIK_SteamNetworkPingLocation& OutPingLocation);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Networking Utils")
	static int32 EstimatePingTimeBetweenTwoLocations(const FSIK_SteamNetworkPingLocation& Location1, const FSIK_SteamNetworkPingLocation& Location2);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Networking Utils")
	static int32 EstimatePingTimeFromLocalHost(const FSIK_SteamNetworkPingLocation& Location);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Networking Utils")
	static FString ConvertPingLocationToString(const FSIK_SteamNetworkPingLocation& Location);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Networking Utils")
	static bool ParsePingLocationString(const FString& PingLocationString, FSIK_SteamNetworkPingLocation& OutPingLocation);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Networking Utils")
	static bool CheckPingDataUpToDate(float MaxAgeSeconds);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Networking Utils")
	static int32 GetPingToDataCenter(FSIK_SteamNetworkingPOPID PopID, FSIK_SteamNetworkingPOPID& ViaRelayPoP);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Networking Utils")
	static int32 GetDirectPingToPOP(FSIK_SteamNetworkingPOPID PopID);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Networking Utils")
	static int32 GetPOPCount();

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Networking Utils")
	static int32 GetPOPList(int32 ListSize, TArray<FSIK_SteamNetworkingPOPID>& OutPOPIDList);
	

};
