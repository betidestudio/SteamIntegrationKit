// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_UserStatsLibrary.h"
#include "SIK_SharedFile.h"

FString USIK_UserStatsLibrary::GetLeaderboardName(int32 LeaderboardId)
{
	if(SteamUserStats() == nullptr)
	{
		return FString();
	}
	return SteamUserStats()->GetLeaderboardName(LeaderboardId);
}

int32 USIK_UserStatsLibrary::GetLeaderboardEntryCount(int32 LeaderboardId)
{
	if(SteamUserStats() == nullptr)
	{
		return 0;
	}
	return SteamUserStats()->GetLeaderboardEntryCount(LeaderboardId);
}

ESIK_LeaderboardSortMethod USIK_UserStatsLibrary::GetLeaderboardSortMethod(int32 LeaderboardId)
{
	if(SteamUserStats() == nullptr)
	{
		return LeaderboardSortMethodNone;
	}
	return static_cast<ESIK_LeaderboardSortMethod>(SteamUserStats()->GetLeaderboardSortMethod(LeaderboardId));
}

ESIK_LeaderboardDisplayType USIK_UserStatsLibrary::GetLeaderboardDisplayType(int32 LeaderboardId)
{
	if(SteamUserStats() == nullptr)
	{
		return LeaderboardDisplayTypeNone;
	}
	return static_cast<ESIK_LeaderboardDisplayType>(SteamUserStats()->GetLeaderboardDisplayType(LeaderboardId));
}

bool USIK_UserStatsLibrary::GetAchievement(const FString& AchievementName)
{
	if(SteamUserStats() == nullptr)
	{
		return LeaderboardDisplayTypeNone;
	}
	bool bAchieved = false;
	SteamUserStats()->GetAchievement(TCHAR_TO_UTF8(*AchievementName), &bAchieved);
	return bAchieved;
}

FString USIK_UserStatsLibrary::GetAchievementName(int32 AchievementIndex)
{
	if(SteamUserStats() == nullptr)
	{
		return FString();
	}
	return SteamUserStats()->GetAchievementName(AchievementIndex);
}

void USIK_UserStatsLibrary::GetAchievementAndUnlockTime(const FString& AchievementName, bool& bAchieved,
                                                        FDateTime& UnlockTime)
{
	if(SteamUserStats() == nullptr)
	{
		return;
	}
	bAchieved = false;
	uint32 UnlockTimeInt = 0;
	SteamUserStats()->GetAchievementAndUnlockTime(TCHAR_TO_UTF8(*AchievementName), &bAchieved, &UnlockTimeInt);
	UnlockTime = FDateTime::FromUnixTimestamp(UnlockTimeInt);
}

FString USIK_UserStatsLibrary::GetAchievementDisplayAttribute(const FString& AchievementName, const FString& Key)
{
	if(SteamUserStats() == nullptr)
	{
		return FString();
	}
	return SteamUserStats()->GetAchievementDisplayAttribute(TCHAR_TO_UTF8(*AchievementName), TCHAR_TO_UTF8(*Key));
}

int32 USIK_UserStatsLibrary::GetNumOfAchievements()
{
	if(SteamUserStats() == nullptr)
	{
		return -1;
	}
	return SteamUserStats()->GetNumAchievements();
}

void USIK_UserStatsLibrary::GetAchievementIcon(const FString& AchievementName, UTexture2D*& Icon)
{
	if(SteamUserStats() == nullptr)
	{
		return;
	}

	int32 IconHandle = SteamUserStats()->GetAchievementIcon(TCHAR_TO_UTF8(*AchievementName));
	uint32 Width = 0;
	uint32 Height = 0;
	auto Res = SteamUtils()->GetImageSize(IconHandle, &Width, &Height);
	if(Width == 0 || Height == 0)
	{
		Icon = nullptr;
		return;
	}

	uint8* ImageData = new uint8[Width * Height * 4];
	bool bSuccess = SteamUtils()->GetImageRGBA(IconHandle, ImageData, Width * Height * 4);
	if (!bSuccess)
	{
		delete[] ImageData;
		return;
	}

	Icon = UTexture2D::CreateTransient(Width, Height, PF_R8G8B8A8);
	if (Icon)
	{
		void* TextureData = Icon->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
		FMemory::Memcpy(TextureData, ImageData, Width * Height * 4);
		Icon->GetPlatformData()->Mips[0].BulkData.Unlock();
		Icon->UpdateResource();
	}

	delete[] ImageData;
}

bool USIK_UserStatsLibrary::CacheCurrentStats()
{
	if(SteamUserStats() == nullptr)
	{
		return false;
	}
	return SteamUserStats()->RequestCurrentStats();
}

bool USIK_UserStatsLibrary::ClearAchievement(const FString& AchievementName)
{
	if(SteamUserStats() == nullptr)
	{
		return false;
	}
	return SteamUserStats()->ClearAchievement(TCHAR_TO_UTF8(*AchievementName));
}

bool USIK_UserStatsLibrary::SetAchievement(const FString& AchievementName)
{
	if(SteamUserStats() == nullptr)
	{
		return false;
	}
	return SteamUserStats()->SetAchievement(TCHAR_TO_UTF8(*AchievementName));
}

bool USIK_UserStatsLibrary::GetStatInt(const FString& StatName, int32& Value)
{
	if(SteamUserStats() == nullptr)
	{
		return false;
	}
	return SteamUserStats()->GetStat(TCHAR_TO_UTF8(*StatName), &Value);
}

bool USIK_UserStatsLibrary::GetStatFloat(const FString& StatName, float& Value)
{
	if(SteamUserStats() == nullptr)
	{
		return false;
	}
	return SteamUserStats()->GetStat(TCHAR_TO_UTF8(*StatName), &Value);
}

bool USIK_UserStatsLibrary::SetStatInt(const FString& StatName, int32 Value)
{
	if(SteamUserStats() == nullptr)
	{
		return false;
	}
	return SteamUserStats()->SetStat(TCHAR_TO_UTF8(*StatName), Value);
}

bool USIK_UserStatsLibrary::SetStatFloat(const FString& StatName, float Value)
{
	if(SteamUserStats() == nullptr)
	{
		return false;
	}
	return SteamUserStats()->SetStat(TCHAR_TO_UTF8(*StatName), Value);
}

bool USIK_UserStatsLibrary::GetAchievementAchievedPercent(const FString& AchievementName, float& Percent)
{
	if(SteamUserStats() == nullptr)
	{
		return false;
	}
	return SteamUserStats()->GetAchievementAchievedPercent(TCHAR_TO_UTF8(*AchievementName), &Percent);
}

bool USIK_UserStatsLibrary::UpdateAvgRateStat(const FString& StatName, float Value, float Rate)
{
	if(SteamUserStats() == nullptr)
	{
		return false;
	}
	return SteamUserStats()->UpdateAvgRateStat(TCHAR_TO_UTF8(*StatName), Value, Rate);
}

bool USIK_UserStatsLibrary::ResetAllStats(bool AchievementsToo)
{
	if(SteamUserStats() == nullptr)
	{
		return false;
	}
	return SteamUserStats()->ResetAllStats(AchievementsToo);
}

bool USIK_UserStatsLibrary::IndicateAchievementProgress(const FString& AchievementName, int32 CurProgress,
	int32 MaxProgress)
{
	if(SteamUserStats() == nullptr)
	{
		return false;
	}
	return SteamUserStats()->IndicateAchievementProgress(TCHAR_TO_UTF8(*AchievementName), CurProgress, MaxProgress);
}

bool USIK_UserStatsLibrary::GetUserAchievement(FSIK_SteamId SteamID, const FString& AchievementName, bool& bAchieved)
{
	if(SteamUserStats() == nullptr)
	{
		return false;
	}
	return SteamUserStats()->GetUserAchievement(SteamID.GetSteamID(), TCHAR_TO_UTF8(*AchievementName), &bAchieved);
}

bool USIK_UserStatsLibrary::GetUserAchievementAndUnlockTime(FSIK_SteamId SteamID, const FString& AchievementName,
	bool& bAchieved, FDateTime& UnlockTime)
{
	if(SteamUserStats() == nullptr)
	{
		return false;
	}
	bAchieved = false;
	uint32 UnlockTimeInt = 0;
	bool bResult = SteamUserStats()->GetUserAchievementAndUnlockTime(SteamID.GetSteamID(), TCHAR_TO_UTF8(*AchievementName), &bAchieved, &UnlockTimeInt);
	UnlockTime = FDateTime::FromUnixTimestamp(UnlockTimeInt);
	return bResult;
}

int32 USIK_UserStatsLibrary::GetMostAchievedAchievementInfo(FString& AchievementName,
	float& Percent, bool& bIsAchieved)
{
	if(SteamUserStats() == nullptr)
	{
		return false;
	}
	char Name[256];
	int32 Result = SteamUserStats()->GetMostAchievedAchievementInfo(TCHAR_TO_UTF8(*AchievementName), 256, &Percent, &bIsAchieved);
	AchievementName = FString(UTF8_TO_TCHAR(Name));
	return Result;
}

int32 USIK_UserStatsLibrary::GetNextMostAchievedAchievementInfo(int32 IteratorPrevious, FString& AchievementName,
	float& Percent, bool& bIsAchieved)
{
	if(SteamUserStats() == nullptr)
	{
		return false;
	}
	char Name[256];
	int32 Result = SteamUserStats()->GetNextMostAchievedAchievementInfo(IteratorPrevious, TCHAR_TO_UTF8(*AchievementName), 256, &Percent, &bIsAchieved);
	AchievementName = FString(UTF8_TO_TCHAR(Name));
	return Result;
}

int32 USIK_UserStatsLibrary::GetGlobalStatHistoryInt(const FString& StatName, TArray<int32>& Data)
{
	if(SteamUserStats() == nullptr)
	{
		return false;
	}
	double *DataArray = new double[0];
	const uint32 cubData = 0;
	const int32 DataCount = SteamUserStats()->GetGlobalStatHistory(TCHAR_TO_UTF8(*StatName), DataArray, cubData);
	Data.SetNum(cubData);
	for(int32 i = 0; i < cubData; i++)
	{
		Data[i] = DataArray[i];
	}
	delete[] DataArray;
	return DataCount;
}

int32 USIK_UserStatsLibrary::GetGlobalStatHistoryFloat(const FString& StatName, TArray<float>& Data)
{
	if(SteamUserStats() == nullptr)
	{
		return false;
	}
	double *DataArray = new double[0];
	const uint32 cubData = 0;
	const int32 DataCount = SteamUserStats()->GetGlobalStatHistory(TCHAR_TO_UTF8(*StatName), DataArray, cubData);
	Data.SetNum(cubData);
	for(int32 i = 0; i < cubData; i++)
	{
		Data[i] = DataArray[i];
	}
	delete[] DataArray;
	return DataCount;
}

bool USIK_UserStatsLibrary::GetGlobalStatInt(const FString& StatName, int64& Data)
{
	if(SteamUserStats() == nullptr)
	{
		return false;
	}
	return SteamUserStats()->GetGlobalStat(TCHAR_TO_UTF8(*StatName), &Data);
}

bool USIK_UserStatsLibrary::GetGlobalStatFloat(const FString& StatName, float& Data)
{
	if(SteamUserStats() == nullptr)
	{
		return false;
	}
	double DataDouble = 0;
	bool Ret = SteamUserStats()->GetGlobalStat(TCHAR_TO_UTF8(*StatName), &DataDouble);
	Data = DataDouble;
	return Ret;
}

bool USIK_UserStatsLibrary::RequestCurrentStats()
{
if(SteamUserStats() == nullptr)
	{
		return false;
	}
	return SteamUserStats()->RequestCurrentStats();
}

bool USIK_UserStatsLibrary::StoreStats()
{
	if(SteamUserStats() == nullptr)
	{
		return false;
	}
	return SteamUserStats()->StoreStats();
}
