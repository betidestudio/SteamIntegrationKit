// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SIK_SharedFile.h"
#include "SIK_GetDurationControl_AsyncFunction.generated.h"

UENUM(BlueprintType)
enum ESIK_DurationControlNotification
{
	DurationControlNotification_None = 0 UMETA(DisplayName = "None"),
	DurationControlNotification_1Hour = 1 UMETA(DisplayName = "1 Hour"),
	DurationControlNotification_3Hours = 2 UMETA(DisplayName = "3 Hours"),
	DurationControlNotification_HalfProgress = 3 UMETA(DisplayName = "Half Progress"),
	DurationControlNotification_ExitSoon_3h = 4 UMETA(DisplayName = "Exit Soon 3h"),
	DurationControlNotification_ExitSoon_5h = 4 UMETA(DisplayName = "Exit Soon 5h"),
	DurationControlNotification_ExitSoon_Night = 4 UMETA(DisplayName = "Exit Soon Night"),
};

UENUM(BlueprintType)
enum ESIK_DurationControlProgress
{
	DurationControlProgress_Full = 0 UMETA(DisplayName = "Full"),
	DurationControlProgress_Half = 1 UMETA(DisplayName = "Half"),
	DurationControlProgress_None = 2 UMETA(DisplayName = "None"),
};
DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnDurationControl,TEnumAsByte<ESIK_Result>,Result, TEnumAsByte<ESIK_DurationControlNotification>,Notification, TEnumAsByte<ESIK_DurationControlProgress>,Progress, int32, SecsLast5h,bool, bApplicable, int32, AppID);

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_GetDurationControl_AsyncFunction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, DisplayName="Get Duration Control",meta = (BlueprintInternalUseOnly = "true"), Category="Steam Integration Kit || SDK Functions || User")
	static USIK_GetDurationControl_AsyncFunction* GetDurationControl();

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | User")
	FOnDurationControl OnSuccess;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | User")
	FOnDurationControl OnFailure;
private:
	virtual void Activate() override;
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
	SteamAPICall_t m_SteamAPICall;
	CCallResult<USIK_GetDurationControl_AsyncFunction, DurationControl_t> m_Callback;
	void OnDurationControl(DurationControl_t* DurationControl, bool bIOFailure);
#endif
};
