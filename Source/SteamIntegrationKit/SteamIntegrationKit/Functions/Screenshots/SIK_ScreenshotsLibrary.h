// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SIK_SharedFile.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SIK_ScreenshotsLibrary.generated.h"

/**
 * 
 */
UCLASS()
class STEAMINTEGRATIONKIT_API USIK_ScreenshotsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Screenshots")
	static FSIK_ScreenshotHandle AddScreenshotToLibrary(FString FileName, FString ThumbnailFileName, int32 Width, int32 Height);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Screenshots")
	static FSIK_ScreenshotHandle AddVRScreenshotToLibrary(TEnumAsByte<ESIK_VRScreenshotType> Type, FString FileName, FString VR_Filename);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Screenshots")
	static void HookScreenshots(bool bHook);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Screenshots")
	static bool IsScreenshotsHooked();

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Screenshots")
	static bool SetLocation(FSIK_ScreenshotHandle Handle, FString Location);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Screenshots")
	static bool TagPublishedFile(FSIK_ScreenshotHandle Handle, FSIK_PublishedFileId PublishedFileID);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Screenshots")
	static bool TagUser(FSIK_ScreenshotHandle Handle, FSIK_SteamId SteamID);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Screenshots")
	static void TriggerScreenshot();

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Screenshots")
	static FSIK_ScreenshotHandle WriteScreenshot(TArray<uint8> Data, int32 Width, int32 Height);

};
