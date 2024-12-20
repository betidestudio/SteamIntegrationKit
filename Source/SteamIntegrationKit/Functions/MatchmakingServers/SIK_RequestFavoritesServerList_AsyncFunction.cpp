// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_RequestFavoritesServerList_AsyncFunction.h"

#include "SIK_SharedFile.h"
#include "Async/Async.h"

USIK_RequestFavoritesServerList_AsyncFunction* USIK_RequestFavoritesServerList_AsyncFunction::RequestFavoritesServerList(FSIK_AppId AppId,
	const TMap<FString, FString>& Filters, float TimeOut)
{
	USIK_RequestFavoritesServerList_AsyncFunction* BlueprintNode = NewObject<USIK_RequestFavoritesServerList_AsyncFunction>();
	BlueprintNode->VarAppId = AppId;
	BlueprintNode->Filters = Filters;
	BlueprintNode->Var_TimeOut = TimeOut;
	return BlueprintNode;
}

void USIK_RequestFavoritesServerList_AsyncFunction::Activate()
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
	HServerListRequest Request = SteamMatchmakingServers()->RequestFavoritesServerList(VarAppId.GetAppID(), &KeyValuePairs, Filters.Num(), this);
	FDateTime DateTime = FDateTime::UtcNow();
	StartTime = DateTime.ToUnixTimestamp();
#else
	OnFailure.Broadcast(ESIK_MatchMakingServerResponse::ServerResponded, TArray<FSIK_FoundServers>());
	SetReadyToDestroy();
	MarkAsGarbage();
#endif
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
void USIK_RequestFavoritesServerList_AsyncFunction::ServerResponded(HServerListRequest hRequest, int iServer)
{
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

void USIK_RequestFavoritesServerList_AsyncFunction::ServerFailedToRespond(HServerListRequest hRequest, int iServer)
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

void USIK_RequestFavoritesServerList_AsyncFunction::RefreshComplete(HServerListRequest hRequest,
	EMatchMakingServerResponse response)
{
	auto Param = response;
	auto input = hRequest;
	AsyncTask(ENamedThreads::GameThread, [this, Param, input, hRequest]()
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
		SteamMatchmakingServers()->ReleaseRequest(hRequest);
SetReadyToDestroy();
MarkAsGarbage();
	});
}
#endif