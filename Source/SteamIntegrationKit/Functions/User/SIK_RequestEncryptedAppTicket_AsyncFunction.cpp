// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_RequestEncryptedAppTicket_AsyncFunction.h"

#include "Async/Async.h"

USIK_RequestEncryptedAppTicket_AsyncFunction* USIK_RequestEncryptedAppTicket_AsyncFunction::RequestEncryptedAppTicket(
	const TArray<uint8>& EncryptedAppTicket)
{
	USIK_RequestEncryptedAppTicket_AsyncFunction* BlueprintNode = NewObject<USIK_RequestEncryptedAppTicket_AsyncFunction>();
	BlueprintNode->m_EncryptedAppTicket = EncryptedAppTicket;
	return BlueprintNode;
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
void USIK_RequestEncryptedAppTicket_AsyncFunction::OnRequestEncryptedAppTicket(
	EncryptedAppTicketResponse_t* EncryptedAppTicketResponse, bool bIOFailure)
{
	auto Param = *EncryptedAppTicketResponse;
	AsyncTask(ENamedThreads::GameThread, [this, Param, bIOFailure]()
	{
		if (bIOFailure)
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

void USIK_RequestEncryptedAppTicket_AsyncFunction::Activate()
{
	Super::Activate();
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
	if (!SteamUser())
	{
		OnFailure.Broadcast(ESIK_Result::ResultBusy);
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	void *pData = m_EncryptedAppTicket.GetData();
	int cbData = m_EncryptedAppTicket.Num();
	m_SteamAPICall = SteamUser()->RequestEncryptedAppTicket(pData, cbData);
	if(m_SteamAPICall == k_uAPICallInvalid)
	{
		OnFailure.Broadcast(ESIK_Result::ResultFail);
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	m_Callback.Set(m_SteamAPICall, this, &USIK_RequestEncryptedAppTicket_AsyncFunction::OnRequestEncryptedAppTicket);
#else
	OnFailure.Broadcast(ESIK_Result::ResultFail);
	SetReadyToDestroy();
	MarkAsGarbage();
#endif
}
