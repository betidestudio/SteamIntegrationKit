// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_SetPersonaName_AsyncFunction.h"

#include "Async/Async.h"

USIK_SetPersonaName_AsyncFunction* USIK_SetPersonaName_AsyncFunction::SetPersonaName(const FString& PersonaName)
{
	USIK_SetPersonaName_AsyncFunction* BlueprintNode = NewObject<USIK_SetPersonaName_AsyncFunction>();
	BlueprintNode->m_PersonaName = PersonaName;
	return BlueprintNode;
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
void USIK_SetPersonaName_AsyncFunction::OnSetPersonaName(PersonaStateChange_t* PersonaStateChange, bool bIOFailure)
{
	auto Param = *PersonaStateChange;
	AsyncTask(ENamedThreads::GameThread, [this, Param, bIOFailure]()
	{
		if(bIOFailure)
		{
			OnFailure.Broadcast();
		}
		else
		{
			OnSuccess.Broadcast();
		}
	});
	SetReadyToDestroy();
	MarkAsGarbage();
}
#endif

void USIK_SetPersonaName_AsyncFunction::Activate()
{
	Super::Activate();
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() == nullptr)
	{
		OnFailure.Broadcast();
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	m_CallbackHandle = SteamFriends()->SetPersonaName(TCHAR_TO_UTF8(*m_PersonaName));
	if(m_CallbackHandle == k_uAPICallInvalid)
	{
		OnFailure.Broadcast();
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	m_Callback.Set(m_CallbackHandle, this, &USIK_SetPersonaName_AsyncFunction::OnSetPersonaName);
#else
	OnFailure.Broadcast();
	SetReadyToDestroy();
	MarkAsGarbage();
#endif
}
