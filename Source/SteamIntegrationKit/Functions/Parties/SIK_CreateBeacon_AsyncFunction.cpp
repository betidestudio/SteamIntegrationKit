// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_CreateBeacon_AsyncFunction.h"

#include "Async/Async.h"

USIK_CreateBeacon_AsyncFunction* USIK_CreateBeacon_AsyncFunction::CreateBeacon(int32 OpenSlots,
                                                                               const FSIK_SteamPartyBeaconLocation& Location, const FString& ConnectString, const FString& Metadata)
{
	USIK_CreateBeacon_AsyncFunction* Node = NewObject<USIK_CreateBeacon_AsyncFunction>();
	Node->Var_nOpenSlots = OpenSlots;
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
	Node->Var_Location = Location.GetSteamPartyBeaconLocation();
#endif
	Node->Var_sConnectString = ConnectString;
	Node->Var_sMetadata = Metadata;
	return Node;
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
void USIK_CreateBeacon_AsyncFunction::OnCreateBeaconCallback(CreateBeaconCallback_t* CreateBeaconCallback,
                                                             bool bIOFailure)
{
	auto Param = *CreateBeaconCallback;
	AsyncTask(ENamedThreads::GameThread, [this, Param,bIOFailure]()
	{
		if(bIOFailure)
		{
			OnFailure.Broadcast(ESIK_Result::ResultFail, FSIK_PartyBeaconID());
		}
		else
		{
			TEnumAsByte<ESIK_Result> Result = static_cast<ESIK_Result>(Param.m_eResult);
			FSIK_PartyBeaconID BeaconID = Param.m_ulBeaconID;
			OnSuccess.Broadcast(Result, BeaconID);
		}
	});
	SetReadyToDestroy();
	MarkAsGarbage();
}
#endif

void USIK_CreateBeacon_AsyncFunction::Activate()
{
	Super::Activate();
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
	if(!SteamParties())
	{
		OnFailure.Broadcast(ESIK_Result::ResultFail, FSIK_PartyBeaconID());
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	CallbackHandle = SteamParties()->CreateBeacon(Var_nOpenSlots, &Var_Location, TCHAR_TO_ANSI(*Var_sConnectString), TCHAR_TO_ANSI(*Var_sMetadata));
	if(CallbackHandle == k_uAPICallInvalid)
	{
		OnFailure.Broadcast(ESIK_Result::ResultFail, FSIK_PartyBeaconID());
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	OnCreateBeaconCallResult.Set(CallbackHandle, this, &USIK_CreateBeacon_AsyncFunction::OnCreateBeaconCallback);
#else
	OnFailure.Broadcast(ESIK_Result::ResultFail, FSIK_PartyBeaconID());
	SetReadyToDestroy();
	MarkAsGarbage();
#endif
}
