// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SIK_SharedFile.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "HostMigrationSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHostMigration, FSIK_SteamId, LobbyId, bool, bLocalPlayerHost);

UCLASS()
class STEAMINTEGRATIONKIT_API UHostMigrationSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit | Matchmaking")
	void StartHostMigration(FSIK_SteamId LobbyId);

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit | Matchmaking | Callbacks")
	FOnHostMigration OnHostMigration;
	
	UHostMigrationSubsystem();
	~UHostMigrationSubsystem();
private:
	FSIK_SteamId CurrentLobbyId;
	FSIK_SteamId CurrentOwner;
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	STEAM_CALLBACK_MANUAL(UHostMigrationSubsystem, OnLobbyDataUpdateCallback, LobbyDataUpdate_t, m_CallbackLobbyDataUpdate);
#endif
	
};
