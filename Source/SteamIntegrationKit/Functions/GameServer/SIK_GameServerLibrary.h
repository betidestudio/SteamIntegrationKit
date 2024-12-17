// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SIK_SharedFile.h"
#include "Runtime/Launch/Resources/Version.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SIK_GameServerLibrary.generated.h"



UENUM(BlueprintType)
enum ESIK_UserHasLicenseForAppResult
{
	UserHasLicenseResultHasLicense = 0 UMETA(DisplayName = "Has License"),
	UserHasLicenseResultDoesNotHaveLicense = 1 UMETA(DisplayName = "Does Not Have License"),
	UserHasLicenseResultNoAuth = 2 UMETA(DisplayName = "No Auth"),
};

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_GameServerLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, DisplayName = "Begin Steam Auth Session", meta=(Keywords="BeginAuthSession"), Category = "Steam Integration Kit || SDK Functions || Game Server")
	static TEnumAsByte<ESIK_BeginAuthSessionResult> BeginAuthSession(const TArray<uint8>& Token, FSIK_SteamId SteamId);

	/*
	Checks if the game server is currently logged on to Steam.
	@return - true if logged on, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Logged On", meta=(Keywords="BLoggedOn"), Category = "Steam Integration Kit || SDK Functions || Game Server")
	static bool LoggedOn();

	/*
	Checks if the game server is marked as secure.
	@return - true if secure, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Secure", meta=(Keywords="BSecure"), Category = "Steam Integration Kit || SDK Functions || Game Server")
	static bool Secure();

	/*
	Updates the user data for a connected user.
	@param SteamId - The Steam ID of the user.
	@param PlayerName - The name of the player.
	@param Score - The score of the player.
	@return - true if the user data was updated successfully, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Update User Data", meta=(Keywords="BUpdateUserData"), Category = "Steam Integration Kit || SDK Functions || Game Server")
	static bool UpdateUserData(FSIK_SteamId SteamId, const FString& PlayerName, int32 Score);

	/*
	Cancels an auth ticket for a user.
	@param SteamId - The Steam ID of the user.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Cancel Steam Auth Ticket", meta=(Keywords="CancelAuthTicket"), Category = "Steam Integration Kit || SDK Functions || Game Server")
	static void CancelAuthTicket(FSIK_AuthTicket AuthTicket);

	/*
	Clears all key-value pairs for the game server.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Clear All Key Values", meta=(Keywords="ClearAllKeyValues"), Category = "Steam Integration Kit || SDK Functions || Game Server")
	static void ClearAllKeyValues();

	/*
	Creates an unauthenticated user connection.
	@return - The Steam ID of the unauthenticated user.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Create Unauthenticated User Connection", meta=(Keywords="CreateUnauthenticatedUserConnection"), Category = "Steam Integration Kit || SDK Functions || Game Server")
	static FSIK_SteamId CreateUnauthenticatedUserConnection();

	/*
	Ends an auth session for a user.
	@param SteamId - The Steam ID of the user.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "End Auth Session", meta=(Keywords="EndAuthSession"), Category = "Steam Integration Kit || SDK Functions || Game Server")
	static void EndAuthSession(FSIK_SteamId SteamId);

	/*
	Gets an auth session ticket for the game server.
	@return - The auth session ticket as an array of bytes.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Get Auth Session Ticket", meta=(Keywords="GetAuthSessionTicket"), Category = "Steam Integration Kit || SDK Functions || Game Server")
	static TArray<uint8> GetAuthSessionTicket();

	/*
	Gets the public IP address of the game server.
	@return - The public IP address.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Get Public IP", meta=(Keywords="GetPublicIP"), Category = "Steam Integration Kit || SDK Functions || Game Server")
	static FSIK_SteamIPAddress GetPublicIP();

	/*
	Gets the Steam ID of the game server.
	@return - The Steam ID of the server.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Get Server Steam ID", meta=(Keywords="GetSteamID"), Category = "Steam Integration Kit || SDK Functions || Game Server")
	static FSIK_SteamId GetSteamID();

	/*
	Logs the game server off from Steam.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Log Server Off", meta=(Keywords="LogOff"), Category = "Steam Integration Kit || SDK Functions || Game Server")
	static void LogOff();

	/*
	Logs the game server on to Steam.
	@param Token - The login token for the server.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Log Server On", meta=(Keywords="LogOn"), Category = "Steam Integration Kit || SDK Functions || Game Server")
	static void LogOn(const FString& Token);

	/*
	Logs the game server on to Steam anonymously.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Log Server On Anonymous", meta=(Keywords="LogOnAnonymous"), Category = "Steam Integration Kit || SDK Functions || Game Server")
	static void LogOnAnonymous();

	/*
	Requests the user group status for a user.
	@param SteamId - The Steam ID of the user.
	@param GroupId - The Steam ID of the group.
	@return - true if the request was successful, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Request User Group Status", meta=(Keywords="RequestUserGroupStatus"), Category = "Steam Integration Kit || SDK Functions || Game Server")
	static bool RequestUserGroupStatus(FSIK_SteamId SteamId, FSIK_SteamId GroupId);

	/*
	Sets the bot player count for the game server.
	@param BotPlayerCount - The number of bot players.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Set Bot Player Count", meta=(Keywords="SetBotPlayerCount"), Category = "Steam Integration Kit || SDK Functions || Game Server")
	static void SetBotPlayerCount(int32 BotPlayerCount);

	/*
	Sets whether the game server is a dedicated server.
	@param bDedicated - If true, the server is dedicated.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Set Dedicated Server", meta=(Keywords="SetDedicatedServer"), Category = "Steam Integration Kit || SDK Functions || Game Server")
	static void SetDedicatedServer(bool bDedicated);

	/*
	Sets the game data for the game server.
	@param GameData - The game data string.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Set Game Data", meta=(Keywords="SetGameData"), Category = "Steam Integration Kit || SDK Functions || Game Server")
	static void SetGameData(const FString& GameData);

	/*
	Sets the game description for the game server.
	@param GameDescription - The game description string.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Set Game Description", meta=(Keywords="SetGameDescription"), Category = "Steam Integration Kit || SDK Functions || Game Server")
	static void SetGameDescription(const FString& GameDescription);

	/*
	Sets the game tags for the game server.
	@param GameTags - The game tags string.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Set Game Tags", meta=(Keywords="SetGameTags"), Category = "Steam Integration Kit || SDK Functions || Game Server")
	static void SetGameTags(const FString& GameTags);

	/*
	Sets a key-value pair for the game server.
	@param Key - The key string.
	@param Value - The value string.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Set Key Value", meta=(Keywords="SetKeyValue"), Category = "Steam Integration Kit || SDK Functions || Game Server")
	static void SetKeyValue(const FString& Key, const FString& Value);

	/*
	Sets the map name for the game server.
	@param MapName - The map name string.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Set Map Name", meta=(Keywords="SetMapName"), Category = "Steam Integration Kit || SDK Functions || Game Server")
	static void SetMapName(const FString& MapName);

	/*
	Sets the max player count for the game server.
	@param MaxPlayerCount - The maximum number of players.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Set Max Player Count", meta=(Keywords="SetMaxPlayerCount"), Category = "Steam Integration Kit || SDK Functions || Game Server")
	static void SetMaxPlayerCount(int32 MaxPlayerCount);

	/*
	Sets the mod directory for the game server.
	@param ModDir - The mod directory string.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Set Mod Dir", meta=(Keywords="SetModDir"), Category = "Steam Integration Kit || SDK Functions || Game Server")
	static void SetModDir(const FString& ModDir);

	/*
	Sets whether the game server is password protected.
	@param bPasswordProtected - If true, the server is password protected.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Set Password Protected", meta=(Keywords="SetPasswordProtected"), Category = "Steam Integration Kit || SDK Functions || Game Server")
	static void SetPasswordProtected(bool bPasswordProtected);

	/*
	Sets the product name for the game server.
	@param Product - The product name string.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Set Product", meta=(Keywords="SetProduct"), Category = "Steam Integration Kit || SDK Functions || Game Server")
	static void SetProduct(const FString& Product);

	/*
	Sets the region for the game server.
	@param Region - The region string.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Set Region", meta=(Keywords="SetRegion"), Category = "Steam Integration Kit || SDK Functions || Game Server")
	static void SetRegion(const FString& Region);

	/*
	Sets the server name for the game server.
	@param ServerName - The server name string.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Set Server Name", meta=(Keywords="SetServerName"), Category = "Steam Integration Kit || SDK Functions || Game Server")
	static void SetServerName(const FString& ServerName);

	/*
	Sets the spectator port for the game server.
	@param SpectatorPort - The spectator port number.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Set Spectator Port", meta=(Keywords="SetSpectatorPort"), Category = "Steam Integration Kit || SDK Functions || Game Server")
	static void SetSpectatorPort(int32 SpectatorPort);

	/*
	Sets the spectator server name for the game server.
	@param SpectatorServerName - The spectator server name string.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Set Spectator Server Name", meta=(Keywords="SetSpectatorServerName"), Category = "Steam Integration Kit || SDK Functions || Game Server")
	static void SetSpectatorServerName(const FString& SpectatorServerName);

	/*
	Checks if a user has a license for an app.
	@param SteamId - The Steam ID of the user.
	@param AppId - The App ID to check.
	@return - The license result as an ESIK_UserHasLicenseForAppResult enum.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "User Has License For App", meta=(Keywords="UserHasLicenseForApp"), Category = "Steam Integration Kit || SDK Functions || Game Server")
	static TEnumAsByte<ESIK_UserHasLicenseForAppResult> UserHasLicenseForApp(FSIK_SteamId SteamId, int32 AppId);

	/*
	Checks if a restart was requested for the game server.
	@return - true if a restart was requested, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "Was Restart Requested", meta=(Keywords="WasRestartRequested"), Category = "Steam Integration Kit || SDK Functions || Game Server")
	static bool WasRestartRequested();
};
