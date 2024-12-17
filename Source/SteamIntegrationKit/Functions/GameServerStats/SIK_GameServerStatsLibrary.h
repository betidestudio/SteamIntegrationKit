// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SIK_SharedFile.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SIK_GameServerStatsLibrary.generated.h"

/**
 * 
 */
UCLASS()
class STEAMINTEGRATIONKIT_API USIK_GameServerStatsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/*
	Resets the unlock status of an achievement for the specified user.

	This is primarily only ever used for testing.

	You must have called RequestUserStats and it needs to return successfully via its callback prior to calling this!
	
	This call only modifies Steam's in-memory state and is very cheap. To submit the stats to the server you must call StoreUserStats.

	NOTE: This will work only on achievements that game servers are allowed to set. If the "Set By" field for this achievement is "Official GS" then only game servers that have been declared as officially controlled by you will be able to set it. To do this you must set the IP range of your official servers in the Dedicated Servers section of App Admin.
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Clear User Achievement", meta=(Keywords="ClearUserAchievement"), Category = "Steam Integration Kit || SDK Functions || Game Server Stats")
	static bool ClearUserAchievement(FSIK_SteamId SteamId, FString AchievementName);

	UFUNCTION(BlueprintCallable, DisplayName = "Get User Achievement", meta=(Keywords="GetUserAchievement"), Category = "Steam Integration Kit || SDK Functions || Game Server Stats")
	static bool GetUserAchievement(FSIK_SteamId SteamId, FString AchievementName, bool& bAchieved);

	UFUNCTION(BlueprintCallable, DisplayName = "Get Int User Stat", meta=(Keywords="GetUserStat"), Category = "Steam Integration Kit || SDK Functions || Game Server Stats")
	static bool GetIntUserStat(FSIK_SteamId SteamId, FString StatName, int32& Data);

	UFUNCTION(BlueprintCallable, DisplayName = "Get Float User Stat", meta=(Keywords="GetUserStat"), Category = "Steam Integration Kit || SDK Functions || Game Server Stats")
	static bool GetFloatUserStat(FSIK_SteamId SteamId, FString StatName, float& Data);

	UFUNCTION(BlueprintCallable, DisplayName = "Request User Stats", meta=(Keywords="RequestUserStats"), Category = "Steam Integration Kit || SDK Functions || Game Server Stats")
	static bool RequestUserStats(FSIK_SteamId SteamId);

	UFUNCTION(BlueprintCallable, DisplayName = "Set User Achievement", meta=(Keywords="SetUserAchievement"), Category = "Steam Integration Kit || SDK Functions || Game Server Stats")
	static bool SetUserAchievement(FSIK_SteamId SteamId, FString AchievementName);

	UFUNCTION(BlueprintCallable, DisplayName = "Set Int User Stat", meta=(Keywords="SetUserStat"), Category = "Steam Integration Kit || SDK Functions || Game Server Stats")
	static bool SetIntUserStat(FSIK_SteamId SteamId, FString StatName, int32 Data);

	UFUNCTION(BlueprintCallable, DisplayName = "Set Float User Stat", meta=(Keywords="SetUserStat"), Category = "Steam Integration Kit || SDK Functions || Game Server Stats")
	static bool SetFloatUserStat(FSIK_SteamId SteamId, FString StatName, float Data);

	UFUNCTION(BlueprintCallable, DisplayName = "Store User Stats", meta=(Keywords="StoreUserStats"), Category = "Steam Integration Kit || SDK Functions || Game Server Stats")
	static bool StoreUserStats(FSIK_SteamId SteamId);

	UFUNCTION(BlueprintCallable, DisplayName = "Update User Avg Rate Stat", meta=(Keywords="UpdateUserStat"), Category = "Steam Integration Kit || SDK Functions || Game Server Stats")
	static bool UpdateUserAvgRateStat(FSIK_SteamId SteamId, FString StatName, float CountThisSession, float SessionLength);
	
};
