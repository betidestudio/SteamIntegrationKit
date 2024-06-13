// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SIK_SharedFile.h"
THIRD_PARTY_INCLUDES_START
#if WITH_ENGINE_STEAM
#include "steam/steam_api.h"
#include "steam/isteamvideo.h"
#include "steam/steam_api_common.h"
#else
#include "isteamvideo.h"
#include "steam_api_common.h"
#endif
THIRD_PARTY_INCLUDES_END
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SIK_VideoLibrary.generated.h"

/**
 * 
 */
UCLASS()
class STEAMINTEGRATIONKIT_API USIK_VideoLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, DisplayName = "Get OPF Settings", meta=(Keywords="GetOPFSettings"), Category="Steam Integration Kit || SDK Functions || Video")
	static void GetOPFSettings(FSIK_AppId AppID);

	UFUNCTION(BlueprintCallable, DisplayName = "Get OPF String For App", meta=(Keywords="GetOPFStringForApp"), Category="Steam Integration Kit || SDK Functions || Video")
	static bool GetOPFStringForApp(FSIK_AppId AppID, FString& OutString);

	UFUNCTION(BlueprintCallable, DisplayName = "Get Video URL", meta=(Keywords="GetVideoURL"), Category="Steam Integration Kit || SDK Functions || Video")
	static void GetVideoURL(FSIK_AppId AppID);

	UFUNCTION(BlueprintCallable, DisplayName = "Is Broadcasting", meta=(Keywords="IsBroadcasting"), Category="Steam Integration Kit || SDK Functions || Video")
	static bool IsBroadcasting(int32& OutNumViewers);

	
};
