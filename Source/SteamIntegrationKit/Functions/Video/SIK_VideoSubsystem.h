// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SIK_SharedFile.h"
THIRD_PARTY_INCLUDES_START
#if WITH_ENGINE_STEAM
#include <steam/steam_api.h>
#include <steam/isteamvideo.h>
#include <steam/steam_api_common.h>
#else
#include <steam_api.h>
#include <isteamvideo.h>
#include <steam_api_common.h>
#endif
THIRD_PARTY_INCLUDES_END
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
	//GetOPFSettingsResult_t
	STEAM_CALLBACK_MANUAL(USIK_VideoSubsystem, OnGetOPFSettingsResultCallbck, GetOPFSettingsResult_t, m_CallbackGetOPFSettingsResult);
	//GetVideoURLResult_t
	STEAM_CALLBACK_MANUAL(USIK_VideoSubsystem, OnGetVideoURLResultCallbck, GetVideoURLResult_t, m_CallbackGetVideoURLResult);
};
