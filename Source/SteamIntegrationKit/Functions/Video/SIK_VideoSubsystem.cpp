// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_VideoSubsystem.h"


USIK_VideoSubsystem::USIK_VideoSubsystem()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	m_CallbackGetOPFSettingsResult.Register(this, &USIK_VideoSubsystem::OnGetOPFSettingsResultCallbck);
	m_CallbackGetVideoURLResult.Register(this, &USIK_VideoSubsystem::OnGetVideoURLResultCallbck);
	if(IsRunningDedicatedServer())
	{
		m_CallbackGetOPFSettingsResult.SetGameserverFlag();
		m_CallbackGetVideoURLResult.SetGameserverFlag();
	}
#endif
}
USIK_VideoSubsystem::~USIK_VideoSubsystem()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	m_CallbackGetOPFSettingsResult.Unregister();
	m_CallbackGetVideoURLResult.Unregister();
#endif
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
void USIK_VideoSubsystem::OnGetOPFSettingsResultCallbck(GetOPFSettingsResult_t* pParam)
{
	OnGetOPFSettingsResult.Broadcast(FSIK_AppId(pParam->m_unVideoAppID), static_cast<ESIK_Result>(pParam->m_eResult));
}

void USIK_VideoSubsystem::OnGetVideoURLResultCallbck(GetVideoURLResult_t* pParam)
{
	OnGetVideoURLResult.Broadcast(FSIK_AppId(pParam->m_unVideoAppID), static_cast<ESIK_Result>(pParam->m_eResult), pParam->m_rgchURL);
}
#endif