// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_RequestStoreAuthURL_AsyncFunction.h"

#include "Async/Async.h"

USIK_RequestStoreAuthURL_AsyncFunction* USIK_RequestStoreAuthURL_AsyncFunction::RequestStoreAuthURL(const FString& URL)
{
	USIK_RequestStoreAuthURL_AsyncFunction* BlueprintNode = NewObject<USIK_RequestStoreAuthURL_AsyncFunction>();
	BlueprintNode->m_URL = URL;
	return BlueprintNode;
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
void USIK_RequestStoreAuthURL_AsyncFunction::OnRequestStoreAuthURL(StoreAuthURLResponse_t* StoreAuthURLResponse,
                                                                   bool bIOFailure)
{
	auto Param = *StoreAuthURLResponse;
	AsyncTask(ENamedThreads::GameThread, [this, Param, bIOFailure]()
	{
		if (bIOFailure)
		{
			OnFailure.Broadcast("");
		}
		else
		{
			OnSuccess.Broadcast(UTF8_TO_TCHAR(Param.m_szURL));
		}
	});
	SetReadyToDestroy();
	MarkAsGarbage();
}
#endif

void USIK_RequestStoreAuthURL_AsyncFunction::Activate()
{
	Super::Activate();
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
	if (!SteamUser())
	{
		OnFailure.Broadcast("");
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	m_SteamAPICall = SteamUser()->RequestStoreAuthURL(TCHAR_TO_UTF8(*m_URL));
	m_Callback.Set(m_SteamAPICall, this, &USIK_RequestStoreAuthURL_AsyncFunction::OnRequestStoreAuthURL);
#else
	OnFailure.Broadcast("");
	SetReadyToDestroy();
	MarkAsGarbage();
#endif
}
