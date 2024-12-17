// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SIK_CreateLeaderboard_AsyncFunction.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Runtime/Core/Public/PixelFormat.h"
#include "Serialization/BulkData.h"
#include "Engine/Texture2D.h"
#include "Engine/Texture.h"
#include "TextureResource.h"
#include "SIK_SharedFile.h"
#include "SIK_UserStatsLibrary.generated.h"

/**
 * 
 */
UCLASS()
class STEAMINTEGRATIONKIT_API USIK_UserStatsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "Steam Integration Kit || SDK Functions || User Stats")
	static FString GetLeaderboardName(int32 LeaderboardId);

	UFUNCTION(BlueprintPure, Category = "Steam Integration Kit || SDK Functions || User Stats")
	static int32 GetLeaderboardEntryCount(int32 LeaderboardId);

	UFUNCTION(BlueprintPure, Category = "Steam Integration Kit || SDK Functions || User Stats")
	static ESIK_LeaderboardSortMethod GetLeaderboardSortMethod(int32 LeaderboardId);

	UFUNCTION(BlueprintPure, Category = "Steam Integration Kit || SDK Functions || User Stats")
	static ESIK_LeaderboardDisplayType GetLeaderboardDisplayType(int32 LeaderboardId);

	UFUNCTION(BlueprintPure, Category = "Steam Integration Kit || SDK Functions || User Stats")
	static bool GetAchievement(const FString& AchievementName);

	UFUNCTION(BlueprintPure, Category = "Steam Integration Kit || SDK Functions || User Stats")
	static FString GetAchievementName(int32 AchievementIndex);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || User Stats")
	static void GetAchievementAndUnlockTime(const FString& AchievementName, bool& bAchieved, FDateTime& UnlockTime);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || User Stats")
	static FString GetAchievementDisplayAttribute(const FString& AchievementName, const FString& Key);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || User Stats")
	static int32 GetNumOfAchievements();

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || User Stats")
	static void GetAchievementIcon(const FString& AchievementName, UTexture2D*& Icon);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || User Stats")
	static bool CacheCurrentStats();

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || User Stats")
	static bool ClearAchievement(const FString& AchievementName);
	
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || User Stats")
	static bool SetAchievement(const FString& AchievementName);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || User Stats")
	static bool GetStatInt(const FString& StatName, int32& Value);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || User Stats")
	static bool GetStatFloat(const FString& StatName, float& Value);
	
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || User Stats")
	static bool SetStatInt(const FString& StatName, int32 Value);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || User Stats")
	static bool SetStatFloat(const FString& StatName, float Value);
	
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || User Stats")
	static bool GetAchievementAchievedPercent(const FString& AchievementName, float& Percent);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || User Stats")
	static bool UpdateAvgRateStat(const FString& StatName, float Value, float Rate);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || User Stats")
	static bool ResetAllStats(bool AchievementsToo);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || User Stats")
	static bool IndicateAchievementProgress(const FString& AchievementName, int32 CurProgress, int32 MaxProgress);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || User Stats")
	static bool GetUserAchievement(FSIK_SteamId SteamID, const FString& AchievementName, bool& bAchieved);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || User Stats")
	static bool GetUserAchievementAndUnlockTime(FSIK_SteamId SteamID, const FString& AchievementName, bool& bAchieved, FDateTime& UnlockTime);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || User Stats")
	static int32 GetMostAchievedAchievementInfo(FString& AchievementName, float& Percent, bool& bIsAchieved);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || User Stats")
	static int32 GetNextMostAchievedAchievementInfo(int32 IteratorPrevious,FString& AchievementName, float& Percent, bool& bIsAchieved);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || User Stats")
	static int32 GetGlobalStatHistoryInt(const FString& StatName, TArray<int32>& Data);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || User Stats")
	static int32 GetGlobalStatHistoryFloat(const FString& StatName, TArray<float>& Data);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || User Stats")
	static bool GetGlobalStatInt(const FString& StatName, int64& Data);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || User Stats")
	static bool GetGlobalStatFloat(const FString& StatName, float& Data);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || User Stats")
	static bool RequestCurrentStats();

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || User Stats")
	static bool StoreStats();
};