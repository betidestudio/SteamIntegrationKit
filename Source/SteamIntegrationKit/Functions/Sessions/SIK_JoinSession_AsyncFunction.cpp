// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_JoinSession_AsyncFunction.h"
#include "OnlineSubsystemUtils.h"
#include "Kismet/GameplayStatics.h"

USIK_JoinSession_AsyncFunction* USIK_JoinSession_AsyncFunction::JoinSIKSessions(UObject* WorldContextObject, FName SessionName, FSSessionFindStruct SessionToJoin)
{
	USIK_JoinSession_AsyncFunction* Ueik_JoinSessionObject = NewObject<USIK_JoinSession_AsyncFunction>();
	Ueik_JoinSessionObject->Var_SessionToJoin = SessionToJoin;
	Ueik_JoinSessionObject->Var_SessionName = SessionName;
	Ueik_JoinSessionObject->Var_WorldContextObject = WorldContextObject;
	return Ueik_JoinSessionObject;
}

void USIK_JoinSession_AsyncFunction::Activate()
{
	JoinSession();
	Super::Activate();
}

void USIK_JoinSession_AsyncFunction::JoinSession()
{
	if(const IOnlineSubsystem *SubsystemRef = Online::GetSubsystem(this->GetWorld(), STEAM_SUBSYSTEM))
	{
		if(const IOnlineSessionPtr SessionPtrRef = SubsystemRef->GetSessionInterface())
		{
 			SessionPtrRef->OnJoinSessionCompleteDelegates.AddUObject(this, &USIK_JoinSession_AsyncFunction::OnJoinSessionCompleted);
			SessionPtrRef->JoinSession(0, Var_SessionName,Var_SessionToJoin.SessionResult.OnlineResult);
		}
		else
		{
			if(bDelegateCalled)
			{
				return;
			}
			OnFail.Broadcast(ESIKJoinResult::UnknownError, FString());
			bDelegateCalled = true;
			SetReadyToDestroy();
			MarkAsGarbage();
		}
	}
	else
	{
		if(bDelegateCalled)
		{
			return;
		}
		OnFail.Broadcast(ESIKJoinResult::UnknownError, FString());
		bDelegateCalled = true;
		SetReadyToDestroy();
		MarkAsGarbage();
	}
}
void USIK_JoinSession_AsyncFunction::OnJoinSessionCompleted(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (bDelegateCalled)
	{
		return;
	}
	if (Result == EOnJoinSessionCompleteResult::Success)
	{
		if (APlayerController* PlayerControllerRef = UGameplayStatics::GetPlayerController(Var_WorldContextObject, 0))
		{
			if (const IOnlineSubsystem* SubsystemRef = Online::GetSubsystem(GetWorld(), STEAM_SUBSYSTEM))
			{
				const IOnlineSessionPtr SessionPtrRef = SubsystemRef->GetSessionInterface();
				if (SessionPtrRef.IsValid())
				{
					FString JoinAddress;
					SessionPtrRef->GetResolvedConnectString(SessionName, JoinAddress);
					if (Var_SessionToJoin.bIsDedicatedServer)
					{
						FString PortInfo = "7777";
						if (Var_SessionToJoin.SessionSettings.Contains("PortInfo"))
						{
							Var_SessionToJoin.SessionResult.OnlineResult.Session.SessionSettings.Get("PortInfo", PortInfo);
						}
						TArray<FString> IpPortArray;
						JoinAddress.ParseIntoArray(IpPortArray, TEXT(":"), true);
						const FString IpAddress = IpPortArray[0];
						JoinAddress = IpAddress + ":" + PortInfo;
					}

					if (!JoinAddress.IsEmpty())
					{
						PlayerControllerRef->ClientTravel(JoinAddress, ETravelType::TRAVEL_Absolute);
						OnSuccess.Broadcast(ESIKJoinResult::Success, JoinAddress);
						bDelegateCalled = true;
						SetReadyToDestroy();
MarkAsGarbage();
						return;
					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("EIK: Could not retrieve address"));
						OnFail.Broadcast(ESIKJoinResult::CouldNotRetrieveAddress, FString());
						bDelegateCalled = true;
						SetReadyToDestroy();
MarkAsGarbage();
						return;
					}
				}
			}
		}
		else
		{
			OnFail.Broadcast(ESIKJoinResult::UnknownError, FString());
			bDelegateCalled = true;
			SetReadyToDestroy();
MarkAsGarbage();
			return;
		}
	}
	else
	{
		switch (Result)
		{
			case EOnJoinSessionCompleteResult::SessionIsFull:
				OnFail.Broadcast(ESIKJoinResult::SessionIsFull, FString());
				break;
			case EOnJoinSessionCompleteResult::SessionDoesNotExist:
				OnFail.Broadcast(ESIKJoinResult::SessionDoesNotExist, FString());
				break;
			case EOnJoinSessionCompleteResult::CouldNotRetrieveAddress:
				OnFail.Broadcast(ESIKJoinResult::CouldNotRetrieveAddress, FString());
				break;
			case EOnJoinSessionCompleteResult::AlreadyInSession:
				OnFail.Broadcast(ESIKJoinResult::AlreadyInSession, FString());
				break;
			default:
				OnFail.Broadcast(ESIKJoinResult::UnknownError, FString());
		}
		SetReadyToDestroy();
MarkAsGarbage();
		bDelegateCalled = true;
	}
}


