// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SIK_SharedFile.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SIK_PartiesSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FSIK_JoinPartyDelegate, TEnumAsByte<ESIK_Result>, Result, FSIK_PartyBeaconID, PartyBeaconID, FSIK_SteamId, BeaconOwner, FString, ConnectString);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCreateBeaconDelegate1, TEnumAsByte<ESIK_Result>, Result, FSIK_PartyBeaconID, BeaconID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FReservationNotificationDelegate, FSIK_PartyBeaconID, BeaconID, FSIK_SteamId, SteamID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChangeNumOpenSlotsDelegate1, const TEnumAsByte<ESIK_Result>, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAvailableBeaconLocationsUpdatedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FActiveBeaconsUpdatedDelegate);
UCLASS(DisplayName="Parties Subsystem", meta=(BlueprintInternalUseOnly = "true"), Category="Steam Integration Kit || SDK Functions || Parties")
class STEAMINTEGRATIONKIT_API USIK_PartiesSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	USIK_PartiesSubsystem();
	~USIK_PartiesSubsystem();

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || Parties")
	FSIK_JoinPartyDelegate OnJoinPartyResult;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || Parties")
	FCreateBeaconDelegate1 OnCreateBeaconResult;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || Parties")
	FReservationNotificationDelegate OnReservationNotification;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || Parties")
	FChangeNumOpenSlotsDelegate1 OnChangeNumOpenSlots;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || Parties")
	FAvailableBeaconLocationsUpdatedDelegate OnAvailableBeaconLocationsUpdated;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || SDK Functions || Parties")
	FActiveBeaconsUpdatedDelegate OnActiveBeaconsUpdated;

private:
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	STEAM_CALLBACK_MANUAL(USIK_PartiesSubsystem, OnJoinPartyCallback, JoinPartyCallback_t, m_CallbackJoinParty);
	STEAM_CALLBACK_MANUAL(USIK_PartiesSubsystem, OnCreateBeaconCallback, CreateBeaconCallback_t, m_CallbackCreateBeacon);
	STEAM_CALLBACK_MANUAL(USIK_PartiesSubsystem, OnReservationNotificationCallback, ReservationNotificationCallback_t, m_CallbackReservationNotification);
	STEAM_CALLBACK_MANUAL(USIK_PartiesSubsystem, OnChangeNumOpenSlotsCallback, ChangeNumOpenSlotsCallback_t, m_CallbackChangeNumOpenSlots);
	STEAM_CALLBACK_MANUAL(USIK_PartiesSubsystem, OnAvailableBeaconLocationsUpdatedCallback, AvailableBeaconLocationsUpdated_t, m_CallbackAvailableBeaconLocationsUpdated);
	STEAM_CALLBACK_MANUAL(USIK_PartiesSubsystem, OnActiveBeaconsUpdatedCallback, ActiveBeaconsUpdated_t, m_CallbackActiveBeaconsUpdated);
#endif
};
