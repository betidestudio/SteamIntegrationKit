// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_DestroySession_AsyncFunction.h"
#include "OnlineSubsystemUtils.h"
#include "Kismet/GameplayStatics.h"

USIK_DestroySession_AsyncFunction* USIK_DestroySession_AsyncFunction::DestroySIKSessions(
	FName SessionName)
{
	USIK_DestroySession_AsyncFunction* Ueik_DestroySessionObject = NewObject<USIK_DestroySession_AsyncFunction>();
	Ueik_DestroySessionObject->Var_SessionName = SessionName;
	return Ueik_DestroySessionObject;
}

void USIK_DestroySession_AsyncFunction::Activate()
{
	DestroySession();
	Super::Activate();
}

void USIK_DestroySession_AsyncFunction::DestroySession()
{
	if(const IOnlineSubsystem *SubsystemRef = Online::GetSubsystem(GetWorld(), STEAM_SUBSYSTEM))
	{
		if(const IOnlineSessionPtr SessionPtrRef = SubsystemRef->GetSessionInterface())
		{
			SessionPtrRef->OnDestroySessionCompleteDelegates.AddUObject(this,&USIK_DestroySession_AsyncFunction::OnDestroySessionCompleted);
			SessionPtrRef->DestroySession(Var_SessionName);
		}
		else
		{
			if(bDelegateCalled)
			{
				return;
			}
			OnFail.Broadcast();
			SetReadyToDestroy();
			MarkAsGarbage();
			bDelegateCalled = true;
		}
	}
	else
	{
		if(bDelegateCalled)
		{
			return;
		}
		OnFail.Broadcast();
		SetReadyToDestroy();
MarkAsGarbage();
		bDelegateCalled = true;
	}
}

void USIK_DestroySession_AsyncFunction::OnDestroySessionCompleted(FName SessionName, bool bWasSuccess)
{
	if(bDelegateCalled)
	{
		return;
	}
	bDelegateCalled = true;
	if(bWasSuccess)
	{
		OnSuccess.Broadcast();
	}
	else
	{
		OnFail.Broadcast();
	}
	SetReadyToDestroy();
MarkAsGarbage();
}
