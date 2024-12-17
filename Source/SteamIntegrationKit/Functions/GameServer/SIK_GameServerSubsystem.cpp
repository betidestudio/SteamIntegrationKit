// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_GameServerSubsystem.h"

#include "Async/Async.h"

USIK_GameServerSubsystem::USIK_GameServerSubsystem()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	m_CallbackAssociateWithClanResult.Register(this, &USIK_GameServerSubsystem::OnAssociateWithClanResultCallbck);
	m_CallbackComputeNewPlayerCompatibilityResult.Register(this, &USIK_GameServerSubsystem::OnComputeNewPlayerCompatibilityResultCallbck);
	m_CallbackGSClientApprove.Register(this, &USIK_GameServerSubsystem::OnGSClientApproveCallbck);
	m_CallbackGSClientDeny.Register(this, &USIK_GameServerSubsystem::OnGSClientDenyCallbck);
	m_CallbackGSClientGroupStatus.Register(this, &USIK_GameServerSubsystem::OnGSClientGroupStatusCallbck);
	m_CallbackGSClientKick.Register(this, &USIK_GameServerSubsystem::OnGSClientKickCallbck);
	m_CallbackGSPolicyResponse.Register(this, &USIK_GameServerSubsystem::OnGSPolicyResponseCallbck);


 	if(IsRunningDedicatedServer())
 	{
 		m_CallbackAssociateWithClanResult.SetGameserverFlag();
 		m_CallbackGSClientApprove.SetGameserverFlag();
 		m_CallbackComputeNewPlayerCompatibilityResult.SetGameserverFlag();
 		m_CallbackGSClientDeny.SetGameserverFlag();
 		m_CallbackGSClientGroupStatus.SetGameserverFlag();
 		m_CallbackGSClientKick.SetGameserverFlag();
 		m_CallbackGSPolicyResponse.SetGameserverFlag();
 	}
#endif
}

USIK_GameServerSubsystem::~USIK_GameServerSubsystem()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	m_CallbackAssociateWithClanResult.Unregister();
	m_CallbackComputeNewPlayerCompatibilityResult.Unregister();
	m_CallbackGSClientApprove.Unregister();
	m_CallbackGSClientDeny.Unregister();
	m_CallbackGSClientGroupStatus.Unregister();
	m_CallbackGSClientKick.Unregister();
	m_CallbackGSPolicyResponse.Unregister();
#endif
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
void USIK_GameServerSubsystem::OnAssociateWithClanResultCallbck(AssociateWithClanResult_t* pCallback)
{
	auto Param = *pCallback;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnAssociateWithClanResult.Broadcast(static_cast<ESIK_Result>(Param.m_eResult));
	});
}

void USIK_GameServerSubsystem::OnComputeNewPlayerCompatibilityResultCallbck(ComputeNewPlayerCompatibilityResult_t* pCallback)
{
	auto Param = *pCallback;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnComputeNewPlayerCompatibilityResult.Broadcast(static_cast<ESIK_Result>(Param.m_eResult), Param.m_SteamIDCandidate, Param.m_cPlayersThatDontLikeCandidate, Param.m_cPlayersThatCandidateDoesntLike, Param.m_cClanPlayersThatDontLikeCandidate);
	});
}

void USIK_GameServerSubsystem::OnGSClientApproveCallbck(GSClientApprove_t* pCallback)
{
	auto Param = *pCallback;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnGSClientApprove.Broadcast(Param.m_SteamID, Param.m_OwnerSteamID);
	});
}

void USIK_GameServerSubsystem::OnGSClientDenyCallbck(GSClientDeny_t* pCallback)
{
	auto Param = *pCallback;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnGSClientDeny.Broadcast(Param.m_SteamID, static_cast<ESIK_DenyReason>(Param.m_eDenyReason), Param.m_rgchOptionalText);
	});
}

void USIK_GameServerSubsystem::OnGSClientGroupStatusCallbck(GSClientGroupStatus_t* pCallback)
{
	auto Param = *pCallback;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnGSClientGroupStatus.Broadcast(Param.m_SteamIDUser, Param.m_SteamIDGroup, Param.m_bMember, Param.m_bOfficer);
	});
}

void USIK_GameServerSubsystem::OnGSClientKickCallbck(GSClientKick_t* pCallback)
{
	auto Param = *pCallback;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnGSClientKick.Broadcast(Param.m_SteamID, static_cast<ESIK_DenyReason>(Param.m_eDenyReason));
	});
}

void USIK_GameServerSubsystem::OnGSPolicyResponseCallbck(GSPolicyResponse_t* pCallback)
{
	auto Param = *pCallback;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnGSPolicyResponse.Broadcast(Param.m_bSecure == 1);
	});
}
#endif