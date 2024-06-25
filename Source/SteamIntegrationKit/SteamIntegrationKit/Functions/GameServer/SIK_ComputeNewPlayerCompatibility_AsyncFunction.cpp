// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_ComputeNewPlayerCompatibility_AsyncFunction.h"

#include "Async/Async.h"

USIK_ComputeNewPlayerCompatibility_AsyncFunction* USIK_ComputeNewPlayerCompatibility_AsyncFunction::
ComputeNewPlayerCompatibility(const FSIK_SteamId& PlayerSteamId)
{
	USIK_ComputeNewPlayerCompatibility_AsyncFunction* Node = NewObject<USIK_ComputeNewPlayerCompatibility_AsyncFunction>();
	Node->Var_PlayerSteamId = PlayerSteamId;
	return Node;
}

void USIK_ComputeNewPlayerCompatibility_AsyncFunction::OnComputeNewPlayerCompatibilityCallback(
	ComputeNewPlayerCompatibilityResult_t* ComputeNewPlayerCompatibilityResult, bool bIOFailure)
{
	auto Param = *ComputeNewPlayerCompatibilityResult;
	AsyncTask(ENamedThreads::GameThread, [this, Param,bIOFailure]()
	{
		if(bIOFailure)
		{
			OnFailure.Broadcast(ESIK_Result::ResultFail, 0, 0, 0);
		}
		else
		{
			if(Param.m_SteamIDCandidate == Var_PlayerSteamId.GetSteamID())
			{
				OnSuccess.Broadcast(static_cast<ESIK_Result>(Param.m_eResult), Param.m_cPlayersThatDontLikeCandidate, Param.m_cPlayersThatCandidateDoesntLike, Param.m_cClanPlayersThatDontLikeCandidate);
			}
			else
			{
				OnFailure.Broadcast(static_cast<ESIK_Result>(Param.m_eResult), Param.m_cPlayersThatDontLikeCandidate, Param.m_cPlayersThatCandidateDoesntLike, Param.m_cClanPlayersThatDontLikeCandidate);
			}
		}
	});
	SetReadyToDestroy();
	MarkAsGarbage();
}

void USIK_ComputeNewPlayerCompatibility_AsyncFunction::Activate()
{
	Super::Activate();
	if(!SteamGameServer())
	{
		OnFailure.Broadcast(ESIK_Result::ResultFail, 0, 0, 0);
		SetReadyToDestroy();
		MarkAsGarbage();
		return;	
	}
	CallbackHandle = SteamGameServer()->ComputeNewPlayerCompatibility(Var_PlayerSteamId.GetSteamID());
	if(CallbackHandle == k_uAPICallInvalid)
	{
		OnFailure.Broadcast(ESIK_Result::ResultFail, 0, 0, 0);
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	OnComputeNewPlayerCompatibilityCallResult.Set( CallbackHandle, this, &USIK_ComputeNewPlayerCompatibility_AsyncFunction::OnComputeNewPlayerCompatibilityCallback);
}
