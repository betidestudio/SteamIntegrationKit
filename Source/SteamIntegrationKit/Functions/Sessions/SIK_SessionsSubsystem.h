// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SIK_SharedFile.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SIK_SessionsSubsystem.generated.h"

USTRUCT(BlueprintType)
struct FSIK_CurrentSessionInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category="Steam Integration Kit || Game Functions || Sessions")
	FString SessionName;

	UPROPERTY(BlueprintReadWrite, Category="Steam Integration Kit || Game Functions || Sessions")
	FSIK_SteamId LobbyId;

	FSIK_CurrentSessionInfo()
	{
		SessionName = "";
		LobbyId = FSIK_SteamId();
	}
	FSIK_CurrentSessionInfo(FString InSessionName, FSIK_SteamId InLobbyId)
	{
		SessionName = InSessionName;
		LobbyId = InLobbyId;
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSIK_OnSessionUserInviteAccepted, bool, bWasSuccesfull, const FBlueprintSessionResult&, AcceptedSession);

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_SessionsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void Func_OnSessionUserInviteAccepted(bool bArg, int I, TSharedPtr<const FUniqueNetId> UniqueNetId, const FOnlineSessionSearchResult& OnlineSessionSearchResult);
	
	USIK_SessionsSubsystem();
	~USIK_SessionsSubsystem();

	FDelegateHandle OnSessionUserInviteAcceptedDelegateHandle;
	
	UPROPERTY(BlueprintAssignable, DisplayName="On Session User Invite Accepted")
	FSIK_OnSessionUserInviteAccepted OnSessionUserInviteAccepted;
	
	
	UFUNCTION(BlueprintCallable, DisplayName="Get All Joined Sessions And Lobbies", Category="Steam Integration Kit || Game Functions || Sessions", meta=( WorldContext = "Context" ))
	static TArray<FSIK_CurrentSessionInfo> GetAllJoinedSessionsAndLobbies(UObject* Context);

	UFUNCTION(BlueprintCallable, DisplayName="Is SIK Active", Category="Steam Integration Kit || Game Functions || Sessions", meta=( WorldContext = "Context" ))
	static bool IsSIKActive(UObject* Context);

	
};
