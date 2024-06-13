// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SIK_SharedFile.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SIK_AppLibrary.generated.h"

/**
 * 
 */
UCLASS()
class STEAMINTEGRATIONKIT_API USIK_AppLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/*
	Returns metadata for a DLC by index.
	@param Index - Index of the DLC to get between 0 and GetDLCCount.
	@param AppID - Returns the App ID of the DLC.
	@param Available - Returns whether the DLC is currently available on the Steam store. Will be false if the DLC does not have a visible store page
	@param Name - Returns the name of the DLC by copying it into this buffer.
	@return - true if the current App ID has DLC's associated with it and iDLC falls between the range of 0 to GetDLCCount, otherwise false.
	*/
	UFUNCTION(BlueprintCallable, DisplayName="Get DLC Data By Index", Category="Steam Integration Kit || SDK Functions || Apps")
	static bool GetDLCDataByIndex(int32 Index, FSIK_AppId& AppID, bool& Available, FString& Name);

	/*
	Checks if a specific app is installed.

	The app may not actually be owned by the current user, they may have it left over from a free weekend, etc.

	This only works for base applications, not Downloadable Content (DLC). Use BIsDlcInstalled for DLC instead.
	
	@param AppID - The AppID of the app to check.
	@return - true if the app is installed, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, DisplayName="Is App Installed", meta=(Keywords="BIsAppInstalled"), Category="Steam Integration Kit || SDK Functions || Apps")
	static bool IsAppInstalled(FSIK_AppId AppID);

	/*
	Checks if the user is in a Cybercafe.
	@return - true if the user is in a Cybercafe, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, DisplayName="Is Cybercafe", meta=(Keywords="BIsCybercafe"), Category="Steam Integration Kit || SDK Functions || Apps")
	static bool IsCybercafe();

	/*
	Checks if a DLC is installed.
	
	Note: Should only be used for simple client side checks - not intended for granting in-game items.
	
	@param AppID - The AppID of the DLC to check.
	@return - true if the user owns the DLC, and it's currently installed, otherwise false.
	*/
	UFUNCTION(BlueprintCallable, DisplayName="Is DLC Installed", meta=(Keywords="BIsDLCInstalled"), Category="Steam Integration Kit || SDK Functions || Apps")
	static bool IsDLCInstalled(int32 AppID);

	/*
	Checks if the license owned by the user provides low violence depots.

	Low violence depots are useful for copies sold in countries that have content restrictions.
	
	@return - true if the user is running a low violence version, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, DisplayName="Is Low Violence", meta=(Keywords="BIsLowViolence"), Category="Steam Integration Kit || SDK Functions || Apps")
	static bool IsLowViolence();

	/*
	Checks if the user is subscribed to the current app.
	@return - true if the user is subscribed, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, DisplayName="Is Subscribed", meta=(Keywords="BIsSubscribed"), Category="Steam Integration Kit || SDK Functions || Apps")
	static bool IsSubscribed();

	/*
	Checks if the user is subscribed to a specific app.
	@param AppID - The AppID of the app to check.
	@return - true if the user is subscribed to the app, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, DisplayName="Is Subscribed App", meta=(Keywords="BIsSubscribedApp"), Category="Steam Integration Kit || SDK Functions || Apps")
	static bool IsSubscribedApp(int32 AppID);

	/*
	Checks if the user is subscribed to the app through Family Sharing.
	@return - true if the user is subscribed through Family Sharing, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, DisplayName="Is Subscribed From Family Sharing", meta=(Keywords="BIsSubscribedFromFamilySharing"), Category="Steam Integration Kit || SDK Functions || Apps")
	static bool IsSubscribedFromFamilySharing();

	/*
	Checks if the user is subscribed to the app from a free weekend.
	@return - true if the user is subscribed from a free weekend, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, DisplayName="Is Subscribed From Free Weekend", meta=(Keywords="BIsSubscribedFromFreeWeekend"), Category="Steam Integration Kit || SDK Functions || Apps")
	static bool IsSubscribedFromFreeWeekend();

	/*
	Checks if the user is running a timed trial of the app.
	@param SecondsAllowed - The number of seconds allowed for the trial.
	@param SecondsPlayed - The number of seconds played in the trial.
	@return - true if the user is running a timed trial, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, DisplayName="Is Timed Trial", meta=(Keywords="BIsTimedTrial"), Category="Steam Integration Kit || SDK Functions || Apps")
	static bool IsTimedTrial(int32& SecondsAllowed, int32& SecondsPlayed);

	/*
	Checks if the user is VAC banned.
	@return - true if the user is VAC banned, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, DisplayName="Is VAC Banned", meta=(Keywords="BIsVACBanned"), Category="Steam Integration Kit || SDK Functions || Apps")
	static bool IsVACBanned();

	/*
	Gets the build ID of the current app.
	@return - The build ID of the current app.
	*/
	UFUNCTION(BlueprintCallable, DisplayName="Get App Build ID", meta=(Keywords="GetAppBuildID"), Category="Steam Integration Kit || SDK Functions || Apps")
	static int32 GetAppBuildID();

	/*
	Gets the install directory of an app.
	@param AppID - The AppID of the app to get the install directory for.
	@return - The install directory of the app.
	*/
	UFUNCTION(BlueprintCallable, DisplayName="Get App Install Dir", meta=(Keywords="GetAppInstallDir"), Category="Steam Integration Kit || SDK Functions || Apps")
	static FString GetAppInstallDir(int32 AppID);

	/*
	Gets the Steam ID of the owner of the current app.
	@return - The Steam ID of the app owner.
	*/
	UFUNCTION(BlueprintCallable, DisplayName="Get App Owner", meta=(Keywords="GetAppOwner"), Category="Steam Integration Kit || SDK Functions || Apps")
	static FSIK_SteamId GetAppOwner();

	/*
	Gets the list of available game languages for the current app.
	@return - A list of available game languages.
	*/
	UFUNCTION(BlueprintCallable, DisplayName="Get Available Game Languages", meta=(Keywords="GetAvailableGameLanguages"), Category="Steam Integration Kit || SDK Functions || Apps")
	static TArray<FString> GetAvailableGameLanguages();
	
	/*
	Gets the current beta name for the app.
	@param Name - The name of the current beta.
	@return - true if a beta name is available, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, DisplayName="Get Current Beta Name", meta=(Keywords="GetCurrentBetaName"), Category="Steam Integration Kit || SDK Functions || Apps")
	static bool GetCurrentBetaName(FString& Name);

	/*
	Gets the current game language for the app.
	@return - The current game language.
	*/
	UFUNCTION(BlueprintCallable, DisplayName="Get Current Game Language", meta=(Keywords="GetCurrentGameLanguage"), Category="Steam Integration Kit || SDK Functions || Apps")
	static FString GetCurrentGameLanguage();

	/*
	Gets the number of DLCs for the current app.
	@return - The number of DLCs.
	*/
	UFUNCTION(BlueprintCallable, DisplayName="Get DLC Count", meta=(Keywords="GetDLCCount"), Category="Steam Integration Kit || SDK Functions || Apps")
	static int32 GetDLCCount();

	/*
	Gets the download progress for a DLC.
	@param AppID - The AppID of the DLC.
	@param BytesDownloaded - The number of bytes downloaded.
	@param BytesTotal - The total number of bytes to download.
	@return - true if the download progress is available, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, DisplayName="Get DLC Download Progress", meta=(Keywords="GetDLCDownloadProgress"), Category="Steam Integration Kit || SDK Functions || Apps")
	static bool GetDLCDownloadProgress(FSIK_AppId AppID, int64& BytesDownloaded, int64& BytesTotal);

	/*
	Gets the Unix time of the earliest purchase of an app.
	@param AppID - The AppID of the app.
	@return - The Unix time of the earliest purchase.
	*/
	UFUNCTION(BlueprintCallable, DisplayName="Get Earliest Purchase Unix Time", meta=(Keywords="GetEarliestPurchaseUnixTime"), Category="Steam Integration Kit || SDK Functions || Apps")
	static int32 GetEarliestPurchaseUnixTime(FSIK_AppId AppID);

	/*
	Gets the list of installed depots for an app.
	@param AppID - The AppID of the app.
	@return - A list of installed depots.
	*/
	UFUNCTION(BlueprintCallable, DisplayName="Get Installed Depots", meta=(Keywords="GetInstalledDepots"), Category="Steam Integration Kit || SDK Functions || Apps")
	static TArray<int32> GetInstalledDepots(FSIK_AppId AppID);

	/*
	Gets the launch command line for the app.
	@param CommandLine - The command line string.
	@return - The length of the command line string.
	*/
	UFUNCTION(BlueprintCallable, DisplayName="Get Launch Command Line", meta=(Keywords="GetLaunchCommandLine"), Category="Steam Integration Kit || SDK Functions || Apps")
	static int32 GetLaunchCommandLine(FString& CommandLine);

	/*
	Gets a launch query parameter.
	@param Key - The key of the query parameter.
	@return - The value of the query parameter.
	*/
	UFUNCTION(BlueprintCallable, DisplayName="Get Launch Query Param", meta=(Keywords="GetLaunchQueryParam"), Category="Steam Integration Kit || SDK Functions || Apps")
	static FString GetLaunchQueryParam(FString Key);

	/*
	Installs a DLC.
	@param AppID - The AppID of the DLC to install.
	*/
	UFUNCTION(BlueprintCallable, DisplayName="Install DLC", meta=(Keywords="InstallDLC"), Category="Steam Integration Kit || SDK Functions || Apps")
	static void InstallDLC(FSIK_AppId AppID);
	
	/*
	Marks the content as corrupt.
	@param MissingFilesOnly - true if only missing files should be marked corrupt, false otherwise.
	@return - true if the content was marked as corrupt, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, DisplayName="Mark Content Corrupt", meta=(Keywords="MarkContentCorrupt"), Category="Steam Integration Kit || SDK Functions || Apps")
	static bool MarkContentCorrupt(bool MissingFilesOnly);

	/*
	Uninstalls a DLC.
	@param AppID - The AppID of the DLC to uninstall.
	*/
	UFUNCTION(BlueprintCallable, DisplayName="Uninstall DLC", meta=(Keywords="UninstallDLC"), Category="Steam Integration Kit || SDK Functions || Apps")
	static void UninstallDLC(FSIK_AppId AppID);
};
