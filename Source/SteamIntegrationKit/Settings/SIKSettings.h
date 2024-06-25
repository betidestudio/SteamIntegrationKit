// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Engine/RuntimeOptionsBase.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "Misc/MessageDialog.h"
#include "Misc/ConfigCacheIni.h"
#include "Engine/DataAsset.h"
#include "Runtime/Launch/Resources/Version.h"
#include "Engine/DeveloperSettings.h"
#include "SIKSettings.generated.h"

UENUM(BlueprintType)
enum ESIK_BuildConfiguration
{
	/** Unknown build configuration. */
	UnknownBuild1 = 0 UMETA(DisplayName = "Unknown"),

	/** Debug build. */
	Debug1 = 1 UMETA(DisplayName = "Debug"),

	/** DebugGame build. */
	DebugGame1 = 2 UMETA(DisplayName = "DebugGame"),

	/** Development build. */
	Development1 = 3 UMETA(DisplayName = "Development"),

	/** Shipping build. */
	Shipping1 = 4 UMETA(DisplayName = "Shipping"),

	/** Test build. */
	Test1 = 5 UMETA(DisplayName = "Test"),
};

UCLASS(meta=(DisplayName="Steam Integration Kit"))
class STEAMINTEGRATIONKIT_API USIKSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	USIKSettings();

	UPROPERTY(EditAnywhere, Category = "Basic Settings")
	FString GameVersion = "1.0.0.0";

	UPROPERTY(EditAnywhere, Category = "Basic Settings")
	int32 SteamAppId = 480;
	
	UPROPERTY(EditAnywhere, Category = "Basic Settings")
	int32 SteamDevAppId = 480;

	UPROPERTY(EditAnywhere, Category = "Basic Settings")
	bool bRelaunchInSteam = false;
	
	UPROPERTY(EditAnywhere, Category = "Basic Settings")
	int32 GameServerPort = 7777;

	UPROPERTY(EditAnywhere, Category = "Basic Settings")
	int32 P2PConnectionTimeout = 120;

	UPROPERTY(EditAnywhere, Category = "One Click Deploy")
	TEnumAsByte<ESIK_BuildConfiguration> BuildConfiguration = ESIK_BuildConfiguration::Development1;

	UPROPERTY(EditAnywhere, Category = "One Click Deploy")
	TArray<FString> MapsToCook;

	UPROPERTY(EditAnywhere, Category = "One Click Deploy")
	TArray<int32> DepotIds;

	//Beta branch name to automatically set live after successful build, none if empty. Note that the 'default' branch can not be set live automatically. That must be done through the App Admin panel.
	UPROPERTY(EditAnywhere, Category = "One Click Deploy")
	FString BranchName;

	UPROPERTY(EditAnywhere, Category = "Deployer Account Information")
	FString Username;

	UPROPERTY(EditAnywhere, Category = "Deployer Account Information")
	FString Password;

	UPROPERTY(EditAnywhere, Category = "Game Server Settings")
	FString ServerName;

	UPROPERTY(EditAnywhere, Category = "Game Server Settings")
	FString ServerDescription;

	UPROPERTY(EditAnywhere, Category = "Game Server Settings")
	FString ServerModDir;
	


private:
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	
};
