// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_RequestHistoryServerList_AsyncFunction.h"

#include "SIK_SharedFile.h"
#include "Async/Async.h"


USIK_RequestHistoryServerList_AsyncFunction* USIK_RequestHistoryServerList_AsyncFunction::RequestHistoryServerList(
	FSIK_AppId AppId, const TMap<FString, FString>& Filters, float TimeOut)
{
	USIK_RequestHistoryServerList_AsyncFunction* BlueprintNode = NewObject<USIK_RequestHistoryServerList_AsyncFunction>();
	BlueprintNode->VarAppId = AppId;
	BlueprintNode->Filters = Filters;
	BlueprintNode->Var_TimeOut = TimeOut;
	return BlueprintNode;
}

void USIK_RequestHistoryServerList_AsyncFunction::Activate()
{
	Super::Activate();
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMatchmakingServers())
	{
		return;
	}
	MatchMakingKeyValuePair_t* KeyValuePairs = new MatchMakingKeyValuePair_t[Filters.Num()];
	int32 Index = 0;
	for(auto& Elem : Filters)
	{
		KeyValuePairs[Index] = MatchMakingKeyValuePair_t(TCHAR_TO_ANSI(*Elem.Key), TCHAR_TO_ANSI(*Elem.Value));
		Index++;
	}
	HServerListRequest Request = SteamMatchmakingServers()->RequestHistoryServerList(VarAppId.GetAppID(), &KeyValuePairs, Filters.Num(), this);
	FDateTime DateTime = FDateTime::UtcNow();
	StartTime = DateTime.ToUnixTimestamp();
#else
	OnFailure.Broadcast(ESIK_MatchMakingServerResponse::ServerResponded, TArray<FSIK_FoundServers>());
	SetReadyToDestroy();
	MarkAsGarbage();
#endif
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
void USIK_RequestHistoryServerList_AsyncFunction::ServerResponded(HServerListRequest hRequest, int iServer)
{
	UE_LOG(LogTemp, Warning, TEXT("ServerResponded"));
	//Calculate the time from the start of the request
	FDateTime DateTime = FDateTime::UtcNow();
	const double CurrentTime = DateTime.ToUnixTimestamp();
	const double TimeElapsed = CurrentTime - StartTime;
	if(TimeElapsed >= Var_TimeOut)
	{
		UE_LOG(LogTemp, Warning, TEXT("Time out exceeded with current time: %f"), TimeElapsed);
		SteamMatchmakingServers()->CancelQuery(hRequest);
	}
}

void USIK_RequestHistoryServerList_AsyncFunction::ServerFailedToRespond(HServerListRequest hRequest, int iServer)
{
	UE_LOG(LogTemp, Warning, TEXT("ServerFailedToRespond"));
	FDateTime DateTime = FDateTime::UtcNow();
	const double CurrentTime = DateTime.ToUnixTimestamp();
	const double TimeElapsed = CurrentTime - StartTime;
	if(TimeElapsed >= Var_TimeOut)
	{
		UE_LOG(LogTemp, Warning, TEXT("Time out exceeded with current time: %f"), TimeElapsed);
		SteamMatchmakingServers()->CancelQuery(hRequest);
	}
}

void USIK_RequestHistoryServerList_AsyncFunction::RefreshComplete(HServerListRequest hRequest,
	EMatchMakingServerResponse response)
{
	auto Param = response;
	auto input = hRequest;
	AsyncTask(ENamedThreads::GameThread, [this, Param, input]()
	{
		if(SteamMatchmakingServers()->GetServerCount(input) == 0)
		{
			OnSuccess.Broadcast(static_cast<TEnumAsByte<ESIK_MatchMakingServerResponse>>(Param), TArray<FSIK_FoundServers>());
		}
		else
		{
			TArray<FSIK_FoundServers> FoundServers;
			for(int32 i = 0; i < SteamMatchmakingServers()->GetServerCount(input); i++)
			{
				if(auto gameinfo = SteamMatchmakingServers()->GetServerDetails(input,i))
				{
					FoundServers.Add(*gameinfo);
				}
			}
			OnSuccess.Broadcast(static_cast<TEnumAsByte<ESIK_MatchMakingServerResponse>>(Param), FoundServers);
		}
		SteamMatchmakingServers()->ReleaseRequest(input);
         	SetReadyToDestroy();
         	MarkAsGarbage();
	});
}
#endif
