// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIKSettings.h"

#if WITH_EDITOR
#include "UnrealEdMisc.h"
#include "Misc/MessageDialog.h"
#endif
#define LOCTEXT_NAMESPACE "SIK"

FString ProjectEngineIniPath = FPaths::ProjectConfigDir() / TEXT("DefaultEngine.ini");

USIKSettings::USIKSettings()
{
	CategoryName = TEXT("Game");
	SectionName = TEXT("Steam Integration Kit");
	if(GConfig)
	{
		bool bIsSteamEnabled = false;
		if(!GConfig->GetBool(TEXT("OnlineSubsystemSteam"), TEXT("bEnabled"), bIsSteamEnabled, ProjectEngineIniPath))
		{
			GConfig->SetBool(TEXT("OnlineSubsystemSteam"), TEXT("bEnabled"), true, ProjectEngineIniPath);
			GConfig->Flush(false, ProjectEngineIniPath);
			SaveConfig(CPF_Config, *ProjectEngineIniPath);
		}
		if(!GConfig->GetInt(TEXT("OnlineSubsystemSteam"), TEXT("SteamDevAppId"), SteamDevAppId, ProjectEngineIniPath))
		{
			GConfig->SetInt(TEXT("OnlineSubsystemSteam"), TEXT("SteamDevAppId"), SteamDevAppId, ProjectEngineIniPath);
			GConfig->Flush(false, ProjectEngineIniPath);
			SaveConfig(CPF_Config, *ProjectEngineIniPath);
		}
		if(!GConfig->GetInt(TEXT("OnlineSubsystemSteam"), TEXT("SteamAppId"), SteamAppId, ProjectEngineIniPath))
		{
			GConfig->SetInt(TEXT("OnlineSubsystemSteam"), TEXT("SteamAppId"), SteamAppId, ProjectEngineIniPath);
			GConfig->Flush(false, ProjectEngineIniPath);
			SaveConfig(CPF_Config, *ProjectEngineIniPath);
		}
		GConfig->GetString(TEXT("OnlineSubsystemSteam"), TEXT("GameVersion"), GameVersion, ProjectEngineIniPath);
		GConfig->GetBool(TEXT("OnlineSubsystemSteam"), TEXT("bRelaunchInSteam"), bRelaunchInSteam, ProjectEngineIniPath);
		GConfig->GetInt(TEXT("OnlineSubsystemSteam"), TEXT("GameServerPort"), GameServerPort, ProjectEngineIniPath);
		GConfig->GetInt(TEXT("OnlineSubsystemSteam"), TEXT("P2PConnectionTimeout"), P2PConnectionTimeout, ProjectEngineIniPath);
		GConfig->GetArray(TEXT("OnlineSubsystemSteam"), TEXT("MapsToCook"), MapsToCook, ProjectEngineIniPath);
		int32 BuildConfigurationInt = 0;
		GConfig->GetInt(TEXT("OnlineSubsystemSteam"), TEXT("BuildConfiguration"), BuildConfigurationInt, ProjectEngineIniPath);
		Username = FPlatformMisc::GetEnvironmentVariable(TEXT("SIK_STEAM_USERNAME"));
		if(!Username.IsEmpty())
		{
			bUseEnvironmentVariables = true;
			Password = FPlatformMisc::GetEnvironmentVariable(TEXT("SIK_STEAM_PASSWORD"));
		}
		else
		{
			bUseEnvironmentVariables = false;
			GConfig->GetString(TEXT("OnlineSubsystemSteam"), TEXT("Username"), Username, ProjectEngineIniPath);
			GConfig->GetString(TEXT("OnlineSubsystemSteam"), TEXT("Password"), Password, ProjectEngineIniPath);
		}
		TArray<FString> StringDepotIds;
		GConfig->GetArray(TEXT("OnlineSubsystemSteam"), TEXT("DepotIds"), StringDepotIds, ProjectEngineIniPath);
		for(const FString& StringDepotId : StringDepotIds)
		{
			DepotIds.Add(FCString::Atoi(*StringDepotId));
		}
		GConfig->GetString(TEXT("OnlineSubsystemSteam"), TEXT("ServerName"), ServerName, ProjectEngineIniPath);
		GConfig->GetString(TEXT("OnlineSubsystemSteam"), TEXT("ServerDescription"), ServerDescription, ProjectEngineIniPath);
		GConfig->GetString(TEXT("OnlineSubsystemSteam"), TEXT("ServerGameDir"), ServerGameDir, ProjectEngineIniPath);
		GConfig->GetString(TEXT("OnlineSubsystemSteam"), TEXT("BranchName"), BranchName, ProjectEngineIniPath);
	}
	bEngineInitialized = true;
}

#if WITH_EDITOR
void USIKSettings::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	if(GConfig)
	{
		GConfig->SetBool(TEXT("OnlineSubsystemSteam"), TEXT("bEnabled"), true, ProjectEngineIniPath);
		GConfig->SetInt(TEXT("OnlineSubsystemSteam"), TEXT("SteamDevAppId"), SteamDevAppId, ProjectEngineIniPath);
		GConfig->SetInt(TEXT("OnlineSubsystemSteam"), TEXT("SteamAppId"), SteamAppId, ProjectEngineIniPath);
		GConfig->SetString(TEXT("OnlineSubsystemSteam"), TEXT("GameVersion"), *GameVersion, ProjectEngineIniPath);
		GConfig->SetBool(TEXT("OnlineSubsystemSteam"), TEXT("bRelaunchInSteam"), bRelaunchInSteam, ProjectEngineIniPath);
		GConfig->SetInt(TEXT("OnlineSubsystemSteam"), TEXT("GameServerPort"), GameServerPort, ProjectEngineIniPath);
		GConfig->SetInt(TEXT("OnlineSubsystemSteam"), TEXT("P2PConnectionTimeout"), P2PConnectionTimeout, ProjectEngineIniPath);
		GConfig->SetArray(TEXT("OnlineSubsystemSteam"), TEXT("MapsToCook"), MapsToCook, ProjectEngineIniPath);
		if(FPlatformMisc::GetEnvironmentVariable(TEXT("SIK_STEAM_USERNAME")).IsEmpty())
		{
			bUseEnvironmentVariables = false;
			GConfig->SetString(TEXT("OnlineSubsystemSteam"), TEXT("Username"), *Username, ProjectEngineIniPath);
			GConfig->SetString(TEXT("OnlineSubsystemSteam"), TEXT("Password"), *Password, ProjectEngineIniPath);
		}
		else
		{
			Username = FPlatformMisc::GetEnvironmentVariable(TEXT("SIK_STEAM_USERNAME"));
			Password = FPlatformMisc::GetEnvironmentVariable(TEXT("SIK_STEAM_PASSWORD"));
			bUseEnvironmentVariables = true;
		}
		TArray<FString> StringDepotIds;
		for(int32 DepotId : DepotIds)
		{
			StringDepotIds.Add(FString::FromInt(DepotId));
		}
		GConfig->SetArray(TEXT("OnlineSubsystemSteam"), TEXT("DepotIds"), StringDepotIds, ProjectEngineIniPath);
		GConfig->SetString(TEXT("OnlineSubsystemSteam"), TEXT("BranchName"), *BranchName, ProjectEngineIniPath);
		GConfig->SetString(TEXT("OnlineSubsystemSteam"), TEXT("ServerName"), *ServerName, ProjectEngineIniPath);
		GConfig->SetString(TEXT("OnlineSubsystemSteam"), TEXT("ServerDescription"), *ServerDescription, ProjectEngineIniPath);
		GConfig->SetString(TEXT("OnlineSubsystemSteam"), TEXT("ServerGameDir"), *ServerGameDir, ProjectEngineIniPath);
		GConfig->Flush(false, ProjectEngineIniPath);
		SaveConfig(CPF_Config, *ProjectEngineIniPath);
	}
}

bool USIKSettings::CanEditChange(const FProperty* InProperty) const
{
	if(!bEngineInitialized)
	{
		return Super::CanEditChange(InProperty);	
	}
	return Super::CanEditChange(InProperty);
}
#endif
