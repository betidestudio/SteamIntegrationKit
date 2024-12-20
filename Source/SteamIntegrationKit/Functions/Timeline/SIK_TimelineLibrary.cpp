// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_TimelineLibrary.h"
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
#if WITH_ENGINE_STEAM
#else
#include "isteamtimeline.h"
#endif
#endif

void USIK_TimelineLibrary::SetTimelineStateDescription(FString pchDescription, float flTimeDelta)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
#if WITH_ENGINE_STEAM
	UE_LOG(LogTemp, Warning, TEXT("Steam Integration Kit: SetTimelineStateDescription is not available with Github version of the plugin as the SDK Version is older than 1.60"));
#else
	if(!SteamTimeline())
	{
		return;
	}
	SteamTimeline()->SetTimelineStateDescription(TCHAR_TO_ANSI(*pchDescription), flTimeDelta);
#endif
#endif
}

void USIK_TimelineLibrary::ClearTimelineStateDescription(float flTimeDelta)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
#if WITH_ENGINE_STEAM
	UE_LOG(LogTemp, Warning, TEXT("Steam Integration Kit: SetTimelineStateDescription is not available with Github version of the plugin as the SDK Version is older than 1.60"));
#else
	if(!SteamTimeline())
	{
		return;
	}
	SteamTimeline()->ClearTimelineStateDescription(flTimeDelta);
#endif
#endif
}

void USIK_TimelineLibrary::AddTimelineEvent(FString pchIcon, FString pchTitle, FString pchDescription, int32 unPriority,
	float flStartOffsetSeconds, float flDurationSecondsm, TEnumAsByte<ESIK_TimelineEventClipPriority> ePossibleClip)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
#if WITH_ENGINE_STEAM
	UE_LOG(LogTemp, Warning, TEXT("Steam Integration Kit: SetTimelineStateDescription is not available with Github version of the plugin as the SDK Version is older than 1.60"));
#else
	if(!SteamTimeline())
	{
		return;
	}
	SteamTimeline()->AddTimelineEvent(TCHAR_TO_ANSI(*pchIcon), TCHAR_TO_ANSI(*pchTitle), TCHAR_TO_ANSI(*pchDescription), unPriority, flStartOffsetSeconds, flDurationSecondsm, static_cast<ETimelineEventClipPriority>(ePossibleClip.GetValue()));
#endif
#endif
}

void USIK_TimelineLibrary::SetTimelineGameMode(TEnumAsByte<ESIK_TimelineGameMode> eMode)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
#if WITH_ENGINE_STEAM
	UE_LOG(LogTemp, Warning, TEXT("Steam Integration Kit: SetTimelineStateDescription is not available with Github version of the plugin as the SDK Version is older than 1.60"));
#else
	if(!SteamTimeline())
	{
		return;
	}
	SteamTimeline()->SetTimelineGameMode(static_cast<ETimelineGameMode>(eMode.GetValue()));
#endif
#endif
}
