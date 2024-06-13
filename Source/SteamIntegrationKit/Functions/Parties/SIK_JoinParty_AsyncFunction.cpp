// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_JoinParty_AsyncFunction.h"

#include "Async/Async.h"

USIK_JoinParty_AsyncFunction* USIK_JoinParty_AsyncFunction::JoinParty(FSIK_PartyBeaconID SteamId)
{
	USIK_JoinParty_AsyncFunction* Node = NewObject<USIK_JoinParty_AsyncFunction>();
	Node->Var_SteamId = SteamId;
	return Node;
}

void USIK_JoinParty_AsyncFunction::OnJoinPartyCallback(JoinPartyCallback_t* JoinPartyCallback, bool bIOFailure)
{
	auto Param = *JoinPartyCallback;
	AsyncTask(ENamedThreads::GameThread, [this, Param,bIOFailure]()
	{
		if(bIOFailure)
		{
			OnFailure.Broadcast(ESIK_Result::ResultFail, FSIK_PartyBeaconID(0), FSIK_SteamId(0), TEXT(""));
		}
		else
		{
			TEnumAsByte<ESIK_Result> Result = static_cast<ESIK_Result>(Param.m_eResult);
			FSIK_PartyBeaconID PartyBeaconID = Param.m_ulBeaconID;
			FSIK_SteamId BeaconOwner = Param.m_SteamIDBeaconOwner;
			FString ConnectString = FString(UTF8_TO_TCHAR(Param.m_rgchConnectString));
			OnSuccess.Broadcast(Result, PartyBeaconID, BeaconOwner, ConnectString);
		}
	});
	SetReadyToDestroy();
	MarkAsGarbage();
}

void USIK_JoinParty_AsyncFunction::Activate()
{
	Super::Activate();
	if(!SteamParties())
	{
		OnFailure.Broadcast(ESIK_Result::ResultFail, FSIK_PartyBeaconID(0), FSIK_SteamId(0), TEXT(""));
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	CallbackHandle = SteamParties()->JoinParty(Var_SteamId.GetPartyBeaconID());
	if(CallbackHandle == k_uAPICallInvalid)
	{
		OnFailure.Broadcast(ESIK_Result::ResultFail, FSIK_PartyBeaconID(0), FSIK_SteamId(0), TEXT(""));
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	JoinPartyCallResult.Set(CallbackHandle, this, &USIK_JoinParty_AsyncFunction::OnJoinPartyCallback);
}
