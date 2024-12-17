// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_AssociateWithClan_AsyncFunction.h"

#include "Async/Async.h"

USIK_AssociateWithClan_AsyncFunction* USIK_AssociateWithClan_AsyncFunction::AssociateWithClan(
	const FSIK_SteamId& SteamIdClan)
{
	USIK_AssociateWithClan_AsyncFunction* Node = NewObject<USIK_AssociateWithClan_AsyncFunction>();
	Node->SteamIdClan = SteamIdClan;
	return Node;
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
void USIK_AssociateWithClan_AsyncFunction::OnAssociateWithClanCallBack(
	AssociateWithClanResult_t* AssociateWithClanResult, bool bIOFailure)
{
	auto Param = *AssociateWithClanResult;
	AsyncTask(ENamedThreads::GameThread, [this, Param,bIOFailure]()
	{
		if (bIOFailure)
		{
			OnFailure.Broadcast(ESIK_Result::ResultFail);
		}
		else
		{
			const TEnumAsByte<ESIK_Result> Result = static_cast<ESIK_Result>(Param.m_eResult);
			if(Result == ESIK_Result::ResultOK)
			{
				OnSuccess.Broadcast(Result);
			}
			else
			{
				OnFailure.Broadcast(Result);
			}
		}
	});
	SetReadyToDestroy();
	MarkAsGarbage();
}
#endif

void USIK_AssociateWithClan_AsyncFunction::Activate()
{
	Super::Activate();
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamGameServer())
	{
		OnFailure.Broadcast(ESIK_Result::ResultFail);
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	CallbackHandle = SteamGameServer()->AssociateWithClan(SteamIdClan.GetSteamID());
	if(CallbackHandle == k_uAPICallInvalid)
	{
		OnFailure.Broadcast(ESIK_Result::ResultFail);
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	OnAssociateWithClanCallResult.Set(CallbackHandle, this, &USIK_AssociateWithClan_AsyncFunction::OnAssociateWithClanCallBack);
#else
	OnFailure.Broadcast(ESIK_Result::ResultFail);
	SetReadyToDestroy();
	MarkAsGarbage();
#endif
}
