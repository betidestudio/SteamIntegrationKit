// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SIK_SharedFile.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SIK_SessionsSubsystem.generated.h"

USTRUCT(BlueprintType)
struct FEIK_CurrentSessionInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category="Steam Integration Kit || Game Functions || Sessions")
	FString SessionName;

	UPROPERTY(BlueprintReadWrite, Category="Steam Integration Kit || Game Functions || Sessions")
	FSIK_SteamId LobbyId;

	FEIK_CurrentSessionInfo()
	{
		SessionName = "";
		LobbyId = FSIK_SteamId();
	}
	FEIK_CurrentSessionInfo(FString InSessionName, FSIK_SteamId InLobbyId)
	{
		SessionName = InSessionName;
		LobbyId = InLobbyId;
	}
};

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_SessionsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, DisplayName="Get All Joined Sessions And Lobbies", Category="Steam Integration Kit || Game Functions || Sessions", meta=( WorldContext = "Context" ))
	static TArray<FEIK_CurrentSessionInfo> GetAllJoinedSessionsAndLobbies(UObject* Context);

	UFUNCTION(BlueprintCallable, DisplayName="Is SIK Active", Category="Steam Integration Kit || Game Functions || Sessions", meta=( WorldContext = "Context" ))
	static bool IsSIKActive(UObject* Context);

	
};
