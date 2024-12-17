// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SIK_SharedFile.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SIK_VideoSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGetOPFSettingsResult, FSIK_AppId, AppID, TEnumAsByte<ESIK_Result>, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnGetVideoURLResult, FSIK_AppId, AppID, TEnumAsByte<ESIK_Result>, Result, FString, URL);
UCLASS()
class STEAMINTEGRATIONKIT_API USIK_VideoSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	USIK_VideoSubsystem();
	~USIK_VideoSubsystem();
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | SDK Functions | Video")
	FOnGetOPFSettingsResult OnGetOPFSettingsResult;
	
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | SDK Functions | Video")
	FOnGetVideoURLResult OnGetVideoURLResult;

	
	
private:
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	//GetOPFSettingsResult_t
	STEAM_CALLBACK_MANUAL(USIK_VideoSubsystem, OnGetOPFSettingsResultCallbck, GetOPFSettingsResult_t, m_CallbackGetOPFSettingsResult);
	//GetVideoURLResult_t
	STEAM_CALLBACK_MANUAL(USIK_VideoSubsystem, OnGetVideoURLResultCallbck, GetVideoURLResult_t, m_CallbackGetVideoURLResult);
#endif
};
