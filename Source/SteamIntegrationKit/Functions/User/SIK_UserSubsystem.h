// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SIK_SharedFile.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SIK_UserSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FSIK_ClientGameServerDenyDelegate, int32, AppID, FString, GameServerIP, int32, GameServerPort, int32, Secure, int32, Reason);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSIK_DurationControlDelegate, int32, AppID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSIK_EncryptedAppTicketResponseDelegate, int32, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSIK_GameWebCallbackDelegate, FString, URL);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSIK_GetAuthSessionTicketResponseDelegate, int32, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FSIK_GetTicketForWebApiResponseDelegate, int32, Result, int32, AuthTicket,const TArray<uint8>&, TicketData, const FString&, TicketAsStr);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSIK_IPCFailureDelegate, int32, FailureType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSIK_LicensesUpdatedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FSIK_MicroTxnAuthorizationResponseDelegate, int32, AppID, int32, OrderID, bool, Authorized);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSIK_SteamServerConnectFailureDelegate, int32, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSIK_SteamServersConnectedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSIK_SteamServersDisconnectedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSIK_StoreAuthURLResponseDelegate, FString, URL);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FSIK_ValidateAuthTicketResponseDelegate, FSIK_SteamId, SteamID, int32, AuthSessionResponse, FSIK_SteamId, OwnerSteamID);

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_UserSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	USIK_UserSubsystem();
	~USIK_UserSubsystem();

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || User")
	FSIK_ClientGameServerDenyDelegate OnClientGameServerDenyCallback;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || User")
	FSIK_DurationControlDelegate OnDurationControlCallback;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || User")
	FSIK_EncryptedAppTicketResponseDelegate OnEncryptedAppTicketResponseCallback;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || User")
	FSIK_GameWebCallbackDelegate OnGameWebCallbackCallback;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || User")
	FSIK_GetAuthSessionTicketResponseDelegate OnGetAuthSessionTicketResponseCallback;
	
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || User")
	FSIK_GetTicketForWebApiResponseDelegate OnGetTicketForWebApiResponseCallback;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || User")
	FSIK_IPCFailureDelegate OnIPCFailureCallback;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || User")
	FSIK_LicensesUpdatedDelegate OnLicensesUpdatedCallback;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || User")
	FSIK_MicroTxnAuthorizationResponseDelegate OnMicroTxnAuthorizationResponseCallback;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || User")
	FSIK_SteamServerConnectFailureDelegate OnSteamServerConnectFailureCallback;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || User")
	FSIK_SteamServersConnectedDelegate OnSteamServersConnectedCallback;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || User")
	FSIK_SteamServersDisconnectedDelegate OnSteamServersDisconnectedCallback;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || User")
	FSIK_StoreAuthURLResponseDelegate OnStoreAuthURLResponseCallback;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || User")
	FSIK_ValidateAuthTicketResponseDelegate OnValidateAuthTicketResponseCallback;


private:
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	STEAM_CALLBACK_MANUAL(USIK_UserSubsystem, OnClientGameServerDeny, ClientGameServerDeny_t, m_CallbackClientGameServerDeny);
	STEAM_CALLBACK_MANUAL(USIK_UserSubsystem, OnDurationControl, DurationControl_t, m_CallbackDurationControl);
	STEAM_CALLBACK_MANUAL(USIK_UserSubsystem, OnGameWebCallback, GameWebCallback_t, m_CallbackGameWebCallback);
	STEAM_CALLBACK_MANUAL(USIK_UserSubsystem, OnGetAuthSessionTicketResponse, GetAuthSessionTicketResponse_t, m_CallbackGetAuthSessionTicketResponse);
#if WITH_ENGINE_STEAM && ENGINE_MINOR_VERSION <= 3
#else
	STEAM_CALLBACK_MANUAL(USIK_UserSubsystem, OnGetTicketForWebApiResponse, GetTicketForWebApiResponse_t, m_CallbackGetTicketForWebApiResponse);
#endif
	STEAM_CALLBACK_MANUAL(USIK_UserSubsystem, OnIPCFailure, IPCFailure_t, m_CallbackIPCFailure);
	STEAM_CALLBACK_MANUAL(USIK_UserSubsystem, OnLicensesUpdated, LicensesUpdated_t, m_CallbackLicensesUpdated);
	STEAM_CALLBACK_MANUAL(USIK_UserSubsystem, OnMicroTxnAuthorizationResponse, MicroTxnAuthorizationResponse_t, m_CallbackMicroTxnAuthorizationResponse);
	STEAM_CALLBACK_MANUAL(USIK_UserSubsystem, OnSteamServerConnectFailure, SteamServerConnectFailure_t, m_CallbackSteamServerConnectFailure);
	STEAM_CALLBACK_MANUAL(USIK_UserSubsystem, OnSteamServersConnected, SteamServersConnected_t, m_CallbackSteamServersConnected);
	STEAM_CALLBACK_MANUAL(USIK_UserSubsystem, OnSteamServersDisconnected, SteamServersDisconnected_t, m_CallbackSteamServersDisconnected);
	STEAM_CALLBACK_MANUAL(USIK_UserSubsystem, OnStoreAuthURLResponse, StoreAuthURLResponse_t, m_CallbackStoreAuthURLResponse);
	STEAM_CALLBACK_MANUAL(USIK_UserSubsystem, OnValidateAuthTicketResponse, ValidateAuthTicketResponse_t, m_CallbackValidateAuthTicketResponse);
#endif
	
};
