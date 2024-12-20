// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_ChangeNumOpenSlots_AsyncFunction.h"

#include "Async/Async.h"


USIK_ChangeNumOpenSlots_AsyncFunction* USIK_ChangeNumOpenSlots_AsyncFunction::ChangeNumOpenSlots(
	const FSIK_PartyBeaconID& PartyBeaconID, int32 OpenSlots)
{
	USIK_ChangeNumOpenSlots_AsyncFunction* Node = NewObject<USIK_ChangeNumOpenSlots_AsyncFunction>();
	Node->Var_nOpenSlots = OpenSlots;
	Node->PartyBeaconID = PartyBeaconID;
	return Node;
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
void USIK_ChangeNumOpenSlots_AsyncFunction::OnChangeNumOpenSlots(
	ChangeNumOpenSlotsCallback_t* ChangeNumOpenSlotsCallback, bool bIOFailure)
{
	auto Param = *ChangeNumOpenSlotsCallback;
	AsyncTask(ENamedThreads::GameThread, [this, Param,bIOFailure]()
	{
		OnChangeNumOpenSlotsCallResult.Cancel();
		if(bIOFailure)
		{
			OnFailure.Broadcast(ESIK_Result::ResultFail);
		}
		else
		{
			TEnumAsByte<ESIK_Result> Result = static_cast<ESIK_Result>(Param.m_eResult);
			OnSuccess.Broadcast(Result);
		}
	});
	SetReadyToDestroy();
	MarkAsGarbage();
}
#endif

void USIK_ChangeNumOpenSlots_AsyncFunction::Activate()
{
	Super::Activate();
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
	if(!SteamParties())
	{
		OnFailure.Broadcast(ESIK_Result::ResultFail);
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	CallbackHandle = SteamParties()->ChangeNumOpenSlots(PartyBeaconID.GetPartyBeaconID(), Var_nOpenSlots);
	if(CallbackHandle == k_uAPICallInvalid)
	{
		OnFailure.Broadcast(ESIK_Result::ResultFail);
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	OnChangeNumOpenSlotsCallResult.Set(CallbackHandle, this, &USIK_ChangeNumOpenSlots_AsyncFunction::OnChangeNumOpenSlots);
#else
	OnFailure.Broadcast(ESIK_Result::ResultFail);
	SetReadyToDestroy();
	MarkAsGarbage();
#endif
}
