// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SIK_SharedFile.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SIK_AppSubsystem.generated.h"

UENUM(BlueprintType)
enum ESIK_RegisterActivationCodeResult
{
	RegisterActivationCodeResultOK = 0 UMETA(DisplayName = "OK"),
	RegisterActivationCodeResultFail = 1 UMETA(DisplayName = "Fail"),
	RegisterActivationCodeResultAlreadyRegistered = 2 UMETA(DisplayName = "Already Registered"),
	RegisterActivationCodeResultTimeout = 3 UMETA(DisplayName = "Timeout"),
	RegisterActivationCodeAlreadyOwned = 4 UMETA(DisplayName = "Already Owned")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDlcInstalledDelegate, int32, AppID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FFileDetailsDelegate, TEnumAsByte<ESIK_Result>, Result, int32, FileSize, int32, Flags, const TArray<uint8>&, SHA);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNewUrlLaunchParametersDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FTimedTrialStatusDelegate, int32, AppID, bool, bIsOffline, int32, SecondsAllowed, int32, SecondsPlayed);

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_AppSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	USIK_AppSubsystem();
	~USIK_AppSubsystem();


	//Triggered after the current user gains ownership of DLC and that DLC is installed.
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || Apps || Callbacks")
	FDlcInstalledDelegate OnDlcInstalled;

	//Called after requesting the details of a specific file.
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || Apps")
	FFileDetailsDelegate OnFileDetails;

	//Posted after the user executes a steam url with command line or query parameters such as steam://run/<appid>//?param1=value1;param2=value2;param3=value3; while the game is already running. The new params can be queried with GetLaunchCommandLine and GetLaunchQueryParam.
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || Apps")
	FNewUrlLaunchParametersDelegate OnNewUrlLaunchParameters;

	//Sent every minute when a appID is owned via a timed trial.
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || Apps")
	FTimedTrialStatusDelegate OnTimedTrialStatus;
	
private:
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	STEAM_CALLBACK_MANUAL(USIK_AppSubsystem, OnDlcInstalledCallbck, DlcInstalled_t, m_CallbackDlcInstalled);
	STEAM_CALLBACK_MANUAL(USIK_AppSubsystem, OnFileDetailsCallbck, FileDetailsResult_t, m_CallbackFileDetails);
	STEAM_CALLBACK_MANUAL(USIK_AppSubsystem, OnNewUrlLaunchParametersCallbck, NewUrlLaunchParameters_t, m_CallbackNewUrlLaunchParameters);
	STEAM_CALLBACK_MANUAL(USIK_AppSubsystem, OnTimedTrialStatusCallbck, TimedTrialStatus_t, m_CallbackTimedTrialStatus);
#endif
};
