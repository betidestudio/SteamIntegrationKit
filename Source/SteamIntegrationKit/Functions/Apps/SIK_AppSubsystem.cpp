// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_AppSubsystem.h"

#include "Async/Async.h"

USIK_AppSubsystem::USIK_AppSubsystem()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	m_CallbackDlcInstalled.Register(this, &USIK_AppSubsystem::OnDlcInstalledCallbck);
	m_CallbackFileDetails.Register(this, &USIK_AppSubsystem::OnFileDetailsCallbck);
	m_CallbackNewUrlLaunchParameters.Register(this, &USIK_AppSubsystem::OnNewUrlLaunchParametersCallbck);
	m_CallbackTimedTrialStatus.Register(this, &USIK_AppSubsystem::OnTimedTrialStatusCallbck);

 	if(IsRunningDedicatedServer())
 	{
 		m_CallbackDlcInstalled.SetGameserverFlag();
 		m_CallbackFileDetails.SetGameserverFlag();
 		m_CallbackNewUrlLaunchParameters.SetGameserverFlag();
 		m_CallbackTimedTrialStatus.SetGameserverFlag();
 	}
#endif
}

USIK_AppSubsystem::~USIK_AppSubsystem()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	m_CallbackDlcInstalled.Unregister();
	m_CallbackFileDetails.Unregister();
	m_CallbackNewUrlLaunchParameters.Unregister();
	m_CallbackTimedTrialStatus.Unregister();
#endif
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
void USIK_AppSubsystem::OnDlcInstalledCallbck(DlcInstalled_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnDlcInstalled.Broadcast(Param.m_nAppID);
	});
}

void USIK_AppSubsystem::OnFileDetailsCallbck(FileDetailsResult_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		TArray<uint8> SHA;
		for (int i = 0; i < 20; i++)
		{
			SHA[i] = Param.m_FileSHA[i];
		}
		OnFileDetails.Broadcast(static_cast<ESIK_Result>(Param.m_eResult), Param.m_ulFileSize, Param.m_unFlags, SHA);
	});
}

void USIK_AppSubsystem::OnNewUrlLaunchParametersCallbck(NewUrlLaunchParameters_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnNewUrlLaunchParameters.Broadcast();
	});
}

void USIK_AppSubsystem::OnTimedTrialStatusCallbck(TimedTrialStatus_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnTimedTrialStatus.Broadcast(Param.m_unAppID, Param.m_bIsOffline, Param.m_unSecondsAllowed, Param.m_unSecondsPlayed);
	});
}
#endif