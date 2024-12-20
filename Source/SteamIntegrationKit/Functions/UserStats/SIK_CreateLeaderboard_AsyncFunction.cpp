// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_CreateLeaderboard_AsyncFunction.h"

#include "Async/Async.h"


USIK_CreateLeaderboard_AsyncFunction* USIK_CreateLeaderboard_AsyncFunction::CreateLeaderboard(
	const FString& LeaderboardName, TEnumAsByte<ESIK_LeaderboardSortMethod> SortMethod,
	TEnumAsByte<ESIK_LeaderboardDisplayType> DisplayType)
{
	USIK_CreateLeaderboard_AsyncFunction* BlueprintNode = NewObject<USIK_CreateLeaderboard_AsyncFunction>();
	BlueprintNode->Var_LeaderboardName = LeaderboardName;
	BlueprintNode->Var_SortMethod = SortMethod;
	BlueprintNode->Var_DisplayType = DisplayType;
	return BlueprintNode;
}

void USIK_CreateLeaderboard_AsyncFunction::Activate()
{
	Super::Activate();
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
	if(!SteamUserStats() || Var_LeaderboardName.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("SteamUserStats() is nullptr or LeaderboardName is empty"));
		OnFailure.Broadcast(-1);
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	ELeaderboardSortMethod SortMethod;
	switch(Var_SortMethod)
	{
	case LeaderboardSortMethodNone:
		SortMethod = k_ELeaderboardSortMethodNone;
		break;
	case LeaderboardSortMethodAscending:
		SortMethod = k_ELeaderboardSortMethodAscending;
		break;
	case LeaderboardSortMethodDescending:
		SortMethod = k_ELeaderboardSortMethodDescending;
		break;
	default:
		SortMethod = k_ELeaderboardSortMethodNone;
	}
	ELeaderboardDisplayType DisplayType;
	switch(Var_DisplayType)
	{
	case LeaderboardDisplayTypeNone:
		DisplayType = k_ELeaderboardDisplayTypeNone;
		break;
	case LeaderboardDisplayTypeNumeric:
		DisplayType = k_ELeaderboardDisplayTypeNumeric;
		break;
	case LeaderboardDisplayTypeTimeSeconds:
		DisplayType = k_ELeaderboardDisplayTypeTimeSeconds;
		break;
	case LeaderboardDisplayTypeTimeMilliSeconds:
		DisplayType = k_ELeaderboardDisplayTypeTimeMilliSeconds;
		break;
	default:
		DisplayType = k_ELeaderboardDisplayTypeNone;
	}
	CallbackHandle = SteamUserStats()->FindOrCreateLeaderboard(TCHAR_TO_ANSI(*Var_LeaderboardName), SortMethod, DisplayType);
	if(CallbackHandle == k_uAPICallInvalid)
	{
		OnFailure.Broadcast(-1);
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	OnFindLeaderboardCallResult.Set(CallbackHandle, this, &USIK_CreateLeaderboard_AsyncFunction::OnFindLeaderboard);
#else
	OnFailure.Broadcast(-1);
	SetReadyToDestroy();
	MarkAsGarbage();
#endif
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
void USIK_CreateLeaderboard_AsyncFunction::OnFindLeaderboard(LeaderboardFindResult_t* pResult, bool bIOFailure)
{
	auto Param = *pResult;
	AsyncTask(ENamedThreads::GameThread, [this, Param,bIOFailure]()
	{
		if(bIOFailure)
		{
			OnFailure.Broadcast(-1);
			SetReadyToDestroy();
			MarkAsGarbage();
			return;
		}
		if(Param.m_bLeaderboardFound)
		{
			OnSuccess.Broadcast(Param.m_hSteamLeaderboard);
		}
		else
		{
			OnFailure.Broadcast(-1);
		}
	});
	SetReadyToDestroy();
	MarkAsGarbage();
}
#endif