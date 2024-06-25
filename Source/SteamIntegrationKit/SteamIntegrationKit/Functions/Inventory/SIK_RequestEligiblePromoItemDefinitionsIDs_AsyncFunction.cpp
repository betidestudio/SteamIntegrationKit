// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_RequestEligiblePromoItemDefinitionsIDs_AsyncFunction.h"

#include "Async/Async.h"

USIK_RequestEligiblePromoItemDefinitionsIDs_AsyncFunction* USIK_RequestEligiblePromoItemDefinitionsIDs_AsyncFunction::
RequestEligiblePromoItemDefinitionsIDs(FSIK_SteamId SteamID)
{
	USIK_RequestEligiblePromoItemDefinitionsIDs_AsyncFunction* Node = NewObject<USIK_RequestEligiblePromoItemDefinitionsIDs_AsyncFunction>();
	Node->Var_SteamID = SteamID;
	return Node;
}

void USIK_RequestEligiblePromoItemDefinitionsIDs_AsyncFunction::OnEligiblePromoItemDefinitionsIDsReceived(
	SteamInventoryEligiblePromoItemDefIDs_t* SteamInventoryEligiblePromoItemDefIDs, bool bIOFailure)
{
	auto Param = *SteamInventoryEligiblePromoItemDefIDs;
	AsyncTask(ENamedThreads::GameThread, [this, Param,bIOFailure]()
	{
		if(bIOFailure)
		{
			OnFailure.Broadcast(ESIK_Result::ResultFail, FSIK_SteamId(), -1, false);
		}
		else
		{
			OnSuccess.Broadcast(ESIK_Result::ResultOK, Param.m_steamID, Param.m_numEligiblePromoItemDefs, Param.m_bCachedData);
		}
	});
	SetReadyToDestroy();
	MarkAsGarbage();
}

void USIK_RequestEligiblePromoItemDefinitionsIDs_AsyncFunction::Activate()
{
	Super::Activate();
	if(!SteamInventory())
	{
		OnFailure.Broadcast(ESIK_Result::ResultFail, FSIK_SteamId(), -1, false);
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	CallbackHandle = SteamInventory()->RequestEligiblePromoItemDefinitionsIDs(Var_SteamID.GetSteamID());
	if(CallbackHandle == k_uAPICallInvalid)
	{
		OnFailure.Broadcast(ESIK_Result::ResultFail, FSIK_SteamId(), -1, false);
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	CallResult.Set(CallbackHandle, this, &USIK_RequestEligiblePromoItemDefinitionsIDs_AsyncFunction::OnEligiblePromoItemDefinitionsIDsReceived);
	
}
