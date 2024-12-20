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

    // Define the path and section
    FString ConfigFilePath = FConfigCacheIni::NormalizeConfigIniPath(FPaths::Combine(FPaths::SourceConfigDir(), TEXT("DefaultEngine.ini")));
	FString LocalSectionName = TEXT("OnlineSubsystemSteam");
	
    // Use FConfigFile for direct manipulation
    FConfigFile ConfigFile;
	ConfigFile.Read(*ConfigFilePath);
    if (true)
    {
    	ConfigFile.SetBool(*LocalSectionName, TEXT("bEnabled"), true);
    	ConfigFile.SetInt64(*LocalSectionName, TEXT("SteamDevAppId"), SteamDevAppId);
        ConfigFile.SetString(*LocalSectionName, TEXT("SteamDevAppId"), *FString::FromInt(SteamDevAppId));
        ConfigFile.SetString(*LocalSectionName, TEXT("SteamAppId"), *FString::FromInt(SteamAppId));
        ConfigFile.SetString(*LocalSectionName, TEXT("GameVersion"), *GameVersion);
        ConfigFile.SetString(*LocalSectionName, TEXT("bRelaunchInSteam"), bRelaunchInSteam ? TEXT("True") : TEXT("False"));
        ConfigFile.SetString(*LocalSectionName, TEXT("GameServerPort"), *FString::FromInt(GameServerPort));
        ConfigFile.SetString(*LocalSectionName, TEXT("P2PConnectionTimeout"), *FString::FromInt(P2PConnectionTimeout));
        ConfigFile.SetArray(*LocalSectionName, TEXT("MapsToCook"), MapsToCook);

        if (bUseEnvironmentVariables)
        {
            Username = FPlatformMisc::GetEnvironmentVariable(TEXT("SIK_STEAM_USERNAME"));
            Password = FPlatformMisc::GetEnvironmentVariable(TEXT("SIK_STEAM_PASSWORD"));
        }
        else
        {
            ConfigFile.SetString(*LocalSectionName, TEXT("Username"), *Username);
            ConfigFile.SetString(*LocalSectionName, TEXT("Password"), *Password);
        }

        // Handle DepotIds as an array
        TArray<FString> StringDepotIds;
        for (int32 DepotId : DepotIds)
        {
            StringDepotIds.Add(FString::FromInt(DepotId));
        }
        ConfigFile.SetArray(*LocalSectionName, TEXT("DepotIds"), StringDepotIds);

        // Additional settings
        ConfigFile.SetString(*LocalSectionName, TEXT("BranchName"), *BranchName);
        ConfigFile.SetString(*LocalSectionName, TEXT("ServerName"), *ServerName);
        ConfigFile.SetString(*LocalSectionName, TEXT("ServerDescription"), *ServerDescription);
        ConfigFile.SetString(*LocalSectionName, TEXT("ServerGameDir"), *ServerGameDir);

    	if (ConfigFile.Write(*ConfigFilePath))
        {
            UE_LOG(LogTemp, Log, TEXT("Successfully saved settings to [%s] in %s"), *LocalSectionName, *ConfigFilePath);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to write settings to %s"), *ConfigFilePath);
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to read config file: %s"), *ConfigFilePath);
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
