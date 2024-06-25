// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_VideoSubsystem.h"


void USIK_VideoSubsystem::OnGetOPFSettingsResultCallbck(GetOPFSettingsResult_t* pParam)
{
	OnGetOPFSettingsResult.Broadcast(FSIK_AppId(pParam->m_unVideoAppID), static_cast<ESIK_Result>(pParam->m_eResult));
}

void USIK_VideoSubsystem::OnGetVideoURLResultCallbck(GetVideoURLResult_t* pParam)
{
	OnGetVideoURLResult.Broadcast(FSIK_AppId(pParam->m_unVideoAppID), static_cast<ESIK_Result>(pParam->m_eResult), pParam->m_rgchURL);
}