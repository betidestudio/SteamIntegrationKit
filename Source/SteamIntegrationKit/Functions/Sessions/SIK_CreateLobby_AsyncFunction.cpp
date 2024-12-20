// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_CreateLobby_AsyncFunction.h"
#include "Online/OnlineSessionNames.h"

void USIK_CreateLobby_AsyncFunction::Activate()
{
	CreateLobby();
	Super::Activate();
}

void USIK_CreateLobby_AsyncFunction::CreateLobby()
{
	if(const IOnlineSubsystem *SubsystemRef = Online::GetSubsystem(this->GetWorld(), STEAM_SUBSYSTEM))
	{
		if(const IOnlineSessionPtr SessionPtrRef = SubsystemRef->GetSessionInterface())
		{
			FOnlineSessionSettings SessionCreationInfo;
			SessionCreationInfo.bIsDedicated = false;
			SessionCreationInfo.bAllowInvites = Var_CreateLobbySettings.bAllowInvites;
			SessionCreationInfo.bIsLANMatch = Var_CreateLobbySettings.bIsLanMatch;
			SessionCreationInfo.NumPublicConnections = NumberOfPublicConnections;
			SessionCreationInfo.NumPrivateConnections = Var_CreateLobbySettings.NumberOfPrivateConnections;
			SessionCreationInfo.bUseLobbiesIfAvailable = true;
			SessionCreationInfo.bUsesPresence = Var_CreateLobbySettings.bUsePresence;
			SessionCreationInfo.bAllowJoinViaPresence = Var_CreateLobbySettings.bUsePresence;
			SessionCreationInfo.bAllowJoinViaPresenceFriendsOnly = false;
			SessionCreationInfo.bShouldAdvertise = Var_CreateLobbySettings.bShouldAdvertise;
			SessionCreationInfo.bAllowJoinInProgress = Var_CreateLobbySettings.bAllowJoinInProgress;
 			for (auto& Settings_SingleValue : SessionSettings)
			{
				if (Settings_SingleValue.Key.Len() == 0)
				{
					continue;
				}
				FOnlineSessionSetting Setting;
				Setting.AdvertisementType = EOnlineDataAdvertisementType::ViaOnlineService;
				Setting.Data = Settings_SingleValue.Value.GetVariantData();
				SessionCreationInfo.Set(FName(*Settings_SingleValue.Key), Setting);
			}
			SessionPtrRef->OnCreateSessionCompleteDelegates.AddUObject(this, &USIK_CreateLobby_AsyncFunction::OnCreateLobbyCompleted);
			SessionPtrRef->CreateSession(0,VSessionName,SessionCreationInfo);
		}
		else
		{
			if(bDelegateCalled == false)
			{
				UE_LOG(LogOnline, Warning, TEXT("EIK: SessionPtrRef is null"));
				OnFail.Broadcast(FSIK_SteamId());
				SetReadyToDestroy();
				MarkAsGarbage();
				bDelegateCalled = true;
			}
		}
	}
	else
	{
		if(bDelegateCalled == false)
		{
			UE_LOG(LogOnline, Warning, TEXT("EIK: SubsystemRef is null"));
			OnFail.Broadcast(FSIK_SteamId());
			SetReadyToDestroy();
			MarkAsGarbage();
			bDelegateCalled = true;
		}
	}
}

void USIK_CreateLobby_AsyncFunction::OnCreateLobbyCompleted(FName SessionName, bool bWasSuccessful)
{
	if(bWasSuccessful)
	{
		if(bDelegateCalled == false)
		{
			const IOnlineSessionPtr Sessions = Online::GetSubsystem(GetWorld(), STEAM_SUBSYSTEM)->GetSessionInterface();
			if(const FOnlineSession* CurrentSession = Sessions->GetNamedSession(VSessionName))
			{
				OnSuccess.Broadcast(CurrentSession->SessionInfo.Get()->GetSessionId().ToString());
				bDelegateCalled = true;
				SetReadyToDestroy();
				MarkAsGarbage();
			}
			else
			{
				OnSuccess.Broadcast(FSIK_SteamId());
				bDelegateCalled = true;
				SetReadyToDestroy();
				MarkAsGarbage();
			}
		}
	}
	else
	{
		if(bDelegateCalled == false)
		{
			UE_LOG(LogOnline, Warning, TEXT("EIK: CreateLobby failed and response was false. Check logs for more information."));
			OnFail.Broadcast(FSIK_SteamId());
			SetReadyToDestroy();
			MarkAsGarbage();
			bDelegateCalled = true;
		}
	}
}

USIK_CreateLobby_AsyncFunction* USIK_CreateLobby_AsyncFunction::CreateSIKLobby(TMap<FString, FSIKAttribute> SessionSettings,
FName SessionName,
	int32 NumberOfPublicConnections, FSIKCreateLobbySettings ExtraSettings)
{
	USIK_CreateLobby_AsyncFunction* Ueik_CreateLobbyObject= NewObject<USIK_CreateLobby_AsyncFunction>();
	Ueik_CreateLobbyObject->NumberOfPublicConnections = NumberOfPublicConnections;
	Ueik_CreateLobbyObject->SessionSettings = SessionSettings;
	Ueik_CreateLobbyObject->Var_CreateLobbySettings = ExtraSettings;
	Ueik_CreateLobbyObject->VSessionName = SessionName;
	return Ueik_CreateLobbyObject;
}
