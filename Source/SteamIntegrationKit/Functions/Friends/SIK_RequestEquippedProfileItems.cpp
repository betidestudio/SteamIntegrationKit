// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_RequestEquippedProfileItems.h"

USIK_RequestEquippedProfileItems* USIK_RequestEquippedProfileItems::RequestEquippedProfileItems(
	const FSIK_SteamId& SteamId)
{
	USIK_RequestEquippedProfileItems* Node = NewObject<USIK_RequestEquippedProfileItems>();
	Node->m_SteamId = SteamId;
	return Node;
}

void USIK_RequestEquippedProfileItems::Activate()
{
	Super::Activate();
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(SteamFriends() == nullptr)
	{
		OnFailure.Broadcast(ESIK_Result::ResultFail, FSIK_SteamId(), false, false, false, false);
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	m_CallbackHandle = SteamFriends()->RequestUserInformation(m_SteamId.GetSteamID(), true);
	if(m_CallbackHandle == k_uAPICallInvalid)
	{
		OnFailure.Broadcast(ESIK_Result::ResultFail, FSIK_SteamId(), false, false, false, false);
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
#if !WITH_ENGINE_STEAM
	m_Callback.Set(m_CallbackHandle, this, &USIK_RequestEquippedProfileItems::OnRequestEquippedProfileItems);
#endif
#else
	OnFailure.Broadcast(ESIK_Result::ResultFail, FSIK_SteamId(), false, false, false, false);
	SetReadyToDestroy();
	MarkAsGarbage();
#endif
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
#if !WITH_ENGINE_STEAM
void USIK_RequestEquippedProfileItems::OnRequestEquippedProfileItems(EquippedProfileItems_t* EquippedProfileItemsResponse, bool bIOFailure)
{
	auto Param = *EquippedProfileItemsResponse;
	AsyncTask(ENamedThreads::GameThread, [this, Param, bIOFailure]()
	{
		if(bIOFailure)
		{
			OnFailure.Broadcast(ESIK_Result::ResultFail, FSIK_SteamId(), false, false, false, false);
		}
		else
		{
			if(Param.m_eResult == EResult::k_EResultOK)
			{
				FSIK_SteamId SteamId(Param.m_steamID);
				OnSuccess.Broadcast(static_cast<ESIK_Result>(Param.m_eResult), SteamId, Param.m_bHasAvatarFrame, Param.m_bHasProfileModifier, Param.m_bHasProfileBackground, Param.m_bHasMiniProfileBackground);
			}
			else
			{
				OnFailure.Broadcast(static_cast<ESIK_Result>(Param.m_eResult), FSIK_SteamId(), false, false, false, false);
			}
		}
	});
	SetReadyToDestroy();
	MarkAsGarbage();
}
#endif
#endif