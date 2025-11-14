// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIKSettings.h"

#if WITH_EDITOR
#include "UnrealEdMisc.h"
#include "Misc/MessageDialog.h"
#include "HAL/PlatformMisc.h"
#include "HAL/PlatformFileManager.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#endif

#if PLATFORM_WINDOWS
    #include "Windows/AllowWindowsPlatformTypes.h"
    #include <windows.h>
    #include "Windows/HideWindowsPlatformTypes.h"
#elif PLATFORM_LINUX || PLATFORM_MAC
    #include <stdlib.h>
#endif
#define LOCTEXT_NAMESPACE "SIK"

FString ProjectEngineIniPath = FPaths::ProjectConfigDir() / TEXT("DefaultEngine.ini");

static bool SetEnvironmentVariable_CrossPlatform(const TCHAR* VariableName, const TCHAR* Value)
{
    UE_LOG(LogTemp, Log, TEXT("Setting environment variable: %s"), VariableName);
    
#if PLATFORM_WINDOWS
    BOOL bResult = ::SetEnvironmentVariableW(VariableName, Value);
    if (bResult)
    {
        UE_LOG(LogTemp, Log, TEXT("Successfully set environment variable %s on Windows"), VariableName);
        return true;
    }
    else
    {
        DWORD dwError = GetLastError();
        UE_LOG(LogTemp, Error, TEXT("Failed to set environment variable %s on Windows. Error code: %d"), VariableName, dwError);
        return false;
    }
#elif PLATFORM_LINUX || PLATFORM_MAC
    // setenv returns 0 on success, non-zero on failure
    int result = setenv(TCHAR_TO_UTF8(VariableName), TCHAR_TO_UTF8(Value), 1);
    if (result == 0)
    {
        UE_LOG(LogTemp, Log, TEXT("Successfully set environment variable %s on %s"), VariableName, 
#if PLATFORM_LINUX
               TEXT("Linux")
#else
               TEXT("Mac")
#endif
        );
        return true;
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to set environment variable %s on %s. Error code: %d"), VariableName,
#if PLATFORM_LINUX
               TEXT("Linux"),
#else
               TEXT("Mac"),
#endif
               result);
        return false;
    }
#else
    // Unsupported platform
    UE_LOG(LogTemp, Warning, TEXT("SetEnvironmentVariable not supported on this platform"));
    return false;
#endif
}

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
		// Username and Password are ONLY read from environment variables for security
		// They are never read from INI files
		FString EnvUsername = FPlatformMisc::GetEnvironmentVariable(TEXT("SIK_STEAM_USERNAME"));
		FString EnvPassword = FPlatformMisc::GetEnvironmentVariable(TEXT("SIK_STEAM_PASSWORD"));
		
		UE_LOG(LogTemp, Log, TEXT("Constructor: Raw environment variable check:"));
		UE_LOG(LogTemp, Log, TEXT("Constructor: SIK_STEAM_USERNAME length: %d"), EnvUsername.Len());
		UE_LOG(LogTemp, Log, TEXT("Constructor: SIK_STEAM_PASSWORD length: %d"), EnvPassword.Len());
		UE_LOG(LogTemp, Log, TEXT("Constructor: Loaded Username from environment: '%s'"), *EnvUsername);
		UE_LOG(LogTemp, Log, TEXT("Constructor: Loaded Password from environment: %s"), EnvPassword.IsEmpty() ? TEXT("(empty)") : TEXT("(set)"));
		
#if PLATFORM_WINDOWS
		// Try Windows Registry as fallback for system environment variables
		if (EnvUsername.IsEmpty() || EnvPassword.IsEmpty())
		{
			UE_LOG(LogTemp, Log, TEXT("Constructor: Trying Windows Registry fallback for environment variables"));
			
			HKEY hKey;
			LONG result = RegOpenKeyExW(HKEY_CURRENT_USER, TEXT("Environment"), 0, KEY_READ, &hKey);
			if (result == ERROR_SUCCESS)
			{
				wchar_t Buffer[1024];
				DWORD BufferSize = sizeof(Buffer);
				
				// Try to read SIK_STEAM_USERNAME from registry
				if (EnvUsername.IsEmpty())
				{
					result = RegQueryValueExW(hKey, TEXT("SIK_STEAM_USERNAME"), nullptr, nullptr, (LPBYTE)Buffer, &BufferSize);
					if (result == ERROR_SUCCESS)
					{
						EnvUsername = FString(Buffer);
						UE_LOG(LogTemp, Log, TEXT("Constructor: Found Username in registry: '%s'"), *EnvUsername);
					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("Constructor: Registry query for SIK_STEAM_USERNAME failed with error: %d"), result);
					}
				}
				
				// Try to read SIK_STEAM_PASSWORD from registry
				if (EnvPassword.IsEmpty())
				{
					BufferSize = sizeof(Buffer);
					result = RegQueryValueExW(hKey, TEXT("SIK_STEAM_PASSWORD"), nullptr, nullptr, (LPBYTE)Buffer, &BufferSize);
					if (result == ERROR_SUCCESS)
					{
						EnvPassword = FString(Buffer);
						UE_LOG(LogTemp, Log, TEXT("Constructor: Found Password in registry: %s"), EnvPassword.IsEmpty() ? TEXT("(empty)") : TEXT("(set)"));
					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("Constructor: Registry query for SIK_STEAM_PASSWORD failed with error: %d"), result);
					}
				}
				
				RegCloseKey(hKey);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Constructor: Failed to open Environment registry key with error: %d"), result);
			}
		}
#endif
		
		Username = EnvUsername;
		Password = EnvPassword;
		bUseEnvironmentVariables = true;
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

    // Handle Username/Password changes - write to environment variables
    FName PropertyName = (PropertyChangedEvent.Property != nullptr) 
        ? PropertyChangedEvent.Property->GetFName() 
        : NAME_None;
    
    if (PropertyName == GET_MEMBER_NAME_CHECKED(USIKSettings, Username))
    {
        if (!Username.IsEmpty())
        {
            bool bSuccess = SetEnvironmentVariable_CrossPlatform(TEXT("SIK_STEAM_USERNAME"), *Username);
            if (bSuccess)
            {
                UE_LOG(LogTemp, Log, TEXT("Username successfully written to SIK_STEAM_USERNAME environment variable"));
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Failed to set SIK_STEAM_USERNAME environment variable"));
            }
        }
    }
    else if (PropertyName == GET_MEMBER_NAME_CHECKED(USIKSettings, Password))
    {
        if (!Password.IsEmpty())
        {
            bool bSuccess = SetEnvironmentVariable_CrossPlatform(TEXT("SIK_STEAM_PASSWORD"), *Password);
            if (bSuccess)
            {
                UE_LOG(LogTemp, Log, TEXT("Password successfully written to SIK_STEAM_PASSWORD environment variable"));
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Failed to set SIK_STEAM_PASSWORD environment variable"));
            }
        }
    }
#if WITH_EDITOR
    else if (PropertyName == GET_MEMBER_NAME_CHECKED(USIKSettings, bSaveToSystem))
    {
        if (bSaveToSystem)
        {
            SaveCredentialsToSystem();
            bSaveToSystem = false; // Reset the button
        }
    }
#endif
    else
    {
        // For other property changes, refresh credentials from environment variables
        Username = FPlatformMisc::GetEnvironmentVariable(TEXT("SIK_STEAM_USERNAME"));
        Password = FPlatformMisc::GetEnvironmentVariable(TEXT("SIK_STEAM_PASSWORD"));
    }

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

        // Username and Password are NOT written to INI files for security
        // They are only stored in environment variables

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

void USIKSettings::PostInitProperties()
{
	Super::PostInitProperties();
	
	UE_LOG(LogTemp, Log, TEXT("PostInitProperties: Called"));
	
	// Load credentials from environment variables every time the settings are initialized
	// This ensures they're loaded even when the engine restarts and reuses cached instances
	FString EnvUsername = FPlatformMisc::GetEnvironmentVariable(TEXT("SIK_STEAM_USERNAME"));
	FString EnvPassword = FPlatformMisc::GetEnvironmentVariable(TEXT("SIK_STEAM_PASSWORD"));
	
	if (!EnvUsername.IsEmpty())
	{
		Username = EnvUsername;
		UE_LOG(LogTemp, Log, TEXT("PostInitProperties: Loaded Username from environment variable: %s"), *Username);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PostInitProperties: SIK_STEAM_USERNAME environment variable is empty"));
	}
	
	if (!EnvPassword.IsEmpty())
	{
		Password = EnvPassword;
		UE_LOG(LogTemp, Log, TEXT("PostInitProperties: Loaded Password from environment variable"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PostInitProperties: SIK_STEAM_PASSWORD environment variable is empty"));
	}
}

#if WITH_EDITOR
void USIKSettings::SaveCredentialsToSystem()
{
    UE_LOG(LogTemp, Log, TEXT("SaveCredentialsToSystem button clicked!"));
    
    if (Username.IsEmpty() && Password.IsEmpty())
    {
        UE_LOG(LogTemp, Warning, TEXT("No credentials entered"));
        FMessageDialog::Open(EAppMsgType::Ok, 
            LOCTEXT("NoCredentials", "Please enter Username and/or Password before saving to system."));
        return;
    }

    // Confirm with user
    EAppReturnType::Type Response = FMessageDialog::Open(
        EAppMsgType::YesNo,
        LOCTEXT("ConfirmSaveCredentials", 
            "This will save your Steam credentials to system environment variables.\n\n"
            "Username and Password will be accessible system-wide.\n"
            "You will need to restart the Editor for changes to take full effect.\n\n"
            "Continue?")
    );

    if (Response == EAppReturnType::No)
    {
        return;
    }

    bool bSuccess = false;

#if PLATFORM_WINDOWS
    bSuccess = SaveCredentialsToSystem_Windows();
#elif PLATFORM_MAC
    bSuccess = SaveCredentialsToSystem_Mac();
#elif PLATFORM_LINUX
    bSuccess = SaveCredentialsToSystem_Linux();
#else
    FMessageDialog::Open(EAppMsgType::Ok, 
        LOCTEXT("UnsupportedPlatform", "This platform is not supported for automatic credential saving."));
    return;
#endif

    if (bSuccess)
    {
        FMessageDialog::Open(EAppMsgType::Ok, 
            LOCTEXT("SaveSuccess", 
                "Credentials saved successfully!\n\n"
                "Please restart the Unreal Editor for changes to take effect."));
    }
    else
    {
        FMessageDialog::Open(EAppMsgType::Ok, 
            LOCTEXT("SaveFailed", 
                "Failed to save credentials. Check the Output Log for details."));
    }
}

bool USIKSettings::SaveCredentialsToSystem_Windows()
{
    UE_LOG(LogTemp, Log, TEXT("SaveCredentialsToSystem_Windows called"));
    
    // Build the commands
    TArray<FString> Commands;
    
    if (!Username.IsEmpty())
    {
        Commands.Add(FString::Printf(TEXT("setx SIK_STEAM_USERNAME \"%s\""), *Username));
    }
    
    if (!Password.IsEmpty())
    {
        Commands.Add(FString::Printf(TEXT("setx SIK_STEAM_PASSWORD \"%s\""), *Password));
    }

    // Create a temporary batch file
    FString BatchContent = TEXT("@echo off\n");
    for (const FString& Command : Commands)
    {
        BatchContent += Command + TEXT("\n");
    }
    BatchContent += TEXT("echo.\n");
    BatchContent += TEXT("echo Environment variables set successfully!\n");
    BatchContent += TEXT("echo Please restart Unreal Editor for changes to take effect.\n");
    BatchContent += TEXT("pause\n");

    // Save to temp file
    FString TempDir = FPaths::ProjectSavedDir() / TEXT("Temp");
    FString BatchFilePath = TempDir / TEXT("SetSteamCredentials.bat");
    
    // Ensure directory exists
    IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
    if (!PlatformFile.DirectoryExists(*TempDir))
    {
        PlatformFile.CreateDirectory(*TempDir);
    }

    // Write batch file
    if (!FFileHelper::SaveStringToFile(BatchContent, *BatchFilePath, FFileHelper::EEncodingOptions::ForceAnsi))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create batch file at: %s"), *BatchFilePath);
        return false;
    }

    UE_LOG(LogTemp, Log, TEXT("Created batch file at: %s"), *BatchFilePath);

    // Execute the batch file
    FString FullPath = IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(*BatchFilePath);
    
    FPlatformProcess::CreateProc(
        TEXT("cmd.exe"),
        *FString::Printf(TEXT("/c \"%s\""), *FullPath),
        true,  // bLaunchDetached
        false, // bLaunchHidden
        false, // bLaunchReallyHidden
        nullptr,
        0,
        nullptr,
        nullptr
    );

    return true;
}

bool USIKSettings::SaveCredentialsToSystem_Mac()
{
    // For macOS, we'll modify ~/.zshrc or ~/.bash_profile
    FString HomeDir = FPlatformMisc::GetEnvironmentVariable(TEXT("HOME"));
    FString ShellConfigFile;
    
    // Check which shell config to use
    FString ZshrcPath = HomeDir / TEXT(".zshrc");
    FString BashProfilePath = HomeDir / TEXT(".bash_profile");
    
    if (FPaths::FileExists(ZshrcPath))
    {
        ShellConfigFile = ZshrcPath;
    }
    else if (FPaths::FileExists(BashProfilePath))
    {
        ShellConfigFile = BashProfilePath;
    }
    else
    {
        // Default to .zshrc (macOS default since Catalina)
        ShellConfigFile = ZshrcPath;
    }

    // Create temp script
    FString TempDir = FPaths::ProjectSavedDir() / TEXT("Temp");
    FString ScriptPath = TempDir / TEXT("SetSteamCredentials.sh");
    
    IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
    if (!PlatformFile.DirectoryExists(*TempDir))
    {
        PlatformFile.CreateDirectory(*TempDir);
    }

    // Build script content
    FString ScriptContent = FString::Printf(
        TEXT("#!/bin/bash\n"
             "echo ''\n"
             "echo 'Adding Steam credentials to %s...'\n"
             "echo ''\n"
             "echo '# Steam Integration Kit - Added by Unreal Editor' >> %s\n"
             "%s"
             "echo 'export SIK_STEAM_USERNAME=\"%s\"' >> %s\n"
             "%s"
             "echo 'export SIK_STEAM_PASSWORD=\"%s\"' >> %s\n"
             "echo ''\n"
             "echo 'Credentials added successfully!'\n"
             "echo 'Please restart your terminal and Unreal Editor.'\n"
             "read -p 'Press Enter to continue...'\n"),
        *ShellConfigFile,
        *ShellConfigFile,
        Username.IsEmpty() ? TEXT("") : TEXT(""),
        *Username,
        *ShellConfigFile,
        Password.IsEmpty() ? TEXT("") : TEXT(""),
        *Password,
        *ShellConfigFile
    );

    if (!FFileHelper::SaveStringToFile(ScriptContent, *ScriptPath))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create script file"));
        return false;
    }

    // Make executable
    FPlatformProcess::ExecProcess(TEXT("/bin/chmod"), *FString::Printf(TEXT("+x \"%s\""), *ScriptPath), nullptr, nullptr, nullptr);

    // Open terminal and execute
    FString Command = FString::Printf(TEXT("-a Terminal \"%s\""), *ScriptPath);
    FPlatformProcess::CreateProc(TEXT("/usr/bin/open"), *Command, true, false, false, nullptr, 0, nullptr, nullptr);

    return true;
}

bool USIKSettings::SaveCredentialsToSystem_Linux()
{
    FString HomeDir = FPlatformMisc::GetEnvironmentVariable(TEXT("HOME"));
    FString BashrcPath = HomeDir / TEXT(".bashrc");

    // Build script
    FString ScriptContent = TEXT("#!/bin/bash\n\n");
    ScriptContent += TEXT("echo 'Adding Steam credentials to ~/.bashrc...'\n");
    ScriptContent += TEXT("echo ''\n");
    ScriptContent += TEXT("echo '# Steam Integration Kit - Added by Unreal Editor' >> ~/.bashrc\n");
    
    if (!Username.IsEmpty())
    {
        ScriptContent += FString::Printf(TEXT("echo 'export SIK_STEAM_USERNAME=\"%s\"' >> ~/.bashrc\n"), *Username);
    }
    
    if (!Password.IsEmpty())
    {
        ScriptContent += FString::Printf(TEXT("echo 'export SIK_STEAM_PASSWORD=\"%s\"' >> ~/.bashrc\n"), *Password);
    }
    
    ScriptContent += TEXT("echo ''\n");
    ScriptContent += TEXT("echo 'Credentials added successfully!'\n");
    ScriptContent += TEXT("echo 'Please restart your terminal and Unreal Editor.'\n");
    ScriptContent += TEXT("read -p 'Press Enter to continue...'\n");

    // Save script
    FString TempDir = FPaths::ProjectSavedDir() / TEXT("Temp");
    FString ScriptPath = TempDir / TEXT("SetSteamCredentials.sh");
    
    IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
    if (!PlatformFile.DirectoryExists(*TempDir))
    {
        PlatformFile.CreateDirectory(*TempDir);
    }

    if (!FFileHelper::SaveStringToFile(ScriptContent, *ScriptPath))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create script file"));
        return false;
    }

    // Make executable
    FPlatformProcess::ExecProcess(TEXT("/bin/chmod"), *FString::Printf(TEXT("+x \"%s\""), *ScriptPath), nullptr, nullptr, nullptr);

    // Try to open with common terminal emulators
    TArray<FString> Terminals = {TEXT("gnome-terminal"), TEXT("konsole"), TEXT("xterm")};
    
    for (const FString& Terminal : Terminals)
    {
        FString Command = FString::Printf(TEXT("-- bash -c \"%s\""), *ScriptPath);
        FProcHandle Handle = FPlatformProcess::CreateProc(*Terminal, *Command, true, false, false, nullptr, 0, nullptr, nullptr);
        
        if (Handle.IsValid())
        {
            return true;
        }
    }

    UE_LOG(LogTemp, Error, TEXT("Could not find suitable terminal emulator"));
    return false;
}
#endif // WITH_EDITOR
#endif