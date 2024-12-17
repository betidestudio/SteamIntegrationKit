// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SIK_SharedFile.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SIK_GameServerSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAssociateWithClanResultDelegate, TEnumAsByte<ESIK_Result>, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FComputeNewPlayerCompatibilityResultDelegate, TEnumAsByte<ESIK_Result>, Result, FSIK_SteamId, SteamID, int32, PlayersThatDontLikeCandidate, int32, PlayersThatCandidateDoesntLike, int32, ClanPlayersThatDontLikeCandidate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGSClientApproveDelegate, FSIK_SteamId, SteamID, FSIK_SteamId, OwnerSteamID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FGSClientDenyDelegate, FSIK_SteamId, SteamID, TEnumAsByte<ESIK_DenyReason>, Reason, const FString&, OptionalText);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FGSClientGroupStatusDelegate, FSIK_SteamId, SteamID, FSIK_SteamId, GroupID, bool, Member, bool, Officer);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGSClientKickDelegate, FSIK_SteamId, SteamID, TEnumAsByte<ESIK_DenyReason>, Reason);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGSPolicyResponseDelegate, bool, Secure);

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_GameServerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:

	USIK_GameServerSubsystem();
	~USIK_GameServerSubsystem();
	
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || Game Server")
	FAssociateWithClanResultDelegate OnAssociateWithClanResult;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || Game Server")
	FComputeNewPlayerCompatibilityResultDelegate OnComputeNewPlayerCompatibilityResult;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || Game Server")
	FGSClientApproveDelegate OnGSClientApprove;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || Game Server")
	FGSClientDenyDelegate OnGSClientDeny;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || Game Server")
	FGSClientGroupStatusDelegate OnGSClientGroupStatus;
	
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || Game Server")
	FGSClientKickDelegate OnGSClientKick;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || Game Server")
	FGSPolicyResponseDelegate OnGSPolicyResponse;
	
private:
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	//AssociateWithClanResult_t
	STEAM_CALLBACK_MANUAL(USIK_GameServerSubsystem, OnAssociateWithClanResultCallbck, AssociateWithClanResult_t, m_CallbackAssociateWithClanResult);
	//ComputeNewPlayerCompatibilityResult_t
	STEAM_CALLBACK_MANUAL(USIK_GameServerSubsystem, OnComputeNewPlayerCompatibilityResultCallbck, ComputeNewPlayerCompatibilityResult_t, m_CallbackComputeNewPlayerCompatibilityResult);
	//GSClientApprove_t
	STEAM_CALLBACK_MANUAL(USIK_GameServerSubsystem, OnGSClientApproveCallbck, GSClientApprove_t, m_CallbackGSClientApprove);
	//GSClientDeny_t
	STEAM_CALLBACK_MANUAL(USIK_GameServerSubsystem, OnGSClientDenyCallbck, GSClientDeny_t, m_CallbackGSClientDeny);
	//GSClientGroupStatus_t
	STEAM_CALLBACK_MANUAL(USIK_GameServerSubsystem, OnGSClientGroupStatusCallbck, GSClientGroupStatus_t, m_CallbackGSClientGroupStatus);
	//GSClientKick_t
	STEAM_CALLBACK_MANUAL(USIK_GameServerSubsystem, OnGSClientKickCallbck, GSClientKick_t, m_CallbackGSClientKick);
	//GSPolicyResponse_t
	STEAM_CALLBACK_MANUAL(USIK_GameServerSubsystem, OnGSPolicyResponseCallbck, GSPolicyResponse_t, m_CallbackGSPolicyResponse);
#endif
};
